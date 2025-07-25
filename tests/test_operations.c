#include "../src/sparse_matrix.h"
#include "../src/matrix_operations.h"
#include <assert.h>

// Simple test framework
int tests_run = 0;
int tests_passed = 0;

#define ASSERT_TRUE(condition, message) \
    tests_run++; \
    if (condition) { \
        tests_passed++; \
        printf("✓ %s\n", message); \
    } else { \
        printf("✗ %s\n", message); \
    }

// Helper function to create test matrices
ptrmailli_rep2 create_test_matrix_2x2_1() {
    ptrmailli_rep2 mat = creation_mat_rep2(2);
    
    // Matrix: [1 2]
    //         [3 0]
    ptrmail_rep2 e11 = allouer_rep2();
    e11->val = 1; e11->colo = 1;
    ptrmail_rep2 e12 = allouer_rep2();
    e12->val = 2; e12->colo = 2;
    e11->suiv = e12; e12->suiv = NULL;
    ligne_rep2(mat, 1)->suivcol = e11;
    
    ptrmail_rep2 e21 = allouer_rep2();
    e21->val = 3; e21->colo = 1; e21->suiv = NULL;
    ligne_rep2(mat, 2)->suivcol = e21;
    
    return mat;
}

ptrmailli_rep2 create_test_matrix_2x2_2() {
    ptrmailli_rep2 mat = creation_mat_rep2(2);
    
    // Matrix: [0 1]
    //         [2 3]
    ptrmail_rep2 e12 = allouer_rep2();
    e12->val = 1; e12->colo = 2; e12->suiv = NULL;
    ligne_rep2(mat, 1)->suivcol = e12;
    
    ptrmail_rep2 e21 = allouer_rep2();
    e21->val = 2; e21->colo = 1;
    ptrmail_rep2 e22 = allouer_rep2();
    e22->val = 3; e22->colo = 2;
    e21->suiv = e22; e22->suiv = NULL;
    ligne_rep2(mat, 2)->suivcol = e21;
    
    return mat;
}

void test_matrix_addition() {
    printf("\n=== Testing Matrix Addition ===\n");
    
    ptrmailli_rep2 mat1 = create_test_matrix_2x2_1();
    ptrmailli_rep2 mat2 = create_test_matrix_2x2_2();
    
    ptrmailli_rep2 result = addition_deux_matrice_rep2(mat1, mat2, 2);
    
    ASSERT_TRUE(result != NULL, "Addition should succeed");
    
    // Expected result: [1 3]
    //                 [5 3]
    bool exists;
    ptrmail_rep2 found;
    
    found = rech_pos_ptr_rep2(result, 1, 1, &exists);
    ASSERT_TRUE(exists && found->val == 1, "Result (1,1) should be 1");
    
    found = rech_pos_ptr_rep2(result, 2, 1, &exists);
    ASSERT_TRUE(exists && found->val == 3, "Result (1,2) should be 3");
    
    found = rech_pos_ptr_rep2(result, 1, 2, &exists);
    ASSERT_TRUE(exists && found->val == 5, "Result (2,1) should be 5");
    
    found = rech_pos_ptr_rep2(result, 2, 2, &exists);
    ASSERT_TRUE(exists && found->val == 3, "Result (2,2) should be 3");
}

void test_matrix_multiplication() {
    printf("\n=== Testing Matrix Multiplication ===\n");
    
    ptrmailli_rep2 mat1 = create_test_matrix_2x2_1();
    ptrmailli_rep2 mat2 = create_test_matrix_2x2_2();
    
    ptrmailli_rep2 result = multiplication_rep2(mat1, mat2, 2, 2, 2, 2);
    
    ASSERT_TRUE(result != NULL, "Multiplication should succeed");
    
    // Expected result: [4 7]
    //                 [0 3]
    bool exists;
    ptrmail_rep2 found;
    
    found = rech_pos_ptr_rep2(result, 1, 1, &exists);
    ASSERT_TRUE(exists && found->val == 4, "Result (1,1) should be 4");
    
    found = rech_pos_ptr_rep2(result, 2, 1, &exists);
    ASSERT_TRUE(exists && found->val == 7, "Result (1,2) should be 7");
    
    found = rech_pos_ptr_rep2(result, 1, 2, &exists);
    ASSERT_TRUE(!exists, "Result (2,1) should be 0 (not stored)");
    
    found = rech_pos_ptr_rep2(result, 2, 2, &exists);
    ASSERT_TRUE(exists && found->val == 3, "Result (2,2) should be 3");
}

void test_matrix_transpose() {
    printf("\n=== Testing Matrix Transpose ===\n");
    
    ptrmailli_rep2 mat = create_test_matrix_2x2_1();
    ptrmailli_rep2 transposed = transpose_rep2(mat, 2, 2);
    
    ASSERT_TRUE(transposed != NULL, "Transpose should succeed");
    
    // Original: [1 2]    Transposed: [1 3]
    //          [3 0]                  [2 0]
    bool exists;
    ptrmail_rep2 found;
    
    found = rech_pos_ptr_rep2(transposed, 1, 1, &exists);
    ASSERT_TRUE(exists && found->val == 1, "Transposed (1,1) should be 1");
    
    found = rech_pos_ptr_rep2(transposed, 2, 1, &exists);
    ASSERT_TRUE(exists && found->val == 3, "Transposed (1,2) should be 3");
    
    found = rech_pos_ptr_rep2(transposed, 1, 2, &exists);
    ASSERT_TRUE(exists && found->val == 2, "Transposed (2,1) should be 2");
    
    found = rech_pos_ptr_rep2(transposed, 2, 2, &exists);
    ASSERT_TRUE(!exists, "Transposed (2,2) should be 0 (not stored)");
}

void test_invalid_multiplication() {
    printf("\n=== Testing Invalid Multiplication ===\n");
    
    // Create matrices with incompatible dimensions
    ptrmailli_rep2 mat1 = creation_mat_rep2(2); // 2x2
    ptrmailli_rep2 mat2 = creation_mat_rep2(3); // 3x3
    
    ptrmailli_rep2 result = multiplication_rep2(mat1, mat2, 2, 2, 3, 3);
    ASSERT_TRUE(result == NULL, "Invalid multiplication should return NULL");
}

int main() {
    printf("Running Matrix Operations Tests...\n");
    
    test_matrix_addition();
    test_matrix_multiplication();
    test_matrix_transpose();
    test_invalid_multiplication();
    
    printf("\n=== Test Results ===\n");
    printf("Tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);
    
    if (tests_passed == tests_run) {
        printf("All tests passed! ✓\n");
        return 0;
    } else {
        printf("Some tests failed! ✗\n");
        return 1;
    }
}