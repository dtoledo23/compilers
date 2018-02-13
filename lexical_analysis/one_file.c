#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// families.c
// ---------------------------------------------

bool isAlphabetic(char c) {
  if (c >= 'a' && c <= 'z') return true;
  if (c >= 'A' && c <= 'Z') return true;
  return false;
}

bool isNumeric(char c) {
  if (c >= '0' && c <= '9') return true;
  return false;
}

bool isOctal(char c) {
  if (c >= '0' && c <= '7') return true;
  return false;
}

bool isHexadecimal(char c){
  if (c >= '0' && c <= '9') return true;
  if (c >= 'a' && c <= 'f') return true;
  if (c >= 'A' && c <= 'F') return true;
  return false;
}

bool isAlphanumeric(char c) {
  return isAlphabetic(c) || isNumeric(c);
}

bool isDot(char c) {
  return c == '.';
}

bool isUnderscore(char c) {
  return c == '_';
}

bool isSign(char c) {
  return c == '+' || c == '-';
}

bool isTokenAcceptedChar(char c) {
  return isAlphanumeric(c) || isUnderscore(c);
}

bool isE(char c) {
    return c == 'e' || c == 'E';
  }

bool isX(char c) {
  return c == 'x' || c == 'X';
}

// util.c
// ---------------------------------------------

#define SIZE 1024
char ignore_buff[SIZE];
char buff[SIZE];

const char *delimiter_characters = " /\n\t";
const char *blank_characters = " \n\t";
FILE *lexemeStart, *advance;

void initialize(const char* filename) {
  printf("Opening %s.\n", filename);
  lexemeStart = fopen(filename, "r");
  advance = fopen(filename, "r");
}

char getNext() {
  return fgetc(advance);
}

int move(FILE* file, int spaces) {
  return fseek(file, ftell(file) + spaces, SEEK_SET);
}

char readNext() {
  char c = getNext();
  if (c != EOF) {
    move(advance, -1);
  }
  return c;
}

bool isfeof() {
  return readNext() == EOF;
}

void readAdvance(char* buffer) {
  long start = ftell(lexemeStart);
  long end = ftell(advance);

  fread(buffer, end - start, 1, lexemeStart);
  fseek(lexemeStart, start, SEEK_SET);
  buffer[end-start] = '\0';
}

void acceptAdvance() {
  long start = ftell(lexemeStart);
  long end = ftell(advance);

  fseek(lexemeStart, end, SEEK_SET);
}

void resetAdvance() {
  fseek(advance, ftell(lexemeStart), SEEK_SET);
}


bool isDelimiterChar(char c) {
  if (c == EOF) return true;
  return strchr(delimiter_characters, c) != NULL;
}

bool isBlankChar(char c) {
  return strchr(blank_characters, c) != NULL;
}

// Move the file pointers to first non-blank character.
// Return true if it moved the pointers, false if nothing happened.
bool skipBlanks() {
  bool moved = false;
  bool keepMoving = true;

  while(isBlankChar(getNext())) {
    if (isfeof()) {
      acceptAdvance();
      return false;
    }

    moved = true;
  }

  // If not EOF we need to go back to keep
  // pointer at start of next token.
  if (moved) {
    move(advance, -1);
    acceptAdvance();
  } else {
    resetAdvance();
  }

  return moved;
}

// If encountered with the comments initiators, move the file pointers to 
// first position in next line. Return true if it moved the pointers, false 
// if nothing happened.
bool skipComment() {
  char c1 = getNext();
  char c2 = getNext();

  if (c1 == '/' && c2 == '/') {
    fgets (ignore_buff, SIZE, advance);
    acceptAdvance();
    return true;
  } else {
    resetAdvance();
    return false;
  }
}

// Move file pointer to next valid token. Ignoring comments and blanks along the way.
void moveToNextToken() {
  bool keepMoving = true;

  while(keepMoving) {
    bool b = skipBlanks();
    bool c = skipComment();
    if (isfeof()) break;
    keepMoving = b || c;
  }
}

bool hasNextToken() {
  moveToNextToken();
  return !isfeof();
}

char* nextToken() {
  if (!hasNextToken()) return NULL;

  // Advance till next delimiter
  while(!isDelimiterChar(readNext())) getNext();

  // Read advanced positions and append end of
  // string character at the end.
  int size = ftell(advance) - ftell(lexemeStart);
  readAdvance(buff);
  buff[size] = '\0';
  return buff;
}

int getCurrentLine() {
  long currentPos = ftell(lexemeStart);
  fseek(lexemeStart, 0, SEEK_SET);

  int i;
  int lines = 1;
  for(i = 0; i < currentPos; i++) {
    char c = fgetc(lexemeStart);
    if (c == '\n') {
      
      lines++;
    }
  }
  return lines;
}

