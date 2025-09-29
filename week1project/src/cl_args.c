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

char *parse_args(int argc, char *argv[], Seen *seen) {
  char *result = (char *)calloc(MAX_OUTPUT, sizeof(char));

  if (argc == 1) { // just the program name
    sprintf(result, NO_ARGS, argc - 1);
    printf("no args result: %s\n", result);
  } else {
    strcpy(result, "");
    for (int i = 1; i < argc; i++) { // walk all argv strings
      if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
        if (!seen->seen_help) {
          strcat(result, USAGE);
          seen->seen_help = true;
        } else {
          strcat(result, HELP_DUP);
          break;
        }
      }
      if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
        if (!seen->seen_verbose) {
          strcat(result, VERBOSE);
          seen->seen_verbose = true;
        } else {
          strcat(result, VERBOSE_DUP);
          break;
        }
      }
      if (strcmp(argv[i], "-o") == 0) {
        if (i == argc - 1) { //-o is the last command line argument
          snprintf(result + strlen(result), MAX_OUTPUT - strlen(result),
                   MISSING_OUTPUT);
        } else if (i < argc - 1) {
          char *next_arg = argv[i + 1];
          if (next_arg[0] == '-' || is_number(strlen(next_arg), next_arg)) {
            strcat(result, USAGE);
          } else {
            strcat(result, next_arg);
          }
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

  static Seen seen;

  for (int i = 0; i < argc; i++) {
    printf("%s\n", argv[i]);
  }

  parse_args(argc, argv, &seen);

  printf("main() in cl_args.c ran\n");
  return EXIT_SUCCESS;
}
#endif
