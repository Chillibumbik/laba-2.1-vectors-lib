#include <stdio.h>
#include "interface.h"
#include "handler.h"

void startInterface() {
    int dataType;

    printf("Select data type:\n");
    printf("1 - Double\n2 - Complex\n3 - Integer\n");
    while (scanf("%d", &dataType) != 1 || dataType < 1 || dataType > 3) {
        printf("Invalid input. Please select a valid option (1, 2, 3): ");
        while(getchar() != '\n');
    }

    handleVectorOperations(dataType);
}
