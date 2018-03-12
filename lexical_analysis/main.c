#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lexical_analysis.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  const char* filename = "sample.txt";
  char* tokens[BUFFER_SIZE];
  int tokens_counts;

  return lexical_analysis(filename, tokens, &tokens_counts);
}