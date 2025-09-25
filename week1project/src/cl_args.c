#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cl_args.h"

bool is_number(size_t len, char *str) {
  for (int i = 0; i < len; i++) {
    if (!isdigit(*(str + i))) {
      return false;
    }
  }
  return true;
}

char *parse_args(int argc, char *argv[]) {
  char *result = (char *)calloc(MAX_OUTPUT, sizeof(char));

  if (argc == 1) { // just the program name
    sprintf(result, NO_ARGS, argc - 1);
    printf("no args result: %s\n", result);
  } else {
    strcpy(result, "");
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-h") == 0) {
        strcat(result, USAGE);
      }
      if (strcmp(argv[i], "-v") == 0) {
        strcat(result, VERBOSE);
      }
      if (strcmp(argv[i], "-o") == 0) {
        if (i + 1 < argc) {
          char *test_for_number = argv[i + 1];
          if (is_number(strlen(test_for_number), test_for_number)) {
            strcat(result, "FAIL - incorrect value for '-o' option!\n");
          } else {
            snprintf(result + strlen(result), MAX_OUTPUT - strlen(result),
                     "%s\n", test_for_number);
          }
        } else {
          snprintf(result + strlen(result), MAX_OUTPUT - strlen(result),
                   "missing value for '-o' option\n");
        }
      }
      if (strcmp(argv[i], "-n") == 0) {
        if (i + 1 < argc) {
          char *test_for_number = argv[i + 1];
          if (!is_number(strlen(test_for_number), test_for_number)) {
            strcat(result, "FAIL - incorrect value for '-n' option!\n");
          } else {
            snprintf(result + strlen(result), MAX_OUTPUT - strlen(result),
                     "%s\n", test_for_number);
          }
        } else {
          snprintf(result + strlen(result), MAX_OUTPUT - strlen(result),
                   "missing value for '-n' option\n");
        }
      }
    }
  }
  return result;
}

#ifdef IS_EXE
int main(int argc, char *argv[]) {
  printf("Number of args: %d\n", argc);

  for (int i = 0; i < argc; i++) {
    printf("%s\n", argv[i]);
  }

  parse_args(argc, argv);

  printf("main() in cl_args.c ran\n");
  return EXIT_SUCCESS;
}
#endif
