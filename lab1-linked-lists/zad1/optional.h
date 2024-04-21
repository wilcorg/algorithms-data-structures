#include <stdbool.h>

typedef struct OptionalInt OptionalInt;

struct OptionalInt {
    bool isPresent;
    int value;
};
