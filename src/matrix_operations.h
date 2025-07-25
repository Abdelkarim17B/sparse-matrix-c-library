#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "sparse_matrix.h"

/* Transposition operations */
ptrmailli_rep2 transpose_rep2(ptrmailli_rep2 tete, int ligne, int col);

/* Addition operations */
ptrmailli_rep2 addition_ligne_rep2(ptrmailli_rep2 first, ptrmailli_rep2 second);
ptrmailli_rep2 addition_deux_matrice_rep2(ptrmailli_rep2 first, ptrmailli_rep2 second, int ligne);
void addition_plusieur_matrice_rep2(ptrmailli_rep2 *result, int ligne, int col);

/* Multiplication operations */
ptrmail_rep2 produit_rep2(ptrmailli_rep2 tete1, ptrmailli_rep2 tete2, int line, int col, bool *nulle);
ptrmailli_rep2 multiplication_rep2(ptrmailli_rep2 mat1, ptrmailli_rep2 mat2, int ligne_1, int col_1, int ligne_2, int col_2);

#endif /* MATRIX_OPERATIONS_H */