// floating.c
// ---------------------------------------------
static const char* floatingName = "Floating number";

bool isAcceptedFloating(char c) {
  return isTokenAcceptedChar(c)
    || isDot(c) 
    || isSign(c);
}

bool floating(char* name, char* token) {

  // States
  const int INITIAL = 0;
  const int MANTISA1 = 1;
  const int MANTISA_DOT = 2;
  const int MANTISA2 = 3;
  const int EXP_E = 4;
  const int EXP_SIGN = 5;
  const int EXP_NUM = 6;
  const int REJECTED = 7;

  int state = 0;

  while(isAcceptedFloating(readNext())) {
    char c = getNext();
    switch(state) {
      case INITIAL:
        if (isNumeric(c)) state = MANTISA1;
        else state = REJECTED;
        break;
      case MANTISA1:
        if (isNumeric(c)) state = MANTISA1;
        else if (isDot(c)) state = MANTISA_DOT;
        else state = REJECTED;
        break;
      case MANTISA_DOT:
        if (isNumeric(c)) state = MANTISA2;
        else state = REJECTED;
        break;
      case MANTISA2:
        if (isNumeric(c)) state = MANTISA2;
        else if (isE(c)) state = EXP_E;
        else state = REJECTED;
        break;
      case EXP_E:
        if (isNumeric(c)) state = EXP_NUM;
        else if (isSign(c)) state = EXP_SIGN;
        else state = REJECTED;
        break;
      case EXP_SIGN:
        if (isNumeric(c)) state = EXP_NUM;
        else state = REJECTED;
        break;
      case EXP_NUM:
        if (isNumeric(c)) state = EXP_NUM;
        else state = REJECTED;
        break;
      case REJECTED:
        return false;
    }
  }

  if(state == MANTISA2 || state == EXP_NUM) {
    stpcpy(name, floatingName);
    readAdvance(token);
    return true;
  }

  return false;
}


// hexadecimal.c
// ---------------------------------------------
static const char* hexadecimalName = "Hexadecimal number";

bool hexadecimal(char* name, char* token) {
  // States
  const int INITIAL = 0;
  const int ZERO = 1;
  const int X = 2;
  const int HEX = 3;
  const int REJECTED = 4;

  int state = 0;

  while(isTokenAcceptedChar(readNext())) {
    char c = getNext();
    switch(state) {
      case INITIAL:
        if (c == '0') state = ZERO;
        else state = REJECTED;
        break;
      case ZERO:
        if (isX(c)) state = X;
        else state = REJECTED;
        break;
      case X:
        if (isHexadecimal(c)) state = HEX;
        else state = REJECTED;
        break;
      case HEX:
        if (isHexadecimal(c)) state = HEX;
        else state = REJECTED;
        break;
      case REJECTED:
        return false;
    }
  }

  if(state == HEX) {
    stpcpy(name, hexadecimalName);
    readAdvance(token);
    return true;
  }

  return false;
}


// natural.c
// ---------------------------------------------
static const char* naturalName = "Natural number";

bool natural(char* name, char* token) {
  // States
  const int INITIAL = 0;
  const int NATURAL = 1;
  const int REJECTED = 2;

  int state = 0;

  while(isTokenAcceptedChar(readNext())) {
    char c = getNext();
    switch(state) {
      case INITIAL:
        if (c == '0') state = REJECTED;
        else if (isNumeric(c)) state = NATURAL;
        else state = REJECTED;
        break;
      case NATURAL:
        if (isNumeric(c)) state = NATURAL;
        else state = REJECTED;
        break;
      case REJECTED:
        return false;
    }
  }

  if(state == NATURAL) {
    stpcpy(name, naturalName);
    readAdvance(token);
    return true;
  }

  return false;
}


// octal.c
// ---------------------------------------------
static const char* octalName = "Octal number";

bool octal(char* name, char* token) {
  // States
  const int INITIAL = 0;
  const int OCTAL = 1;
  const int REJECTED = 2;
  int state = 0;

  while(isTokenAcceptedChar(readNext())) {
    char c = getNext();
    switch(state) {
      case INITIAL:
        if (c == '0') state = OCTAL;
        else state = REJECTED;
        break;
      case OCTAL:
        if (isOctal(c)) state = OCTAL;
        else state = REJECTED;
        break;
      case REJECTED:
        return false;
    }
  }

  if(state == OCTAL) {
    stpcpy(name, octalName);
    readAdvance(token);
    return true;
  }

  return false;
}


// arithmetic.c
// ---------------------------------------------
static const char* sumName = "Sum";
static const char* substractionName = "Substraction";
static const char* multiplicationName = "Multiplication";
static const char* divisionName = "Division";

