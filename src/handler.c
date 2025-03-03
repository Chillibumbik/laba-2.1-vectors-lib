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
    
    // Устанавливаем typeInfo в зависимости от выбранного типа данных
    if (dataType == 1) {
        typeInfo = GetDoubleTypeInfo();
    } else if (dataType == 2) {
        typeInfo = GetComplexTypeInfo();
    } else if (dataType == 3) {
        typeInfo = GetIntTypeInfo();
    } else {
        printf("Invalid type selected!\n");
        return;
    }

    unsigned long long vectorSize;
    printf("Enter the size of the vectors: ");
    while (scanf("%llu", &vectorSize) != 1 || vectorSize <= 0) {
        printf("Invalid size. Please enter a positive integer: ");
        while(getchar() != '\n'); // Очистка буфера
    }

    // Выделяем память для векторов
    void* vector1 = malloc(typeInfo->size * vectorSize);
    void* vector2 = malloc(typeInfo->size * vectorSize);

    // Ввод данных для первого вектора
    printf("Enter elements of the first vector:\n");
    for (unsigned long long i = 0; i < vectorSize; i++) {
        printf("Element %llu: ", i + 1);
        while (scanf("%lf", (char*)vector1 + i * typeInfo->size) != 1) {
            printf("Invalid input. Try again: ");
            while(getchar() != '\n');  // Очистка буфера
        }
    }

    // Ввод данных для второго вектора
    printf("Enter elements of the second vector:\n");
    for (unsigned long long i = 0; i < vectorSize; i++) {
        printf("Element %llu: ", i + 1);
        while (scanf("%lf", (char*)vector2 + i * typeInfo->size) != 1) {
            printf("Invalid input. Try again: ");
            while(getchar() != '\n');  // Очистка буфера
        }
    }

    // Вывод данных векторов
    printf("First vector:\n");
    for (unsigned long long i = 0; i < vectorSize; i++) {
        typeInfo->print((char*)vector1 + i * typeInfo->size);
        printf(" ");
    }
    printf("\n");

    printf("Second vector:\n");
    for (unsigned long long i = 0; i < vectorSize; i++) {
        typeInfo->print((char*)vector2 + i * typeInfo->size);
        printf(" ");
    }
    printf("\n");

    // Выбор операции
    int operation;
    printf("Select operation: 1 - Add, 2 - Scalar Product, 3 - Exit: ");
    while (scanf("%d", &operation) != 1 || operation < 1 || operation > 3) {
        printf("Invalid choice. Try again: ");
        while(getchar() != '\n');
    }

    // Выполнение выбранной операции
    if (operation == 1) {
        // Сложение векторов
        void* result = malloc(typeInfo->size * vectorSize);
        add_vectors(vector1, vector2, result);
        printf("Result of addition:\n");
        for (unsigned long long i = 0; i < vectorSize; i++) {
            typeInfo->print((char*)result + i * typeInfo->size);
            printf(" ");
        }
        printf("\n");
        free(result);
    } else if (operation == 2) {
        // Скалярное произведение
        double result = 0;
        multiply_vectors(vector1, vector2, &result);
        printf("Scalar product: %lf\n", result);
    }

    // Освобождение памяти
    free(vector1);
    free(vector2);
}
