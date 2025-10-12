#include "../../external/unity/src/unity.h"
#include "../src/cl_args.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *name = "program";
static Seen seen;

void setUp(void) {
  seen.seen_help = false;
  seen.seen_verbose = false;
  seen.seen_output = false;
  seen.seen_num = false;
}
void tearDown(void) {
  seen.seen_help = false;
  seen.seen_verbose = false;
  seen.seen_output = false;
  seen.seen_num = false;
}

void test_dummy(void) { printf("dummy test\n"); }

void test_no_args(void) {
  char *no_args[] = {name};
  char *actual = parse_args(1, no_args, &seen);
  char expected[128];
  sprintf(expected, NO_ARGS, 0);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  // I think I need to free actual because parse_args() allocates memory
  // for it. Where do I do that? Does execution flow get past
  // TEST_ASSERT_EQUAL_STRING if test fails???
  free(actual);
}

void test_help(void) {
  char *help = "-h";
  char *help_args[] = {name, help};
  char *actual = parse_args(2, help_args, &seen);
  char expected[128];
  TEST_ASSERT_EQUAL_STRING(USAGE, actual);
  free(actual);
}

void test_help_long(void) {
  char *help = "--help";
  char *help_args[] = {name, help};
  char *actual = parse_args(2, help_args, &seen);
  char expected[128];
  TEST_ASSERT_EQUAL_STRING(USAGE, actual);
  free(actual);
}

void test_verbose(void) {
  char *verbose = "-v";
  char *verbose_args[] = {name, verbose};
  char *actual = parse_args(2, verbose_args, &seen);
  char expected[128];
  TEST_ASSERT_EQUAL_STRING(VERBOSE, actual);
  free(actual);
}

void test_verbose_long(void) {
  char *verbose = "--verbose";
  char *verbose_args[] = {name, verbose};
  char *actual = parse_args(2, verbose_args, &seen);
  char expected[128];
  TEST_ASSERT_EQUAL_STRING(VERBOSE, actual);
  free(actual);
}

