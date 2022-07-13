#include <unity.h>
#include "../src/common.h"
#include "../src/chunk.h"

void setUp() {}
void tearDown() {}

void assert_chunk_data(uint8_t* expectedData, 
    int expectedCapacity, 
    int expectedCount, 
    Chunk* actual) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(expectedCapacity, actual->capacity, "Bad Capacity");
        TEST_ASSERT_EQUAL_INT_MESSAGE(expectedCount, actual->count, "Bad Count");
        TEST_ASSERT_NOT_NULL_MESSAGE(actual->code, "code should be null");

        for(int i = 0; i < expectedCount; i++) {
            //Access the array values at the current index.
            uint8_t expectedDataPoint = *(expectedData + sizeof(uint8_t) * i);
            uint8_t actualDataPoint = *(actual->code + sizeof(uint8_t) * i);
            TEST_ASSERT_EQUAL_UINT8_MESSAGE(expectedDataPoint, actualDataPoint, "expected data mismatch");
        }
}

void assert_chunk_empty(Chunk* actual) {
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, actual->capacity, "Bad Capacity");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, actual->count, "Bad Count");
    TEST_ASSERT_NULL_MESSAGE(actual->code, "code should be null");
}

void test_chunk_accepts_data(void)
{
    Chunk chunk;
    initChunk(&chunk);
    writeChunk(&chunk, 1);
    writeChunk(&chunk, 2);

    uint8_t expectedData[] = {1, 2};

    assert_chunk_data(expectedData, 8, 2, &chunk);

    freeChunk(&chunk);

    assert_chunk_empty(&chunk);
}

int main(int argc, const char* argv[]) {
    UNITY_BEGIN();

    RUN_TEST(test_chunk_accepts_data);
    
    return UNITY_END();
}