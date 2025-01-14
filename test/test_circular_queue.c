#include <stdlib.h>

#include <unity.h>

#include "circular_queue.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_circular_queue_create_should_return_valid_queue(void) {
    size_t size = 10;
    circular_queue *queue = circular_queue_create(size);

    TEST_ASSERT_NOT_NULL(queue);
    TEST_ASSERT_NULL(queue->head);
    TEST_ASSERT_NULL(queue->tail);
    TEST_ASSERT_EQUAL(0, queue->length);
    TEST_ASSERT_EQUAL(size, queue->node_size);

    free(queue);
}

void test_circular_queue_create_should_fail_when_size_is_zero(void) {
    size_t size = 0;
    circular_queue *queue = circular_queue_create(size);

    TEST_ASSERT_NULL(queue);

    free(queue);
}

void test_circular_queue_node_create_should_return_valid_node(void) {
    size_t size = sizeof(int);
    int data = 42;
    circular_queue_node *node = circular_queue_node_create(&data, size);

    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(data, node->data);
    TEST_ASSERT_NULL(node->next);

    free(node);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_circular_queue_create_should_return_valid_queue);
    RUN_TEST(test_circular_queue_create_should_fail_when_size_is_zero);
    return UNITY_END();
}
