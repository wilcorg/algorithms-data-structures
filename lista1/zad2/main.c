#include "circularLinkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {

    CircularList* list1 = createList();
    CircularList* list2 = createList();

    for (int i = 0; i < 10; i++) {
        insert(list1, 10 + i);
        insert(list2, 50 - i);
    }

    printf("1st list elements: ");
    toString(list1);

    printf("\n2nd list elements: ");
    toString(list2);

    merge(list1, &list2);

    printf("\n1st list elements after merge: ");
    toString(list1);

    printf("\n2nd list elements after merge: ");
    toString(list2);

    cleanup(&list1);
    printf("\n------------------------------------------------------\n");

    if (RAND_MAX < 100000) {
        fprintf(stderr, "ERROR: RAND_MAX less than 100000, the metrics will be incorrect");
        return -1;
    }

    int random_numbers[10000];
    long search_cost_sum = 0;
    double search_cost_avg = 0;
    srand(time(NULL));
    list1 = createList();

    for (int i = 0; i < 10000; i++) {
        random_numbers[i] = rand() % 100000;
        insert(list1, random_numbers[i]);
    }

    for (int i = 0; i < 10000; i++) {
        int value = exists(list1, random_numbers[rand() % 10000]);
//        printf("%d ", value);
        search_cost_sum += value;
    }
    search_cost_avg = (double) search_cost_sum / 10000.0;

    printf("Case when value exists in array:\n");
    printf("Search sum: %ld\n", search_cost_sum);
    printf("Search average: %lf\n", search_cost_avg);

    printf("------------------------------------------------------\n");

    search_cost_sum = 0;
    search_cost_avg = 0;

    for (int i = 0; i < 10000; i++) {
        int value = exists(list1, rand() % 100000);
        search_cost_sum += value;
    }
    search_cost_avg = (double) search_cost_sum / 10000.0;

    printf("Case when value may exist in array:\n");
    printf("Search sum: %ld\n", search_cost_sum);
    printf("Search average: %lf\n", search_cost_avg);

    cleanup(&list1);
    return 0;
}
