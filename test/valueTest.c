#include <unity.h>
#include <stdlib.h>
#include "../src/common.h"
#include "../src/value.h"
#include "../src/memory.h"

void setUp() {}
void tearDown() {}

void assert_valuearray_data(Value* expectedData, 
    int expectedCapacity, 
    int expectedCount, 
    ValueArray* actual) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(expectedCapacity, actual->capacity, "Bad Capacity");
        TEST_ASSERT_EQUAL_INT_MESSAGE(expectedCount, actual->count, "Bad Count");
        TEST_ASSERT_NOT_NULL_MESSAGE(actual->values, "values should be null");

        for(int i = 0; i < expectedCount; i++) {
            //Access the array values at the current index.
            double expectedDataPoint = *(expectedData + sizeof(double) * i);
            double actualDataPoint = *(actual->values + sizeof(double) * i);

            TEST_ASSERT_EQUAL_DOUBLE(expectedDataPoint, actualDataPoint);
        }
}

void assert_valuearray_empty(ValueArray* actual) {
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, actual->capacity, "Bad Capacity");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, actual->count, "Bad Count");
    TEST_ASSERT_NULL_MESSAGE(actual->values, "values should be null");
}

void test_valuearray_accepts_data(void)
{
    ValueArray valueArray;
    initValueArray(&valueArray);
    writeValueArray(&valueArray, 1.0);
    writeValueArray(&valueArray, 2.0);

    int size = 2;
    Value *expectedData = (Value *)malloc(size * sizeof(Value));
    expectedData[0] = 1.0L;
    expectedData[1] = 2.0L;

    assert_valuearray_data(expectedData, INITIAL_CAPACITY, 2, &valueArray);

    freeValueArray(&valueArray);

    assert_valuearray_empty(&valueArray);

    FREE_ARRAY(Value, expectedData, size);
}

int main(int argc, const char* argv[]) {
    UNITY_BEGIN();

    RUN_TEST(test_valuearray_accepts_data);
    
    return UNITY_END();
}