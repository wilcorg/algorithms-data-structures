#include <stdbool.h>

typedef struct QNode QNode;

struct QNode {
    int value;
    QNode* next;
};

typedef struct Queue Queue;

struct Queue {
    QNode* front;
    QNode* rear;
};

Queue* createQueue();

void enQueue(Queue* queue, int value);

void deQueue(Queue* queue, bool silent);
