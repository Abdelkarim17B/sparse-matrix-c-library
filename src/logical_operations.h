#ifndef LOGICAL_OPERATIONS_H
#define LOGICAL_OPERATIONS_H

#include "sparse_matrix.h"

/* Binary transformation */
ptrmailli_rep2 transformation_binaire_ligne(ptrmailli_rep2 tete);

/* OR operations */
ptrmailli_rep2 or_entre_deux_lignes(ptrmailli_rep2 first, ptrmailli_rep2 second, int col);
ptrmailli_rep2 or_operation(ptrmailli_rep2 first, ptrmailli_rep2 second, int ligne, int col);

/* AND operations */
ptrmailli_rep2 and_entre_deux_lignes(ptrmailli_rep2 first, ptrmailli_rep2 second, int col);
ptrmailli_rep2 and_operation(ptrmailli_rep2 first, ptrmailli_rep2 second, int ligne, int col);

/* XOR operations */
ptrmailli_rep2 xor_entre_deux_lignes(ptrmailli_rep2 first, ptrmailli_rep2 second, int col);
ptrmailli_rep2 xor_operation(ptrmailli_rep2 first, ptrmailli_rep2 second, int ligne, int col);

/* NOT operations */
ptrmailli_rep2 non_ligne(ptrmailli_rep2 tete, int col);
ptrmailli_rep2 non_operation(ptrmailli_rep2 first, int ligne, int col);

#endif /* LOGICAL_OPERATIONS_H */