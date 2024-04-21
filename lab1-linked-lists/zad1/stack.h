#include <stdbool.h>

typedef struct StackNode StackNode;

struct StackNode {
    int value;
    StackNode* next;
};

void push(StackNode** root, int value);

void pop(StackNode** root, bool silent);
