#include "stack.h"
#include "optional.h"
#include <limits.h>
#include <malloc.h>
#include <stdio.h>

StackNode* stackNewNode(int value) {
    StackNode* node = malloc(sizeof(StackNode));

    node->value = value;
    node->next = NULL;

    return node;
}

int isEmpty(StackNode* root) {
    return root == NULL;
}

void push(StackNode** root, int value) {
    StackNode* node = stackNewNode(value);

    node->next = *root;
    *root = node;
}

OptionalInt* pop_impl(StackNode** root) {
    OptionalInt* optional = malloc(sizeof(OptionalInt));

    if (isEmpty(*root)) {
        optional->isPresent = false;
        optional->value = INT_MIN;

        return optional;
    }

    StackNode* toPop = *root;

    *root = (*root)->next;
    optional->value = toPop->value;
    optional->isPresent = true;

    free(toPop);

    return optional;
}

void pop(StackNode** root, bool silent) {
    OptionalInt* result = pop_impl(root);

    if (result->isPresent) {
        if (!silent) {
            printf("%d\n", result->value);
        }
    } else {
        fprintf(stderr, "ERROR: trying to pop from an empty stack\n");
    }
    free(result);
}
