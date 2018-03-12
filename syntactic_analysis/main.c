#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../common/names.h"
#include "./syntactic_analysis.h"

int main(int argc, char *argv[]) {
  const char** input;

  input = (const char*[]){
    identifier,
    asignation,
    natural,
    sum,
    leftParenthesis,
    natural,
    multiplication,
    natural,
    rightParenthesis
  };

  printf("Accepted: %d\n", syntactic_analysis(input, 9));


  input = (const char*[]){
    if_,
    natural,
    greaterOrEqual,
    octal,
    then,
    identifier,
    asignation,
    hexadecimal,
    else_,
    identifier,
    asignation,
    floating,
    end
  };

  printf("Accepted if-else: %d\n", syntactic_analysis(input, 13));

  input = (const char*[]){
    repeat,
    read,
    identifier,
    semiColon,
    write,
    natural,
    multiplication,
    identifier,
    until,
    identifier,
    smallerOrEqual,
    natural
  };

  printf("Accepted repeated: %d\n", syntactic_analysis(input, 12));
}
