typedef struct LNode LNode;

struct LNode {
    int value;
    LNode* next;
};

typedef struct CircularList CircularList;

struct CircularList {
    int capacity;
    LNode* head;
    LNode* tail;
};

CircularList* createList();

void insert(CircularList* list, int value);

void merge(CircularList* list1, CircularList** list2);

void cleanup(CircularList** list);

void toString(CircularList* list);

int exists(CircularList* list, int value);
