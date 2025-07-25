#include "../src/sparse_matrix.h"
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

// Helper function to create a test matrix with specific values
ptrmailli_rep2 create_test_matrix_3x3() {
    ptrmailli_rep2 mat = creation_mat_rep2(3);
    
    // Add element (1,1) = 5
    ptrmail_rep2 element1 = allouer_rep2();
    element1->val = 5;
    element1->colo = 1;
    element1->suiv = NULL;
    ligne_rep2(mat, 1)->suivcol = element1;
    
    // Add element (1,3) = 3
    ptrmail_rep2 element2 = allouer_rep2();
    element2->val = 3;
    element2->colo = 3;
    element2->suiv = NULL;
    element1->suiv = element2;
    
    // Add element (2,2) = 7
    ptrmail_rep2 element3 = allouer_rep2();
    element3->val = 7;
    element3->colo = 2;
    element3->suiv = NULL;
    ligne_rep2(mat, 2)->suivcol = element3;
    
    return mat;
}

void test_matrix_creation() {
    printf("\n=== Testing Matrix Creation ===\n");
    
    ptrmailli_rep2 mat = creation_mat_rep2(3);
    ASSERT_TRUE(mat != NULL, "Matrix creation should succeed");
    
    // Test that all rows are initially empty
    ASSERT_TRUE(ligne_rep2(mat, 1)->suivcol == NULL, "Row 1 should be initially empty");
    ASSERT_TRUE(ligne_rep2(mat, 2)->suivcol == NULL, "Row 2 should be initially empty");
    ASSERT_TRUE(ligne_rep2(mat, 3)->suivcol == NULL, "Row 3 should be initially empty");
}

void test_element_search() {
    printf("\n=== Testing Element Search ===\n");
    
    ptrmailli_rep2 mat = create_test_matrix_3x3();
    bool exists;
    
    // Test existing elements
    ptrmail_rep2 found = rech_pos_ptr_rep2(mat, 1, 1, &exists);
    ASSERT_TRUE(exists && found->val == 5, "Should find element (1,1) = 5");
    
    found = rech_pos_ptr_rep2(mat, 3, 1, &exists);
    ASSERT_TRUE(exists && found->val == 3, "Should find element (1,3) = 3");
    
    found = rech_pos_ptr_rep2(mat, 2, 2, &exists);
    ASSERT_TRUE(exists && found->val == 7, "Should find element (2,2) = 7");
    
    // Test non-existing element
    found = rech_pos_ptr_rep2(mat, 2, 1, &exists);
    ASSERT_TRUE(!exists, "Should not find element (1,2)");
    
    found = rech_pos_ptr_rep2(mat, 1, 3, &exists);
    ASSERT_TRUE(!exists, "Should not find element (3,1)");
}

void test_line_operations() {
    printf("\n=== Testing Line Operations ===\n");
    
    ptrmailli_rep2 mat = create_test_matrix_3x3();
    
    // Test ligne_rep2 function
    ptrmailli_rep2 line1 = ligne_rep2(mat, 1);
    ptrmailli_rep2 line2 = ligne_rep2(mat, 2);
    ptrmailli_rep2 line3 = ligne_rep2(mat, 3);
    
    ASSERT_TRUE(line1 != NULL, "Should get first line");
    ASSERT_TRUE(line2 != NULL, "Should get second line");
    ASSERT_TRUE(line3 != NULL, "Should get third line");
    
    ASSERT_TRUE(line1->suivcol != NULL, "First line should have elements");
    ASSERT_TRUE(line2->suivcol != NULL, "Second line should have elements");
    ASSERT_TRUE(line3->suivcol == NULL, "Third line should be empty");
}

void test_extraction() {
    printf("\n=== Testing Matrix Extraction ===\n");
    
    ptrmailli_rep2 mat = create_test_matrix_3x3();
    
    // Extract submatrix from (1,1) to (2,2)
    ptrmailli_rep2 extracted = extract_matrice_rep2(mat, 1, 1, 2, 2);
    
    ASSERT_TRUE(extracted != NULL, "Extraction should succeed");
    
    bool exists;
    ptrmail_rep2 found = rech_pos_ptr_rep2(extracted, 1, 1, &exists);
    ASSERT_TRUE(exists && found->val == 5, "Extracted matrix should contain (1,1) = 5");
    
    found = rech_pos_ptr_rep2(extracted, 2, 2, &exists);
    ASSERT_TRUE(exists && found->val == 7, "Extracted matrix should contain (2,2) = 7");
}

int main() {
    printf("Running Basic Operations Tests...\n");
    
    test_matrix_creation();
    test_element_search();
    test_line_operations();
    test_extraction();
    
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