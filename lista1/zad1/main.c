#include "queue.h"
#include "stack.h"
#include <malloc.h>
#include <string.h>

int main(int argc, char* argv[]) {

    StackNode* root = NULL;
    Queue* queue = createQueue();
    bool silent = false;
    bool test_error = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--silent") == 0) {
            silent = true;
        } else if (strcmp(argv[i], "--test-error") == 0) {
            test_error = true;
        }
    }

    for (int i = 0; i < 50; i++) {
        push(&root, i);
        enQueue(queue, i);
    }

    for (int i = 0; i < 50; i++) {
        pop(&root, silent);
    }

    for (int i = 0; i < 50; i++) {
        deQueue(queue, silent);
    }

    if (test_error) {
        pop(&root, silent);
        deQueue(queue, silent);
    }

    free(root);
    free(queue);

    return 0;
}
