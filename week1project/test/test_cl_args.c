#include "../../external/unity/src/unity.h"
#include "../src/cl_args.h"
#include <stdio.h>
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void test_dummy(void) { printf("dummy test\n"); }

void test_no_args(void) {
  char *no_args[] = {NULL};
  char *actual = parse_args(0, no_args);
  char expected[128];
  sprintf(expected, NO_ARGS, 0);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
  // I think I need to free actual because parse_args() allocates memory
  // for it. Where do I do that? Does execution flow get past
  // TEST_ASSERT_EQUAL_STRING if test fails???
}

void test_help(void) {
  char *help = "-h";
  char *help_args[] = {help};
  char *actual = parse_args(1, help_args);
  char expected[128];
  TEST_ASSERT_EQUAL_STRING(USAGE, actual);
}

void test_verbose(void) {
  char *verbose = "-v";
  char *verbose_args[] = {verbose};
  char *actual = parse_args(1, verbose_args);
  char expected[128];
  TEST_ASSERT_EQUAL_STRING(VERBOSE, actual);
}

void test_help_and_verbose(void) {
  char *help = "-h";
  char *verbose = "-v";
  char *handv[] = {help, verbose};
  char *actual = parse_args(2, handv);
  char expected[1024] = USAGE;
  strcat(expected, VERBOSE);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_verbose_and_help(void) {
  char *verbose = "-v";
  char *help = "-h";
  char *vandh[] = {verbose, help};
  char *actual = parse_args(2, vandh);
  char expected[1024] = VERBOSE;
  strcat(expected, USAGE);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
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

//./program -o output.txt -o output.txt
void test_output_value_option(void) {
  char *output = "-o";
  char *file = "output.txt";
  char *test[] = {output, file};
  char expected[1024] = "output.txt\n";
  char *actual = parse_args(2, test);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_output_value_option_fail(void) {
  char *output = "-o";
  char *file = "12345";
  char *test[] = {output, file};
  char expected[1024] = "FAIL - incorrect value for '-o' option!\n";
  char *actual = parse_args(2, test);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_output_value_out_of_order(void) {
  char *output = "-o";
  char *file = "12345";
  char *test[] = {file, output};
  char expected[1024] = "missing value for '-o' option\n";
  char *actual = parse_args(2, test);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
}

//./program -n 52
void test_number_value_option(void) {
  char *num = "-n";
  char *value = "52";
  char *test[] = {num, value};
  char expected[1024] = "52\n";
  char *actual = parse_args(2, test);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_number_value_option_fail(void) {
  char *num = "-n";
  char *value = "dog";
  char *test[] = {num, value};
  char expected[1024] = "FAIL - incorrect value for '-n' option!\n";
  char *actual = parse_args(2, test);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_number_value_out_of_order(void) {
  char *num = "-n";
  char *value = "53";
  char *test[] = {value, num};
  char expected[1024] = "missing value for '-n' option\n";
  char *actual = parse_args(2, test);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_number_and_output(void) {
  char *num = "-n";
  char *value = "52";
  char *output = "-o";
  char *file = "output.txt";
  char *test[] = {num, value, output, file};
  char expected[1024] = "52\noutput.txt\n";
  char *actual = parse_args(4, test);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_number_and_output_bad_order(void) {
  char *num = "-n";
  char *value = "52";
  char *output = "-o";
  char *file = "output.txt";
  char *test[] = {num, value, file, output};
  char expected[1024] = "52\nmissing value for '-o' option\n";
  char *actual = parse_args(4, test);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_dummy);
  RUN_TEST(test_no_args);
  RUN_TEST(test_help);
  RUN_TEST(test_verbose);
  RUN_TEST(test_help_and_verbose);
  RUN_TEST(test_verbose_and_help);
  RUN_TEST(test_is_digit);
  RUN_TEST(test_is_not_digit);
  RUN_TEST(test_output_value_option);
  RUN_TEST(test_output_value_option_fail);
  RUN_TEST(test_output_value_out_of_order);
  RUN_TEST(test_number_value_option);
  RUN_TEST(test_number_value_option_fail);
  RUN_TEST(test_number_value_out_of_order);
  RUN_TEST(test_number_and_output);
  RUN_TEST(test_number_and_output_bad_order);
  return UNITY_END();
}
