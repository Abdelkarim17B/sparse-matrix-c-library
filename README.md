# Sparse Matrix Operations in C

A comprehensive C library for sparse matrix operations using linked list representation. This implementation efficiently handles matrices with many zero elements by storing only non-zero values.

## Features

### Core Operations
- **Matrix Creation**: Create sparse matrices with user input or programmatically
- **Matrix Display**: Pretty-print matrices with proper formatting
- **Matrix Extraction**: Extract sub-matrices from larger matrices
- **Matrix Division**: Divide matrices into smaller sub-matrices

### Mathematical Operations
- **Addition**: Add two or multiple sparse matrices
- **Multiplication**: Multiply sparse matrices with dimension validation
- **Transposition**: Transpose sparse matrices efficiently

### Logical Operations
- **AND**: Logical AND operation between matrices
- **OR**: Logical OR operation between matrices  
- **XOR**: Logical XOR (exclusive OR) operation between matrices
- **NOT**: Logical NOT operation on matrices

## Project Structure

```
sparse-matrix-operations/
├── src/                    # Source code
│   ├── sparse_matrix.h     # Core data structures and basic operations
│   ├── sparse_matrix.c     # Implementation of basic matrix operations
│   ├── matrix_operations.h # Mathematical operations header
│   ├── matrix_operations.c # Mathematical operations implementation
│   ├── logical_operations.h # Logical operations header
│   ├── logical_operations.c # Logical operations implementation
│   └── main.c             # Example usage and testing
├── tests/                 # Test files
│   ├── test_basic.c       # Basic operations tests
│   ├── test_operations.c  # Mathematical operations tests
│   └── test_logical.c     # Logical operations tests
├── docs/                  # Documentation
│   └── API.md            # API documentation
├── Makefile              # Build configuration
└── README.md            # This file
```

## Building the Project

### Prerequisites
- GCC compiler
- Make utility

### Compilation
```bash
# Build the main program
make

# Build with debug information
make debug

# Run tests
make test

# Clean build files
make clean
```

## Usage

### Basic Example
```c
#include "src/sparse_matrix.h"
#include "src/matrix_operations.h"

int main() {
    // Create a 3x3 sparse matrix
    ptrmailli_rep2 matrix = creation_mat_rep2(3);
    
    // Display the matrix
    affichage_mat_rep2(matrix, 3, 3);
    
    // Perform operations...
    
    return 0;
}
```

### Interactive Matrix Creation
The program supports interactive matrix creation where you input only non-zero values:

```bash
./sparse_matrix
ENTRER [1,1] : 5
ENTRER [1,2] : 0
ENTRER [1,3] : 3
...
```

## Data Structure

The implementation uses a linked list representation:

- **Matrix Structure**: Each matrix is represented as a linked list of rows
- **Row Structure**: Each row contains a linked list of non-zero elements
- **Element Structure**: Each element stores its value and column position

This approach provides:
- **Memory Efficiency**: Only non-zero elements are stored
- **Dynamic Size**: Matrices can grow as needed
- **Fast Operations**: Optimized for sparse data

## Testing

The project includes comprehensive tests:

```bash
# Run all tests
make test

# Run specific test categories
./tests/test_basic
./tests/test_operations  
./tests/test_logical
```

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is open source and available under the [MIT License](LICENSE).

## Performance Characteristics

- **Space Complexity**: O(n) where n is the number of non-zero elements
- **Time Complexity**: 
  - Matrix addition: O(n + m) where n, m are non-zero elements in each matrix
  - Matrix multiplication: O(n × m × p) in worst case
  - Matrix transposition: O(n) where n is number of non-zero elements

## Known Limitations

- Input validation could be enhanced
- Memory deallocation functions not implemented
- Limited error handling in some edge cases

## Future Enhancements

- [ ] Add memory deallocation functions
- [ ] Implement matrix determinant calculation
- [ ] Add support for different numeric types
- [ ] Improve error handling and validation
- [ ] Add performance benchmarking tools

### Shoutout  
👯 **Binome**: [AbdelAziz Akeb](https://github.com/4zz0u4k) — *Collaborator on this work*  
