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

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_dummy);
  RUN_TEST(test_no_args);
  RUN_TEST(test_help);
  RUN_TEST(test_verbose);
  RUN_TEST(test_help_and_verbose);
  RUN_TEST(test_verbose_and_help);
  return UNITY_END();
}
