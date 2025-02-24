#include <stdio.h>
#include "interface.h"

void show_menu() {
    printf("Choose operation:\n");
    printf("1 - Add vectors\n");
    printf("2 - Scalar product\n");
    printf("3 - Exit\n");
}

void show_type_menu() {
    printf("Choose data type:\n");
    printf("1 - Real numbers (double)\n");
    printf("2 - Complex numbers (Complex)\n");
}
