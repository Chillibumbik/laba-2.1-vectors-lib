#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handler.h"
#include "VectorErrors.h"
#include "Complex.h"
#include "Double.h"
#include "Integer.h"

void handleVectorOperations(int dataType) {
    TypeInfo* typeInfo = NULL;
    
    switch (dataType){
        case 1: //double 
            typeInfo = GetDoubleTypeInfo();
            break;
        case 2: //complex
            typeInfo = GetComplexTypeInfo();
            break;
        case 3: //integer
            typeInfo = GetIntTypeInfo();
            break;
        default:
            printf("Invalid type selected!\n");
            return;
    }

    int size;
    printf("Enter the size of the vectors: ");
    while (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid size. Please enter a positive integer: ");
        while (getchar() != '\n'); 
    }
    unsigned int vectorSize = (unsigned int)size;
    

    VectorErrors opResult;
    Vector* vector1 = createVector(typeInfo, NULL, vectorSize, &opResult);
    Vector* vector2 = createVector(typeInfo, NULL, vectorSize, &opResult);
    Vector* result = createVector(typeInfo, NULL, vectorSize, &opResult);

    if (!vector1 || !vector2 || !result) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("\nEnter elements of the first vector:\n");
    for (unsigned int i = 0; i < vectorSize; i++) {
        printf("Element %llu (for complex - {real imag}): ", i + 1);
        if (dataType == 2) { 
            double real, imag;
            while (scanf("%lf %lf", &real, &imag) != 2) {
                printf("Invalid input. Please enter both real and imaginary parts (real imag): ");
                while(getchar() != '\n');
            }
            Complex c = {real, imag};
            memcpy((char*)vector1->data + i * typeInfo->size, &c, typeInfo->size);
        } else if (dataType == 1) { 
            while (scanf("%lf", (double*)((char*)vector1->data + i * typeInfo->size)) != 1) {
                printf("Invalid input. Try again: ");
                while(getchar() != '\n');
            }
        } else if (dataType == 3) { 
            while (scanf("%d", (int*)((char*)vector1->data + i * typeInfo->size)) != 1) {
                printf("Invalid input. Try again: ");
                while(getchar() != '\n');
            }
        }
    }

    printf("\nEnter elements of the second vector:\n");
    for (unsigned int i = 0; i < vectorSize; i++) {
        printf("Element %llu (for complex - {real imag}): ", i + 1);
        if (dataType == 2) {
            double real, imag;
            while (scanf("%lf %lf", &real, &imag) != 2) {
                printf("Invalid input. Please enter both real and imaginary parts (real imag): ");
                while(getchar() != '\n');
            }
            Complex c = {real, imag};
            memcpy((char*)vector2->data + i * typeInfo->size, &c, typeInfo->size);
        } else if (dataType == 1) { 
            while (scanf("%lf", (double*)((char*)vector2->data + i * typeInfo->size)) != 1) {
                printf("Invalid input. Try again: ");
                while(getchar() != '\n');
            }
        } else if (dataType == 3) { 
            while (scanf("%d", (int*)((char*)vector2->data + i * typeInfo->size)) != 1) {
                printf("Invalid input. Try again: ");
                while(getchar() != '\n');
            }
        }
    }


    printf("\nFirst vector:\n");
    print_vector(vector1);

    printf("\nSecond vector:\n");
    print_vector(vector2);

    int operation;
    printf("\nSelect operation: 1 - Add, 2 - Scalar Product, 3 - Exit: ");
    while (scanf("%d", &operation) != 1 || operation < 1 || operation > 3) {
        printf("Invalid choice. Try again: ");
        while(getchar() != '\n');
    }

    if (operation == 1) {
        add_vectors(vector1, vector2, result);
        printf("Result of addition:\n");
        print_vector(result);
    } else if (operation == 2) {
        double scalarResult = 0;
        multiply_vectors(vector1, vector2, &scalarResult);
        printf("Scalar product: %lf\n", scalarResult);
    }

    free_vector(vector1);
    free_vector(vector2);
    free_vector(result);
}
