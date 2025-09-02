#include "../../external/unity/src/unity.h"
#include "../src/cl_args.h"
#include <stdio.h>

void setUp(void) {}
void tearDown(void) {}

void test_dummy(void) { printf("dummy test\n"); }

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_dummy);
  return UNITY_END();
}