bool arithmetics(char* name, char* token) {
  char c = getNext();
  bool accepted = false;

  if (c == '+') {
    strcpy(name, sumName);
    accepted = true;
  }

  if (c == '-') {
    strcpy(name, substractionName);
    accepted = true;
  }

  if (c == '*') {
    strcpy(name, multiplicationName);
    accepted = true;
  }

   if (c == '/') {
    strcpy(name, divisionName);
    accepted = true;
  }

  if (accepted) {
    readAdvance(token);
    return true;
  }

  return false;
}


// asignation.c
// ---------------------------------------------
static const char* asignationName = "Asignation";

bool asignation(char* name, char* token) {
  char c = getNext();
  bool accepted = false;

  if (c == '=') {
    strcpy(name, asignationName);
    accepted = true;
  }

  if (accepted) {
    readAdvance(token);
    return true;
  }

  return false;
}

// logic.c
// ---------------------------------------------
// Keep both list congruent and updated.
static const int logicWordsCount = 3;
static const char* logicWords[] = {
  "and",
  "or",
  "not"
};
static const char* lexemeNames[] = {
  "Conjunction",
  "Disjunction",
  "Negation"
};

bool logic(char* name, char* token) {
  char* tk = nextToken();
  // printf("Called reserved for tk:%s\n", tk);
  for (int i = 0; i < logicWordsCount; i++) {
    if (strcmp(tk, logicWords[i]) == 0) {
      stpcpy(name, lexemeNames[i]);
      stpcpy(token, tk);
      return true;
    }
  }

  return false;
}


// relation.c
// ---------------------------------------------
static const char* acceptedChars = "=!<>";

static const char* equality = "Equality operator";
static const char* inequality = "Inequality operator";
static const char* greater = "Greater operator";
static const char* smaller = "Smaller operator";
static const char* greaterOrEqual = "Greater or Equal operator";
static const char* smallerOrEqual = "Smaller or Equal operator";

static bool isAcceptedRelation(char c) {
  return strchr(acceptedChars, c) != NULL;
}

// States
static const int INITIAL = 0;
static const int EQUAL = 1;
static const int EQUALITY = 2;
static const int ADMIRATION = 3;
static const int INEQUALITY = 4;
static const int GREATER = 5;
static const int GREATER_OR_EQUAL = 6;
static const int SMALLER = 7;
static const int SMALLER_OR_EQUAL = 8;
static const int REJECTED = 9;


bool relation(char* name, char* token) {
  int state = 0;

  while(isAcceptedRelation(readNext())) {
    char c = getNext();

    switch(state) {
      case INITIAL:
        if (c == '=') state = EQUAL;
        if (c == '!') state = ADMIRATION;
        if (c == '>') state = GREATER;
        if (c == '<') state = SMALLER;
        break;
      case EQUAL:
        if (c == '=') state = EQUALITY;
        else state = REJECTED;
        break;
      case EQUALITY:
        state = REJECTED;
        break;
      case ADMIRATION:
        if (c == '=') state = INEQUALITY;
        else state = REJECTED;
        break;
      case INEQUALITY:
        state = REJECTED;
        break;
      case GREATER:
        if (c == '=') state = GREATER_OR_EQUAL;
        else state = REJECTED;
        break;
      case GREATER_OR_EQUAL:
        state = REJECTED;
        break;
      case SMALLER:
        if (c == '=') state = SMALLER_OR_EQUAL;
        else state = REJECTED;
        break;
      case SMALLER_OR_EQUAL:
        state = REJECTED;
        break;
      case REJECTED:
        return false;
        break;
    }
  }

  switch(state) {
    case EQUALITY:
      stpcpy(name, equality);
      readAdvance(token);
      return true;
    case INEQUALITY:
      stpcpy(name, inequality);
      readAdvance(token);
      return true;
    case GREATER:
      stpcpy(name, greater);
      readAdvance(token);
      return true;
    case GREATER_OR_EQUAL:
      stpcpy(name, greaterOrEqual);
      readAdvance(token);
      return true;
    case SMALLER:
      stpcpy(name, smaller);
      readAdvance(token);
      return true;
    case SMALLER_OR_EQUAL:
      stpcpy(name, smallerOrEqual);
      readAdvance(token);
      return true;
  }
  
  return false;
}

// delimiter.c
// ---------------------------------------------
static const char* leftParenthesis = "Left Parenthesis";
static const char* rightParenthesis = "Right Parenthesis";
static const char* leftBrackets = "Left Brackets";
static const char* rightBrackets = "Right Brackets";

