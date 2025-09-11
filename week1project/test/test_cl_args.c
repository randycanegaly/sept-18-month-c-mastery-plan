#include "../../external/unity/src/unity.h"
#include "../src/cl_args.h"
#include <stdio.h>

#define USAGE "./parse_args [-v] [-h] [-o file] [-n number] [--verbose] [--help] [--output=file] [-number=number]

void setUp(void) {}
void tearDown(void) {}

void test_dummy(void) { printf("dummy test\n"); }

void test_no_args(void) {
	char *no_args[0];	
	char *actual =  parse_args(1, no_args);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_dummy);
  RUN_TEST(test_no_args);
  return UNITY_END();
}
