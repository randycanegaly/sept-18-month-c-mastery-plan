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

char *parse_args(int num_cl_args, char *argv[]) {
  char *result = (char *)calloc(1024, sizeof(char));
  char *temp = (char *)calloc(1024, sizeof(char));

  if (num_cl_args == 0) {
    sprintf(result, NO_ARGS, num_cl_args);
    printf("no args result: %s\n", result);
  } else {
    strcpy(result, "");
    for (int i = 0; i < num_cl_args; i++) {
      if (strcmp(argv[i], "-h") == 0) {
        strcat(result, USAGE);
      }
      if (strcmp(argv[i], "-v") == 0) {
        strcat(result, VERBOSE);
      }
      if (strcmp(argv[i], "-o") == 0) {
        if (i + 1 < num_cl_args) {
          char *test_for_number = argv[i + 1];
          if (is_number(strlen(test_for_number), test_for_number)) {
            strcat(result, "FAIL - incorrect value for '-o' option!\n");
          } else {
            sprintf(temp, "%s\n", test_for_number);
            strcat(result, temp);
          }
        } else {
          sprintf(temp, "missing value for '-o' option\n");
          strcat(result, temp);
        }
      }
      if (strcmp(argv[i], "-n") == 0) {
        if (i + 1 < num_cl_args) {
          char *test_for_number = argv[i + 1];
          if (!is_number(strlen(test_for_number), test_for_number)) {
            strcat(result, "FAIL - incorrect value for '-n' option!\n");
          } else {
            sprintf(temp, "%s\n", test_for_number);
            strcat(result, temp);
          }
        } else {
          sprintf(temp, "missing value for '-n' option\n");
          strcat(result, temp);
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

  printf("main() in cl_args.c ran\n");
  return EXIT_SUCCESS;
}
#endif
