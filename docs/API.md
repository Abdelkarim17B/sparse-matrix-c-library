# Sparse Matrix Library API Documentation

## Core Data Structures

### `struct maillon_rep2`
Represents a single non-zero element in the sparse matrix.
```c
struct maillon_rep2 {
    int val;                        // Value of the element
    int colo;                       // Column position (1-indexed)
    struct maillon_rep2 *suiv;      // Pointer to next element in the row
};
```

### `struct maillon_ligne`
Represents a row in the sparse matrix.
```c
struct maillon_ligne {
    struct maillon_ligne *suivli;   // Pointer to next row
    struct maillon_rep2 *suivcol;   // Pointer to first element in this row
};
```

### Type Definitions
```c
typedef struct maillon_ligne* ptrmailli_rep2;  // Pointer to row
typedef struct maillon_rep2* ptrmail_rep2;     // Pointer to element
```

## Memory Management

### `ptrmail_rep2 allouer_rep2(void)`
Allocates memory for a new matrix element.
- **Returns**: Pointer to allocated element

### `ptrmailli_rep2 allouer_li_rep2(void)`
Allocates memory for a new matrix row.
- **Returns**: Pointer to allocated row

## Basic Operations

### `void aff_adr_rep2(ptrmail_rep2 p, ptrmail_rep2 q)`
Links two matrix elements.
- **Parameters**:
  - `p`: Source element
  - `q`: Target element

### `void aff_val_rep2(ptrmail_rep2 p, int valeur)`
Sets the value of a matrix element.
- **Parameters**:
  - `p`: Element to modify
  - `valeur`: New value

### `void aff_adr_li_rep2(ptrmailli_rep2 p, ptrmailli_rep2 q)`
Links two matrix rows.
- **Parameters**:
  - `p`: Source row
  - `q`: Target row

## Traversal Functions

### `ptrmail_rep2 suiv_rep2(ptrmail_rep2 p)`
Gets the next element in a row.
- **Parameters**: `p` - Current element
- **Returns**: Next element or NULL

### `ptrmailli_rep2 suiv_li_rep2(ptrmailli_rep2 p)`
Gets the next row in the matrix.
- **Parameters**: `p` - Current row
- **Returns**: Next row or NULL

## Search Functions

### `ptrmail_rep2 rech_col_ptr_rep2(ptrmailli_rep2 tete, int col, bool *existe)`
Searches for an element in a specific column of a row.
- **Parameters**:
  - `tete`: Row to search in
  - `col`: Column number (1-indexed)
  - `existe`: Output parameter indicating if element was found
- **Returns**: Pointer to element if found, NULL otherwise

### `ptrmail_rep2 rech_pos_ptr_rep2(ptrmailli_rep2 tete, int col, int ligne, bool *existe)`
Searches for an element at a specific position in the matrix.
- **Parameters**:
  - `tete`: Matrix to search in
  - `col`: Column number (1-indexed)
  - `ligne`: Row number (1-indexed)
  - `existe`: Output parameter indicating if element was found
- **Returns**: Pointer to element if found, NULL otherwise

## Matrix Creation

### `ptrmailli_rep2 creation_matrice_rep2(int li, int col)`
Creates a sparse matrix with user input.
- **Parameters**:
  - `li`: Number of rows
  - `col`: Number of columns
- **Returns**: Pointer to created matrix

### `ptrmailli_rep2 creation_mat_rep2(int li)`
Creates an empty sparse matrix structure.
- **Parameters**: `li` - Number of rows
- **Returns**: Pointer to created matrix

## Display

### `void affichage_mat_rep2(ptrmailli_rep2 teteli, int li, int col)`
Displays the sparse matrix in a formatted way.
- **Parameters**:
  - `teteli`: Matrix to display
  - `li`: Number of rows
  - `col`: Number of columns

## Matrix Operations

### Addition
```c
ptrmailli_rep2 addition_ligne_rep2(ptrmailli_rep2 first, ptrmailli_rep2 second);
ptrmailli_rep2 addition_deux_matrice_rep2(ptrmailli_rep2 first, ptrmailli_rep2 second, int ligne);
```

### Multiplication
```c
ptrmailli_rep2 multiplication_rep2(ptrmailli_rep2 mat1, ptrmailli_rep2 mat2, 
                                   int ligne_1, int col_1, int ligne_2, int col_2);
```

