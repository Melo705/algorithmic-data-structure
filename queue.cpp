/*
 * queue: fifo（first in and first out)
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_QUEUE_ELE_NUM 1024
#define INVALID_VAL -1

m_queue* g_queue = NULL;


int queue_pop(m_queue* q, int* ele)
{
    assert(q != NULL);

    if (q->is_empty == true) {
        printf("pop failed: queue q is empty\n");
        return -1;
    }

    pthread_mutex_lock(&q->mutex);

    // q->head for reading data element
    // pop() ele from q->data
    *ele = q->data[q->head];
    q->data[q->head] = INVALID_VAL;
    ++(q->head);

    // next loop
    if (q->head == q->size) {
        q->head = 0;
    }

    if (q->head == q->tail) {
        q.is_empty = true;
    }

    q.is_full = false;
    q.count--;
    
    pthread_mutex_ulock(&q->mutex);
    return 1;
}

int queue_push(m_queue* q, int ele)
{
    assert(q != NULL);
    if (q.is_full == true) {
        printf("push failed: queue q is full\n");
        return -1;
    }

    pthread_mutex_lock(&q->mutex);

    // for writing data element
    q->data[q->tail] = ele;
    ++(q->tail);

    // next loop
    if (q->tail == q->size) {
        q->tail = 0;
    }

    if (q->head == q->tail) {
        q->is_full = true;
    }

    q->is_empty = false;

    pthread_mutex_ulock(&q->mutex);
    return 1;
}

int queue_init(m_queue* q, int size)
{
    q = (m_queue*)malloc(sizeof(m_queue));
    if (q == NULL) {
        printf("Error in %s\n", __FUNCTION__);
        return -1;
    }
    
    // init data
    q->data = NULL;
    q->data = (int*)malloc(sizeof(int) * MAX_QUEUE_ELE_NUM)；
    if (q->data == NULL) {
        printf("init failed: q->data null\n");
        return -1;
    }

    q->head = 0;
    q->tail = 0;
    q->size = MAX_QUEUE_NUM;
    q->count = 0;
    q->is_empty = true;
    q->is_full = false;
    pthread_mutex_init(&q->mutex, 0);

    return 1;
}

m_queue* queue_clear(m_queue* q)
{
    if (q == NULL) {
        return NULL;
    }

    int data = 0;
    while (!q->is_empty) {
        (void)q.pop(q, &data);
    }
    return q;
}

m_queue* queue_destroy(m_queue* q)
{
    
}

