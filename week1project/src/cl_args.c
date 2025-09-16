#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cl_args.h"

char *parse_args(int num_cl_args, char *argv[]) {
  char *result = (char *)calloc(1024, sizeof(char));

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
      // strcat(result, "");
    }
  }
  return result;
}

#ifdef IS_EXE
int main(void) {
  printf("main() in cl_args.c ran\n");
  return EXIT_SUCCESS;
}
#endif