### Transposition
```c
ptrmailli_rep2 transpose_rep2(ptrmailli_rep2 tete, int ligne, int col);
```

## Logical Operations

### OR Operation
```c
ptrmailli_rep2 or_operation(ptrmailli_rep2 first, ptrmailli_rep2 second, int ligne, int col);
```

### AND Operation
```c
ptrmailli_rep2 and_operation(ptrmailli_rep2 first, ptrmailli_rep2 second, int ligne, int col);
```

### XOR Operation
```c
ptrmailli_rep2 xor_operation(ptrmailli_rep2 first, ptrmailli_rep2 second, int ligne, int col);
```

### NOT Operation
```c
ptrmailli_rep2 non_operation(ptrmailli_rep2 first, int ligne, int col);
```

## Matrix Extraction

### `ptrmailli_rep2 extract_matrice_rep2(ptrmailli_rep2 tete, int ligne_dep, int col_dep, int ligne_arr, int col_arr)`
Extracts a submatrix from the original matrix.
- **Parameters**:
  - `tete`: Source matrix
  - `ligne_dep`: Starting row (1-indexed)
  - `col_dep`: Starting column (1-indexed)
  - `ligne_arr`: Ending row (1-indexed)
  - `col_arr`: Ending column (1-indexed)
- **Returns**: Pointer to extracted submatrix

## Matrix Division

### `void div_sous_mat_rep2(ptrmailli_rep2 mat, int sco, int sli, int ligne, int col)`
Divides a matrix into smaller submatrices and displays them.
- **Parameters**:
  - `mat`: Matrix to divide
  - `sco`: Submatrix column size
  - `sli`: Submatrix row size
  - `ligne`: Original matrix rows
  - `col`: Original matrix columns

## Utility Functions

### `ptrmailli_rep2 ligne_rep2(ptrmailli_rep2 tete, int ligne)`
Gets a specific row from the matrix.
- **Parameters**:
  - `tete`: Matrix
  - `ligne`: Row number (1-indexed)
- **Returns**: Pointer to the specified row

### `void last_element_rep2(ptrmailli_rep2 tete, ptrmail_rep2 *courant, int *type)`
Finds the last element in a row.
- **Parameters**:
  - `tete`: Row to search
  - `courant`: Output parameter for last element
  - `type`: Output parameter indicating element type

## Usage Examples

### Creating and Displaying a Matrix
```c
#include "sparse_matrix.h"

int main() {
    // Create a 3x3 matrix with user input
    ptrmailli_rep2 matrix = creation_matrice_rep2(3, 3);
    
    // Display the matrix
    affichage_mat_rep2(matrix, 3, 3);
    
    return 0;
}
```

### Matrix Addition
```c
#include "sparse_matrix.h"
#include "matrix_operations.h"

int main() {
    ptrmailli_rep2 mat1 = creation_matrice_rep2(3, 3);
    ptrmailli_rep2 mat2 = creation_matrice_rep2(3, 3);
    
    ptrmailli_rep2 result = addition_deux_matrice_rep2(mat1, mat2, 3);
    affichage_mat_rep2(result, 3, 3);
    
    return 0;
}
```

### Logical Operations
```c
#include "sparse_matrix.h"
#include "logical_operations.h"

int main() {
    ptrmailli_rep2 mat1 = creation_matrice_rep2(3, 3);
    ptrmailli_rep2 mat2 = creation_matrice_rep2(3, 3);
    
    ptrmailli_rep2 or_result = or_operation(mat1, mat2, 3, 3);
    ptrmailli_rep2 and_result = and_operation(mat1, mat2, 3, 3);
    ptrmailli_rep2 not_result = non_operation(mat1, 3, 3);
    
    return 0;
}
```

## Performance Notes

- **Space Complexity**: O(n) where n is the number of non-zero elements
- **Time Complexity**: 
  - Search operations: O(k) where k is the number of elements in a row
  - Addition: O(n + m) where n, m are non-zero elements in each matrix
  - Multiplication: O(n × m × p) in worst case
  - Logical operations: O(rows × cols) due to full matrix scan

## Memory Management Notes

- The library currently does not provide automatic memory deallocation functions
- Users should implement proper cleanup routines to avoid memory leaks
- Consider adding `free_matrix()` and `free_element()` functions for production use