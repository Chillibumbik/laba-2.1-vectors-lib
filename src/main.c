#include <stdio.h>
#include "interface.h"
#include "handlers.h"

int main() {
    while (1) {
        int data_type;
        show_type_menu();
        scanf("%d", &data_type);

        if (data_type == 1) {
            handle_double_vectors();
        } else if (data_type == 2) {
            handle_complex_vectors();
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
