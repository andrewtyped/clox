#include <unity.h>

void setUp() {}
void tearDown() {}

void test_1(void)
{
    TEST_ASSERT_EQUAL_UINT8(1,1);
}

int main(int argc, const char* argv[]) {
    UNITY_BEGIN();

    RUN_TEST(test_1);
    
    return UNITY_END();
}