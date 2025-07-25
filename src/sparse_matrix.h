#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* Boolean definitions */
#define true 1
#define false 0

/* Data structure definitions */

/* Simple node containing values representing matrix cells */
struct maillon_rep2 {
    int val;
    int colo;
    struct maillon_rep2 *suiv;
};

/* Row nodes - each represents a matrix row */
struct maillon_ligne {
    struct maillon_ligne *suivli;
    struct maillon_rep2 *suivcol;
};

/* Type definitions */
typedef struct maillon_ligne* ptrmailli_rep2;
typedef struct maillon_rep2* ptrmail_rep2;

/* Basic memory management functions */
ptrmail_rep2 allouer_rep2(void);
ptrmailli_rep2 allouer_li_rep2(void);

/* Basic linking functions */
void aff_adr_rep2(ptrmail_rep2 p, ptrmail_rep2 q);
void aff_val_rep2(ptrmail_rep2 p, int valeur);
void aff_adr_li_rep2(ptrmailli_rep2 p, ptrmailli_rep2 q);

/* Traversal functions */
ptrmail_rep2 suiv_rep2(ptrmail_rep2 p);
ptrmailli_rep2 suiv_li_rep2(ptrmailli_rep2 p);

/* Search functions */
ptrmail_rep2 rech_col_ptr_rep2(ptrmailli_rep2 tete, int col, bool *existe);
ptrmail_rep2 rech_pos_ptr_rep2(ptrmailli_rep2 tete, int col, int ligne, bool *existe);

/* Matrix creation functions */
ptrmailli_rep2 creation_matrice_rep2(int li, int col);
ptrmailli_rep2 creation_mat_rep2(int li);

/* Display function */
void affichage_mat_rep2(ptrmailli_rep2 teteli, int li, int col);

/* Extraction functions */
ptrmailli_rep2 extract_ligne_rep2(ptrmailli_rep2 tete_ligne, int col_dep, int col_arr);
ptrmailli_rep2 extract_matrice_rep2(ptrmailli_rep2 tete, int ligne_dep, int col_dep, int ligne_arr, int col_arr);

/* Matrix division */
void div_sous_mat_rep2(ptrmailli_rep2 mat, int sco, int sli, int ligne, int col);

/* Utility functions */
ptrmailli_rep2 ligne_rep2(ptrmailli_rep2 tete, int ligne);
void last_element_rep2(ptrmailli_rep2 tete, ptrmail_rep2 *courant, int *type);
void aff_case_rep2(ptrmailli_rep2 nv_tete, ptrmailli_rep2 tete, int ligne_courante, int col_courante, int nv_ligne, int nv_col);

#endif /* SPARSE_MATRIX_H */