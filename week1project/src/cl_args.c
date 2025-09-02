#include <stdio.h>
#include <stdlib.h>

#include "cl_args.h"

#ifdef IS_EXE
int main(void) {
  printf("main() in cl_args.c ran\n");
  return EXIT_SUCCESS;
}
#endif
