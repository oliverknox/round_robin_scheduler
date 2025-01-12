#include <stdlib.h>

#include <unity.h>

#include "circular_queue.h"

void setUp(void) {
    // Runs before each test (not needed here but required by Unity)
}

void tearDown(void) {
    // Runs after each test (not needed here but required by Unity)
}

void test_configuration_smoke_test(void) {
    // Create a simple circular queue to test your configuration
    size_t size = 5;
    circular_queue *queue = circular_queue_create(size);

    // Verify the queue is created successfully
    TEST_ASSERT_NOT_NULL(queue);
    TEST_ASSERT_EQUAL(size, queue->node_size);

    // Free the allocated queue
    free(queue);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_configuration_smoke_test);
    return UNITY_END();
}
