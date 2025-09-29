// cl_args.h
#ifndef CL_ARGS_H
#define CL_ARGS_H

#include <stdbool.h>
#include <string.h>

#define USAGE                                                                  \
  "./parse_args [-v] [-h] [-o file] [-n number] [--verbose] [--help] "         \
  "[--output=file] [-number=number] "
#define NO_ARGS "You entered %d command line arguments."
#define VERBOSE "You requested verbose output. "
#define VERBOSE_DUP " WARN: Duplicate option seen. "
#define HELP                                                                   \
  "./parse_args [-v] [-h] [-o file] [-n number] [--verbose] [--help] "         \
  "[--output=file] [-number=number]"
#define HELP_DUP "You requested help. WARN: Duplicate option seen."
#define MISSING_OUTPUT "Missing value for -o option."
#define TEST_FILE "output.txt"

#define MAX_OUTPUT 1024

typedef struct {
  bool seen_help;
  bool seen_verbose;
  bool seen_num;
  bool seen_output;
} Seen;

char *parse_args(int argc, char *argv[], Seen *seen);
bool is_number(size_t len, char *str);

#endif
