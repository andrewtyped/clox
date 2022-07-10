#include "../src/common.h"
#include "../src/chunk.h"
#include <unity.h>

void setUp() {}
void tearDown() {}

void test_Unity(void)
{
    TEST_ASSERT_EQUAL_UINT8(1,1);
    TEST_ASSERT_EQUAL_UINT8(1,2);
}

int main(int argc, const char* argv[]) {
    UNITY_BEGIN();

    RUN_TEST(test_Unity);
    
    return UNITY_END();
}