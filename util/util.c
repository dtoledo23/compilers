#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
