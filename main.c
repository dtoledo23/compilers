#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./lexical_analysis/lexical_analysis.h"
#include "./syntactic_analysis/syntactic_analysis.h"

#define TOKEN_SIZE 1024

int main(int argc, char *argv[]) {
  char* tokens[TOKEN_SIZE];
  int token_count = 0;
  char* filename;
  int exit_code;

  filename = "samples/program.txt";
  if (argc != 2) {
    printf("Filename not provided. Using default %s\n", filename);
  } else {
    filename = argv[1];
  }


  exit_code = lexical_analysis(filename, tokens, &token_count);
  if (exit_code) {
    printf("Lexical analysis failed.\n");
    return exit_code;
  }
  printf("Lexical analysis completed successfully\n");

  bool succeded = syntactic_analysis((const char**)tokens, token_count);
  if (!succeded) {
    printf("Syntactic analysis failed.");
    return exit_code;
  }

  printf("Syntactic analysis completed successfully\n");
  return 0;
}