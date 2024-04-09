#include "circularLinkedList.h"
#include <malloc.h>

LNode* listNewNode(int value) {
    LNode* temp = malloc(sizeof(LNode));

    temp->value = value;
    temp->next = NULL;

    return temp;
}

CircularList* createList() {
    CircularList* list = malloc(sizeof(CircularList));

    list->head = NULL;
    list->tail = NULL;
    list->capacity = 0;

    return list;
}

void insert(CircularList* list, int value) {
    LNode* newNode = listNewNode(value);

    if (list->tail == NULL) {
        newNode->next = newNode;
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->capacity += 1;
}

void merge(CircularList* list1, CircularList** list2) {
    if (list2 == NULL || (*list2)->head == NULL || (*list2)->tail == NULL) {
        return;
    }

    (*list2)->tail->next = NULL;
    LNode* nodeToMove = (*list2)->head;
    while (nodeToMove != NULL) {

        insert(list1, nodeToMove->value);
        nodeToMove = nodeToMove->next;
    }
    cleanup(list2);
}

void cleanup(CircularList** list) {
    if (*list == NULL) {
        return;
    }

    (*list)->tail->next = NULL;
    while ((*list)->head != NULL) {
        LNode* node = (*list)->head;

        (*list)->head = node->next;
        free(node);
        (*list)->capacity -= 1;
    }

    if ((*list)->capacity != 0) {
        fprintf(stderr, "WARNING: cleaned list had different node count than declared");
    }
    free(*list);
    *list = NULL;
}

void toString(CircularList* list) {
    if (list == NULL) {
        return;
    }

    LNode* current = list->head;
    do {
        printf("%d; ", current->value);
        current = current->next;
    } while (current != list->head);

}

int exists(CircularList* list, int value) {
    LNode* current = list->head;
    int i = 0;

    while (current->value != value) {
        if (i == list->capacity) {
            break;
        }

        current = current->next;
        i++;
    }
    return i;
}
