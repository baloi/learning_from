/* SprintTest.c
 * compile with:
 * $ cc SprintTest.c ../unity.c -o SprintTest
 */
#include <stdio.h>
#include "../unity.h"

void test_Sprintf_NoFormatOperations(void) {
    char output[5];
    TEST_ASSERT_EQUAL(3, sprintf(output, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", output);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Sprintf_NoFormatOperations);
    return UNITY_END();
}
