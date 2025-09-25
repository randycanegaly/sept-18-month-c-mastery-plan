#include <stdbool.h>
#include <string.h>

#define USAGE                                                                  \
  "./parse_args [-v] [-h] [-o file] [-n number] [--verbose] [--help] "         \
  "[--output=file] [-number=number] "
#define NO_ARGS "You entered %d command line arguments."
#define VERBOSE "You requested verbose output. "
#define MAX_OUTPUT 1024

char *parse_args(int argc, char *argv[]);
bool is_number(size_t len, char *str);
