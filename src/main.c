#include "sparse_matrix.h"
#include "matrix_operations.h"
#include "logical_operations.h"

void print_menu() {
    printf("\n=== Sparse Matrix Operations ===\n");
    printf("1. Create matrix and display\n");
    printf("2. Test matrix addition\n");
    printf("3. Test matrix multiplication\n");
    printf("4. Test matrix transposition\n");
    printf("5. Test matrix extraction\n");
    printf("6. Test logical operations\n");
    printf("7. Test matrix division\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

void test_creation_display() {
    printf("\n=== Matrix Creation and Display Test ===\n");
    int rows, cols;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    
    ptrmailli_rep2 mat = creation_matrice_rep2(rows, cols);
    printf("\nMatrix created:\n");
    affichage_mat_rep2(mat, rows, cols);
}

void test_addition() {
    printf("\n=== Matrix Addition Test ===\n");
    int rows = 3, cols = 3;
    
    printf("Enter first matrix (%dx%d):\n", rows, cols);
    ptrmailli_rep2 mat1 = creation_matrice_rep2(rows, cols);
    
    printf("Enter second matrix (%dx%d):\n", rows, cols);
    ptrmailli_rep2 mat2 = creation_matrice_rep2(rows, cols);
    
    printf("\nFirst matrix:\n");
    affichage_mat_rep2(mat1, rows, cols);
    
    printf("\nSecond matrix:\n");
    affichage_mat_rep2(mat2, rows, cols);
    
    ptrmailli_rep2 result = addition_deux_matrice_rep2(mat1, mat2, rows);
    printf("\nResult of addition:\n");
    affichage_mat_rep2(result, rows, cols);
}

void test_multiplication() {
    printf("\n=== Matrix Multiplication Test ===\n");
    int rows1 = 2, cols1 = 3, rows2 = 3, cols2 = 2;
    
    printf("Enter first matrix (%dx%d):\n", rows1, cols1);
    ptrmailli_rep2 mat1 = creation_matrice_rep2(rows1, cols1);
    
    printf("Enter second matrix (%dx%d):\n", rows2, cols2);
    ptrmailli_rep2 mat2 = creation_matrice_rep2(rows2, cols2);
    
    printf("\nFirst matrix:\n");
    affichage_mat_rep2(mat1, rows1, cols1);
    
    printf("\nSecond matrix:\n");
    affichage_mat_rep2(mat2, rows2, cols2);
    
    ptrmailli_rep2 result = multiplication_rep2(mat1, mat2, rows1, cols1, rows2, cols2);
    if (result != NULL) {
        printf("\nResult of multiplication:\n");
        affichage_mat_rep2(result, rows1, cols2);
    }
}

void test_transpose() {
    printf("\n=== Matrix Transposition Test ===\n");
    int rows = 3, cols = 4;
    
    printf("Enter matrix (%dx%d):\n", rows, cols);
    ptrmailli_rep2 mat = creation_matrice_rep2(rows, cols);
    
    printf("\nOriginal matrix:\n");
    affichage_mat_rep2(mat, rows, cols);
    
    ptrmailli_rep2 transposed = transpose_rep2(mat, rows, cols);
    printf("\nTransposed matrix:\n");
    affichage_mat_rep2(transposed, cols, rows);
}

void test_extraction() {
    printf("\n=== Matrix Extraction Test ===\n");
    int rows = 4, cols = 4;
    
    printf("Enter matrix (%dx%d):\n", rows, cols);
    ptrmailli_rep2 mat = creation_matrice_rep2(rows, cols);
    
    printf("\nOriginal matrix:\n");
    affichage_mat_rep2(mat, rows, cols);
    
    printf("\nExtracting submatrix from (2,2) to (4,4):\n");
    ptrmailli_rep2 extracted = extract_matrice_rep2(mat, 2, 2, 4, 4);
    affichage_mat_rep2(extracted, 3, 3);
}

void test_logical_operations() {
    printf("\n=== Logical Operations Test ===\n");
    int rows = 3, cols = 3;
    
    printf("Enter first matrix (%dx%d):\n", rows, cols);
    ptrmailli_rep2 mat1 = creation_matrice_rep2(rows, cols);
    
    printf("Enter second matrix (%dx%d):\n", rows, cols);
    ptrmailli_rep2 mat2 = creation_matrice_rep2(rows, cols);
    
    printf("\nFirst matrix:\n");
    affichage_mat_rep2(mat1, rows, cols);
    
    printf("\nSecond matrix:\n");
    affichage_mat_rep2(mat2, rows, cols);
    
    ptrmailli_rep2 or_result = or_operation(mat1, mat2, rows, cols);
    printf("\nOR result:\n");
    affichage_mat_rep2(or_result, rows, cols);
    
    ptrmailli_rep2 and_result = and_operation(mat1, mat2, rows, cols);
    printf("\nAND result:\n");
    affichage_mat_rep2(and_result, rows, cols);
    
    ptrmailli_rep2 xor_result = xor_operation(mat1, mat2, rows, cols);
    printf("\nXOR result:\n");
    affichage_mat_rep2(xor_result, rows, cols);
    
    ptrmailli_rep2 not_result = non_operation(mat1, rows, cols);
    printf("\nNOT result (first matrix):\n");
    affichage_mat_rep2(not_result, rows, cols);
}

void test_division() {
    printf("\n=== Matrix Division Test ===\n");
    int rows = 4, cols = 4;
    
    printf("Enter matrix (%dx%d):\n", rows, cols);
    ptrmailli_rep2 mat = creation_matrice_rep2(rows, cols);
    
    printf("\nOriginal matrix:\n");
    affichage_mat_rep2(mat, rows, cols);
    
    printf("\nDividing into 2x2 submatrices:\n");
    div_sous_mat_rep2(mat, 2, 2, rows, cols);
}

int main(void) {
    int choice;
    
    printf("Welcome to Sparse Matrix Operations Program!\n");
    
    do {
        print_menu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                test_creation_display();
                break;
            case 2:
                test_addition();
                break;
            case 3:
                test_multiplication();
                break;
            case 4:
                test_transpose();
                break;
            case 5:
                test_extraction();
                break;
            case 6:
                test_logical_operations();
                break;
            case 7:
                test_division();
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 0);
    
    return 0;
}