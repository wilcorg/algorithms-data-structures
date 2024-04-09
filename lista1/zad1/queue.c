#include "queue.h"
#include "optional.h"
#include <limits.h>
#include <malloc.h>
#include <stdio.h>

#pragma once

QNode* queueNewNode(int value) {
    QNode* temp = malloc(sizeof(QNode));

    temp->value = value;
    temp->next = NULL;

    return temp;
}

Queue* createQueue() {
    Queue* queue = malloc(sizeof(Queue));

    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

void enQueue(Queue* queue, int value) {
    QNode* temp = queueNewNode(value);

    // if queue is empty
    if (queue->rear == NULL) {
        queue->front = temp;
        queue->rear = temp;
    }

    // add new node to the end
    queue->rear->next = temp;
    // update rear
    queue->rear = temp;
}

OptionalInt* deQueue_impl(Queue* queue) {
    OptionalInt* optional = malloc(sizeof(OptionalInt));

    if (queue->front == NULL) {
        optional->isPresent = false;
        optional->value = INT_MIN;

        return optional;
    }

    QNode* temp = queue->front;

    optional->isPresent = true;
    optional->value = temp->value;

    queue->front = queue->front->next;
    free(temp);

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return optional;
}

void deQueue(Queue* queue, bool silent) {
    OptionalInt* result = deQueue_impl(queue);

    if (result->isPresent) {
        if (!silent) {
            printf("%d\n", result->value);
        }
    } else {
        fprintf(stderr, "ERROR: trying to dequeue an empty queue\n");
    }
    free(result);
}
