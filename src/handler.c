#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handler.h"
#include "VectorErrors.h"
#include <math.h>

void startInterface() {
    unsigned int vector_count; 
    printf("Enter the number of vectors: ");
    while (scanf("%u", &vector_count) != 1 || vector_count < 1) {
        printf("Invalid input. Please select a positive number: ");
        while(getchar() != '\n');
    }
    VectorErrors operation_result;

    Vector** vectors = malloc(vector_count * sizeof(Vector*));
    for (unsigned int i = 0; i < vector_count; i++){
        int dataType;
        printf("Select data type:\n");
        printf("1 - Double\n2 - Complex\n3 - Integer\n");
        while (scanf("%d", &dataType) != 1 || dataType < 1 || dataType > 3) {
            printf("Invalid input. Please select a valid option (1, 2, 3): ");
            while(getchar() != '\n');
        }
    
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
        printf("Enter the size of the vector: ");
        while (scanf("%d", &size) != 1 || size <= 0) {
            printf("Invalid size. Please enter a positive integer: ");
            while (getchar() != '\n'); 
        }
        
        printf("Enter %d vector coordinates(for complex - {real imag})\n", i + 1);
        void* data = malloc(size * typeInfo->size);
        
        for (int j=0; j < size; j++){
            switch (dataType){
                case 1: //double 
                    while (scanf("%lf", (double*)((char*)data + j * typeInfo->size)) != 1) {
                        printf("Invalid choice. Try again: ");
                        while(getchar() != '\n');
                    }
                    break;
                case 2: //complex
                    Complex* z = (Complex*)((char*)data + j * typeInfo->size);
                    while (scanf("%lf %lf", &z->real, &z->imag) != 2) {
                        printf("Invalid choice. Try again: ");
                        while(getchar() != '\n');
                    }
                    break;
                case 3: //integer
                    while (scanf("%d", (int*)((char*)data + j * typeInfo->size)) != 1) {
                        printf("Invalid choice. Try again: ");
                        while(getchar() != '\n');
                    }
                    break;
            }   
        
        }
        vectors[i] = createVector(typeInfo, data, size, &operation_result);
        printf("Vector %d\n", i+1);
        print_vector(vectors[i]);
        printf("\n\n");

    }

        while(1){
            short operation;
            printf("\nSelect operation: 1 - Add, 2 - Scalar Product, 3 - Module, 4 - see list of vectors, 5 - change coordinates of vector, 6 - Exit: ");
            while (scanf("%d", &operation) != 1 || operation < 1 || operation > 6) {
                printf("Invalid choice. Try again: ");
                while(getchar() != '\n');
            }
            
            short index1, index2;
            switch (operation){
            case 1: // add
                printf("Choose vector's indexes (1 to %d): ", vector_count);
                while (scanf("%hd %hd", &index1, &index2) != 2 || index1 < 1 || index2 < 1 || index1 > vector_count || index2 > vector_count) {
                    printf("Invalid choice. Please enter numbers between 1 and %d: ", vector_count);
                    while(getchar() != '\n');
                }
                
                index1 -= 1;
                index2 -= 1;

                Vector* add_result = createVector(vectors[index1]->typeInfo, malloc(vectors[index1]->capacity * vectors[index1]->typeInfo->size), vectors[index1]->capacity, &operation_result);

                
                if(errors_handler(add_vectors(vectors[index1], vectors[index2], add_result))){
                    break;
                }else{ 
                printf("Result of addition of vectors %d and %d:\n", index1+1, index2+1);
                print_vector(add_result);
                printf("\n\n");
                }

                free_vector(add_result);
                
                break;
            case 2: // scalar
                printf("Choose vector's indexes (1 to %d): ", vector_count);
                while (scanf("%hd %hd", &index1, &index2) != 2 || index1 < 1 || index2 < 1 || index1 > vector_count || index2 > vector_count) {
                    printf("Invalid choice. Please enter numbers between 1 and %d: ", vector_count);
                    while(getchar() != '\n');
                }
                
                index1 -= 1;
                index2 -= 1;

                void* result = malloc(vectors[index1]->typeInfo->size);
                if(errors_handler(multiply_vectors(vectors[index1], vectors[index2], result))){
                    break;
                }else{
                printf("Scalar product of vectors %d and %d: ", index1+1, index2+1);
                vectors[index1]->typeInfo->print(result);
                }
                free(result);
                break;

            case 3: // module
                unsigned short number_of_vector;
                double pre_module = 0;
                printf("Select Vector: ");
                while (scanf("%u", &number_of_vector) != 1 || number_of_vector < 1){
                    printf("Invalid number. Please enter a positive number: ");
                    while(getchar() != '\n');
                }
                find_module(vectors[number_of_vector-1], &pre_module);
                double module = sqrt(pre_module);
                printf("The module of %u vector: %.2f\n\n", number_of_vector, module);
                break;
            
            case 4: // list of vectors
                for(unsigned int j=0; j<vector_count; j++){
                    print_vector(vectors[j]);
                    printf("\n");
                }
                break;
            
            case 5: // change vec coords
                printf("Select Vector: ");

                while (scanf("%d", &index1) != 1 || number_of_vector < 1){
                    printf("Invalid number. Please enter a positive number: ");
                    while(getchar() != '\n');
                }

                index1-=1;
                printf("Choose vector's %d type (1-double, 2-complex, 3-integer)\n", index1+1);
                int new_type;
                scanf("%d", &new_type);
                printf("Enter the size of vector %d\n", index1+1);
                int new_size;
                while (scanf("%d", &new_size) != 1 || new_size <= 0) {
                    printf("Invalid size. Please enter a positive integer: ");
                    while (getchar() != '\n'); 
                }
                TypeInfo* new_typeInfo = NULL;
                if(new_type==1){
                    new_typeInfo = GetDoubleTypeInfo();
                }
                if(new_type==2){
                    new_typeInfo = GetComplexTypeInfo();
                }
                if(new_type==3){
                    new_typeInfo = GetIntTypeInfo();
                }
                printf("Enter new coordinates of %d vector:\n", index1+1);
                void* new_coord = malloc(new_size * vectors[index1]->typeInfo->size);

                
                for (int j=0; j < new_size; j++){
                    switch (new_type){
                        case 1: //double 
                            while (scanf("%lf", (double*)((char*)new_coord + j * new_typeInfo->size)) != 1) {
                                printf("Invalid choice. Try again: ");
                                while(getchar() != '\n');
                            }
                            break;
                        case 2: //complex
                            Complex* z = (Complex*)((char*)new_coord + j * new_typeInfo->size);
                            while (scanf("%lf %lf", &z->real, &z->imag) != 1) {
                                printf("Invalid choice. Try again: ");
                                while(getchar() != '\n');
                            }
                            break;
                        case 3: //integer
                            while (scanf("%d", (int*)((char*)new_coord + j * new_typeInfo->size)) != 1) {
                                printf("Invalid choice. Try again: ");
                                while(getchar() != '\n');
                            }
                            break;
                    } 
                }  
                if(errors_handler(rewrite_vector(new_typeInfo, vectors[index1], new_size, new_coord))){
                    break;
                }
                
                printf("Changed vector %d\n", index1+1);
                print_vector(vectors[index1]);
                
                free(new_coord);
                break;
            
            case 6: // exit
                printf("Have a good day!\n");
                exit(0);
            }
    }

    
    for ( unsigned int i = 0; i < vector_count; i++) {
        free_vector(vectors[i]);
    }
    free(vectors);
}