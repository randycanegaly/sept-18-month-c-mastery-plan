#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cl_args.h"

char *parse_args(int num_cl_args, char *argv[]) {
  char *result = (char *)malloc(128 * sizeof(char));

  if (num_cl_args == 0) {
    sprintf(result, NO_ARGS, num_cl_args);
    printf("no args result: %s\n", result);
  } else if (num_cl_args > 0 && strcmp(argv[0], "-h") == 0) {
    sprintf(result, USAGE);
    printf("help result: %s\n", result);
  } else if (num_cl_args > 0 && strcmp(argv[0], "-v") == 0) {
    sprintf(result, VERBOSE);
    printf("verbose result: %s\n", result);
  }
  return result;
}

#ifdef IS_EXE
int main(void) {
  printf("main() in cl_args.c ran\n");
  return EXIT_SUCCESS;
}
#endif