void test_verbose_dup(void) {
  size_t len = strlen(VERBOSE) + strlen(VERBOSE_DUP) + 1;
  char *expected = malloc(len);

  if (expected == NULL) {
    TEST_FAIL_MESSAGE("Memory allocation failed!");
  }

  snprintf(expected, len, "%s%s", VERBOSE, VERBOSE_DUP);
  char *verbose = "-v";
  char *verbose_word = "-v";
  char *verbose_args[] = {name, verbose, verbose_word};
  char *actual = parse_args(3, verbose_args, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
  free(expected);
}

void test_verbose_dup_both_types(void) {
  size_t len = strlen(VERBOSE) + strlen(VERBOSE_DUP) + 1;
  char *expected = malloc(len);

  if (expected == NULL) {
    TEST_FAIL_MESSAGE("Memory allocation failed!");
  }

  snprintf(expected, len, "%s%s", VERBOSE, VERBOSE_DUP);
  char *verbose = "-v";
  char *verbose_word = "--verbose";
  char *verbose_args[] = {name, verbose, verbose_word};
  char *actual = parse_args(3, verbose_args, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
  free(expected);
}

void test_help_dup(void) {
  size_t len = strlen(USAGE) + strlen(HELP_DUP) + 1;
  char *expected = malloc(len);

  if (expected == NULL) {
    TEST_FAIL_MESSAGE("Memory allocation failed!");
  }

  snprintf(expected, len, "%s%s", USAGE, HELP_DUP);
  char *help = "-h";
  char *help_word = "-h";
  char *help_args[] = {name, help, help_word};
  char *actual = parse_args(3, help_args, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
  free(expected);
}

void test_help_dup_both_types(void) {
  size_t len = strlen(USAGE) + strlen(HELP_DUP) + 1;
  char *expected = malloc(len);

  if (expected == NULL) {
    TEST_FAIL_MESSAGE("Memory allocation failed!");
  }

  snprintf(expected, len, "%s%s", USAGE, HELP_DUP);
  char *help = "-h";
  char *help_work = "--help";
  char *help_args[] = {name, help, help_work};
  char *actual = parse_args(3, help_args, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
  free(expected);
}

void test_help_and_verbose(void) {
  size_t len = strlen(USAGE) + strlen(VERBOSE) + 1;
  char *expected = malloc(len);

  if (expected == NULL) {
    TEST_FAIL_MESSAGE("Memory allocation failed!");
  }

  snprintf(expected, len, "%s%s", USAGE, VERBOSE);
  char *help = "-h";
  char *verbose = "-v";
  char *handv[] = {name, help, verbose};
  char *actual = parse_args(3, handv, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
}

void test_help_and_verbose_dup(void) {
  size_t len = strlen(USAGE) + strlen(VERBOSE) + strlen(VERBOSE_DUP) + 1;
  char *expected = malloc(len);

  if (expected == NULL) {
    TEST_FAIL_MESSAGE("Memory allocation failed!");
  }

  snprintf(expected, len, "%s%s", USAGE, VERBOSE);
  char *help = "-h";
  char *verbose = "-v";
  char *verbose_word = "--verbose";
  char *handv[] = {name, help, verbose, verbose_word};
  char *actual = parse_args(3, handv, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
}

void test_is_digit(void) {
  char test[32] = "123456";
  bool expected = true;
  bool actual = is_number(6, test);
  TEST_ASSERT(actual);
}

void test_is_not_digit(void) {
  char test[32] = "123456y";
  bool actual = is_number(7, test);
  TEST_ASSERT(!actual);
}

void test_dash_o_only(void) {
  char *output = "-o";
  char *test[] = {name, output};
  char *actual = parse_args(2, test, &seen);
  TEST_ASSERT_EQUAL_STRING(MISSING_OUTPUT, actual);
  free(actual);
}

void test_dash_o_next_is_dash(void) {
  size_t len = strlen(USAGE) + strlen(MISSING_OUTPUT) + 1;
  char *expected = malloc(len);

  if (expected == NULL) {
    TEST_FAIL_MESSAGE("Memory allocation failed!");
  }

  snprintf(expected, len, "%s%s", USAGE, MISSING_OUTPUT);
  char *output = "-o";
  char *file = "-o";
  char *test[] = {name, output, file};
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
}

void test_dash_o_next_is_number(void) {
  char *output = "-o";
  char *file = "52";
  char *test[] = {name, output, file};
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(USAGE, actual);
  free(actual);
}

void test_dash_o_next_is_file_name(void) {
  char *output = "-o";
  char *file = "output.txt";
  char *test[] = {name, output, file};
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(TEST_FILE, actual);
  free(actual);
}

void test_dash_o_long_next_is_file_name(void) {
  char *output = "--output";
  char *file = "output.txt";
  char *test[] = {name, output, file};
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(TEST_FILE, actual);
  free(actual);
}

void test_dash_n_only(void) {
  char *number = "-n";
  char *test[] = {name, number};
  char *actual = parse_args(2, test, &seen);
  TEST_ASSERT_EQUAL_STRING(MISSING_NUMBER, actual);
  free(actual);
}

void test_dash_n_next_is_dash(void) {
  size_t len = strlen(USAGE) + strlen(MISSING_NUMBER) + 1;
  char *expected = malloc(len);

  if (expected == NULL) {
    TEST_FAIL_MESSAGE("Memory allocation failed!");
  }

  snprintf(expected, len, "%s", MISSING_NUMBER);
  char *number = "-n";
  char *num = "-";
  char *test[] = {name, number, num};
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
}

void test_dash_n_next_is_file_name(void) {
  char *number = "-n";
  char *file = "output.txt";
  char *test[] = {name, number, file};
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(MISSING_NUMBER, actual);
  free(actual);
}

void test_dash_n_next_is_number(void) {
  char *number = "-n";
  char *num = "52";
  char *test[] = {name, number, num};
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(num, actual);
  free(actual);
}

void test_dash_n_long_next_is_number(void) {
  char *number = "--number";
  char *num = "52";
  char *test[] = {name, number, num};
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(num, actual);
  free(actual);
}

void test_dash_o_long_with_equals(void) {
  char *output = "--output=output.txt";
  char *test[] = {name, output};
  char *actual = parse_args(2, test, &seen);
  TEST_ASSERT_EQUAL_STRING(TEST_FILE, actual);
  free(actual);
}

void test_dash_o_long_with_equals_is_number(void) {
  char *output = "--output=52";
  char *test[] = {name, output};
  char *actual = parse_args(2, test, &seen);
  TEST_ASSERT_EQUAL_STRING(USAGE, actual);
  free(actual);
}

void test_dash_n_long_with_equals(void) {
  char *number = "--number=52";
  char *test[] = {name, number};
  char *actual = parse_args(2, test, &seen);
  TEST_ASSERT_EQUAL_STRING("52", actual);
  free(actual);
}

void test_dash_n_long_with_equals_is_file_name(void) {
  char *number = "--number=output.txt";
  char *test[] = {name, number};
  char *actual = parse_args(2, test, &seen);
  TEST_ASSERT_EQUAL_STRING(USAGE, actual);
  free(actual);
}

/*
//./program -o output.txt -o output.txt
void test_output_value_option(void) {
  char *output = "-o";
  char *file = "output.txt";
  char *test[] = {name, output, file};
  char expected[1024] = "output.txt\n";
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
}

void test_output_value_option_fail(void) {
  char *output = "-o";
  char *file = "12345";
  char *test[] = {name, output, file};
  char expected[1024] = "FAIL - incorrect value for '-o' option!\n";
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
}

void test_output_value_out_of_order(void) {
  char *output = "-o";
  char *file = "12345";
  char *test[] = {name, file, output};
  char expected[1024] = "missing value for '-o' option\n";
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
}

//./program -n 52
void test_number_value_option(void) {
  char *num = "-n";
  char *value = "52";
  char *test[] = {name, num, value};
  char expected[1024] = "52\n";
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
}

  void test_number_value_option_fail(void) {
  char *num = "-n";
  char *value = "dog";
  char *test[] = {name, num, value};
  char expected[1024] = "FAIL - incorrect value for '-n' option!\n";
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
}

void test_number_value_out_of_order(void) {
  char *num = "-n";
  char *value = "53";
  char *test[] = {name, value, num};
  char expected[1024] = "missing value for '-n' option\n";
  char *actual = parse_args(3, test, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
}

void test_number_and_output(void) {
  char *num = "-n";
  char *value = "52";
  char *output = "-o";
  char *file = "output.txt";
  char *test[] = {name, num, value, output, file};
  char expected[1024] = "52\noutput.txt\n";
  char *actual = parse_args(5, test, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
}

void test_number_and_output_bad_order(void) {
  char *num = "-n";
  char *value = "52";
  char *output = "-o";
  char *file = "output.txt";
  char *test[] = {name, num, value, file, output};
  char expected[1024] = "52\nmissing value for '-o' option\n";
  char *actual = parse_args(5, test, &seen);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  free(actual);
}
*/

/* Need tests for:
 * ./program -o -o or -o -v
 * ./program --verbose, --help, --output=output.txt, --number --> make an or to
 * take either -v or --verbose
 */

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_dummy);
  RUN_TEST(test_no_args);
  RUN_TEST(test_help);
  RUN_TEST(test_help_long);
  RUN_TEST(test_verbose);
  RUN_TEST(test_verbose_long);
  RUN_TEST(test_verbose_dup);
  RUN_TEST(test_help_dup);
  RUN_TEST(test_help_dup_both_types);
  RUN_TEST(test_verbose_dup_both_types);
  RUN_TEST(test_help_and_verbose);
  RUN_TEST(test_help_and_verbose_dup);
  RUN_TEST(test_is_digit);
  RUN_TEST(test_is_not_digit);
  // RUN_TEST(test_output_value_option);
  RUN_TEST(test_dash_o_only);
  RUN_TEST(test_dash_o_next_is_dash);
  RUN_TEST(test_dash_o_next_is_number);
  RUN_TEST(test_dash_o_next_is_file_name);
  RUN_TEST(test_dash_o_long_next_is_file_name);
  RUN_TEST(test_dash_n_only);
  RUN_TEST(test_dash_n_next_is_dash);
  RUN_TEST(test_dash_n_next_is_file_name);
  RUN_TEST(test_dash_n_next_is_number);
  RUN_TEST(test_dash_n_long_next_is_number);
  RUN_TEST(test_dash_o_long_with_equals);
  RUN_TEST(test_dash_n_long_with_equals);
  RUN_TEST(test_dash_o_long_with_equals_is_number);
  RUN_TEST(test_dash_n_long_with_equals_is_file_name);
  /*RUN_TEST(test_output_value_option_fail);
  RUN_TEST(test_output_value_out_of_order);
  RUN_TEST(test_number_value_option);
  RUN_TEST(test_number_value_option_fail);
  RUN_TEST(test_number_value_out_of_order);
  RUN_TEST(test_number_and_output);
  RUN_TEST(test_number_and_output_bad_order);*/
  return UNITY_END();
}