bool delimiter(char* name, char* token) {
  char c = getNext();
  bool accepted = false;

  if (c == '(') {
    strcpy(name, leftParenthesis);
    accepted = true;
  }

  if (c == ')') {
    strcpy(name, rightParenthesis);
    accepted = true;
  }

  if (c == '[') {
    strcpy(name, leftBrackets);
    accepted = true;
  }

  if (c == ']') {
    strcpy(name, rightBrackets);
    accepted = true;
  }

  if (accepted) {
    readAdvance(token);
    return true;
  }

  return false;
}

// identifier.c
// ---------------------------------------------
static const char* identifierName = "Identifier";

// q0 - initial
// q1 - accepted
// q2 - missing alphabetic
// q3 - rejected

bool identifier(char* name, char* token) {
  int currentState = 0;

  while(isTokenAcceptedChar(readNext())) {
    char c = getNext();
    // printf("Read char:%c state:%d\n", c, currentState);
    switch(currentState) {
    case 0:
      if (isAlphabetic(c)) currentState = 1;
      if (isUnderscore(c)) currentState = 2;
      if (isNumeric(c)) currentState = 3;
      break;
    case 1:
      // Do nothing once accepted it stays there.
      break;
    case 2:
      if (isAlphabetic(c)) currentState = 1;
      if (isUnderscore(c)) currentState = 2;
      if (isNumeric(c)) currentState = 2;
      break;
    case 3:
      // Do nothing
      return false;
      break;
    }
  }

  if (currentState == 1) {
    stpcpy(name, identifierName);
    readAdvance(token);
    return true;
  }

  return false;
}


// punctuation.c
// --------------------------------------------
static const char* dotName = "Dot";
static const char* commaName = "Comma";
static const char* semiColonName = "Semicolon";

bool punctuation(char* name, char* token) {
  char c = getNext();
  bool accepted = false;

  if (c == '.') {
    strcpy(name, dotName);
    accepted = true;
  }

  if (c == ',') {
    strcpy(name, commaName);
    accepted = true;
  }

  if (c == ';') {
    strcpy(name, semiColonName);
    accepted = true;
  }

  if (accepted) {
    readAdvance(token);
    return true;
  }

  return false;
}


// reserved.c
// --------------------------------------------
static const char* reservedName = "Reserved word";

static const int reservedWordsCount = 7;
static const char* reservedWords[] = {
   "program",
   "var",
   "begin",
   "end",
   "if",
   "then",
   "else"
};

bool reserved(char* name, char* token) {
  // printf("Called reserved\n");
  char* tk = nextToken();
  // printf("Called reserved for tk:%s\n", tk);
  for (int i = 0; i < reservedWordsCount; i++) {
    // printf("tk:%s  word:%s  equal:%d\n", tk, reservedWords[i], strcmp(tk, reservedWords[i]) == 0);
    if (strcmp(tk, reservedWords[i]) == 0) {
      stpcpy(name, reservedName);
      stpcpy(token, tk);
      return true;
    }
  }

  return false;
}


// main.c
// --------------------------------------------
#define BUFFER_SIZE 1024
#define LEXEME_TYPE_COUNT 12

const char* filename = "sample.txt";
char nameBuff[BUFFER_SIZE];
char tokenBuff[BUFFER_SIZE];

// Lexeme analyzer function type. It uses logic in utils to transverse a file.
// Return true if the next token in file matches with the given lexeme.
// If accepted, (returns true): The function will put the lexeme name in the first 
// parameter and the read token in the second.
// If rejected. It does nothing other than move the 'advance' file pointer.
typedef bool LEXEME(char*, char*);

// It states the priority of one lexeme over another. 
// When a token is available to analize. The lexemes will be executed in this order
// stopping when one of them is accepted.
LEXEME *lexemes[LEXEME_TYPE_COUNT] = {
  // Tokens
  reserved, 
  logic, 
  identifier,

   // Numbers
  floating, 
  hexadecimal, 
  octal, 
  natural,

  // Comparations (two characters)
  relation,

  // Single characters operations or symbols.
  delimiter,
  asignation,
  punctuation,
  arithmetics
};

int main(int argc, char *argv[]) {
  initialize(filename);
  
  bool accepted;
  while(hasNextToken()) {
    accepted = false;
    for(int i = 0; i < LEXEME_TYPE_COUNT; i++) {
      LEXEME* lexeme = lexemes[i];

      accepted = lexeme(nameBuff, tokenBuff);
      if (accepted) {
        printf("%s [%s]\n", nameBuff, tokenBuff);
        acceptAdvance();
        break;
      } else {
        resetAdvance();
      }
    }

    // None of the lexemes accepted the next token.
    if (!accepted) {
      printf("Error in line %d\n", getCurrentLine());
      break;
    }
  }

   printf("End of execution\n");
}