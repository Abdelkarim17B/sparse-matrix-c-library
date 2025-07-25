#include "matrix_operations.h"

/* Transposition */
ptrmailli_rep2 transpose_rep2(ptrmailli_rep2 tete, int ligne, int col) {
    int i, j;
    ptrmailli_rep2 nv_tete = creation_mat_rep2(col);
    for (i = 1; i <= col; ++i) {
        for (j = 1; j <= ligne; ++j) {
            aff_case_rep2(nv_tete, tete, j, i, i, j);
        }
    }
    return nv_tete;
}

/* Addition operations */
ptrmailli_rep2 addition_ligne_rep2(ptrmailli_rep2 first, ptrmailli_rep2 second) {
    ptrmail_rep2 current_first, current_second, current_result, precedant;
    ptrmailli_rep2 result;
    
    if (first->suivcol == NULL) {
        return second;
    } else if (second->suivcol == NULL) {
        return first;
    } else {
        result = allouer_li_rep2();
        current_result = allouer_rep2();
        result->suivcol = current_result;
        current_first = first->suivcol;
        current_second = second->suivcol;
        
        while (current_first != NULL && current_second != NULL) {
            if (current_first->colo == current_second->colo) {
                current_result->val = current_first->val + current_second->val;
                current_result->colo = current_first->colo;
                current_first = suiv_rep2(current_first);
                current_second = suiv_rep2(current_second);
            } else if (current_first->colo < current_second->colo) {
                current_result->val = current_first->val;
                current_result->colo = current_first->colo;
                current_first = suiv_rep2(current_first);
            } else {
                current_result->val = current_second->val;
                current_result->colo = current_second->colo;
                current_second = suiv_rep2(current_second);
            }
            precedant = current_result;
            current_result = allouer_rep2();
            aff_adr_rep2(precedant, current_result);
        }
        
        if (current_first == NULL) {
            while (current_second != NULL) {
                current_result->val = current_second->val;
                current_result->colo = current_second->colo;
                precedant = current_result;
                current_result = allouer_rep2();
                aff_adr_rep2(precedant, current_result);
                current_second = suiv_rep2(current_second);
            }
        }
        
        while (current_first != NULL) {
            current_result->val = current_first->val;
            current_result->colo = current_first->colo;
            precedant = current_result;
            current_result = allouer_rep2();
            aff_adr_rep2(precedant, current_result);
            current_first = suiv_rep2(current_first);
        }
    }
    return result;
}

ptrmailli_rep2 addition_deux_matrice_rep2(ptrmailli_rep2 first, ptrmailli_rep2 second, int ligne) {
    int i;
    ptrmailli_rep2 ligne_courante_first = first;
    ptrmailli_rep2 ligne_courante_second = second;
    ptrmailli_rep2 result = addition_ligne_rep2(ligne_courante_first, ligne_courante_second);
    ptrmailli_rep2 precedant = result;
    ptrmailli_rep2 current;
    
    for (i = 1; i < ligne; i++) {
        ligne_courante_first = suiv_li_rep2(ligne_courante_first);
        ligne_courante_second = suiv_li_rep2(ligne_courante_second);
        current = addition_ligne_rep2(ligne_courante_first, ligne_courante_second);
        aff_adr_li_rep2(precedant, current);
        precedant = current;
    }
    return result;
}

void addition_plusieur_matrice_rep2(ptrmailli_rep2 *result, int ligne, int col) {
    int n, i;
    printf("entrez le numero des matrices a additionner : ");
    scanf("%d", &n);
    ptrmailli_rep2 mat1;
    *result = creation_mat_rep2(ligne);
    
    for (i = 1; i <= n; i++) {
        printf("entrez les infos de la %d° matrice\n", i);
        mat1 = creation_matrice_rep2(ligne, col);
        *result = addition_deux_matrice_rep2(*result, mat1, ligne);
    }
}

/* Multiplication operations */
ptrmail_rep2 produit_rep2(ptrmailli_rep2 tete1, ptrmailli_rep2 tete2, int line, int col, bool *nulle) {
    ptrmail_rep2 result, courant, case_a_mutiplier;
    bool existe;
    
    if (ligne_rep2(tete1, line)->suivcol != NULL) {
        result = allouer_rep2();
        result->val = 0;
        courant = ligne_rep2(tete1, line)->suivcol;
        
        while (courant != NULL) {
            case_a_mutiplier = rech_col_ptr_rep2(ligne_rep2(tete2, courant->colo), col, &existe);
            if (existe == true) {
                result->val = result->val + courant->val * case_a_mutiplier->val;
            }
            courant = suiv_rep2(courant);
        }
        
        if (result->val != 0) {
            *nulle = false;
            return result;
        } else {
            *nulle = true;
            free(result);
            return NULL;
        }
    } else {
        *nulle = true;
        return NULL;
    }
}

ptrmailli_rep2 multiplication_rep2(ptrmailli_rep2 mat1, ptrmailli_rep2 mat2, int ligne_1, int col_1, int ligne_2, int col_2) {
    ptrmailli_rep2 resultat;
    ptrmail_rep2 current, maill;
    int type;
    bool nulle;
    
    if ((ligne_1 != col_2) && (col_2 != 1)) {
        printf("la multiplication est impossible\n");
        return NULL;
    } else if (col_2 == 1 && col_1 != ligne_2) {
        printf("la multiplication est impossible !\n");
        return NULL;
    } else {
        resultat = creation_mat_rep2(ligne_1);
        
        for (int i = 1; i <= ligne_1; ++i) {
            for (int j = 1; j <= col_2; ++j) {
                ptrmail_rep2 courant = produit_rep2(mat1, mat2, i, j, &nulle);
                if (nulle == false) {
                    last_element_rep2(ligne_rep2(resultat, i), &current, &type);
                    maill = allouer_rep2();
                    if (type == 0 || j == 1) {
                        ligne_rep2(resultat, i)->suivcol = maill;
                    } else {
                        aff_adr_rep2(current, maill);
                    }
                    maill->colo = j;
                    maill->val = courant->val;
                    aff_adr_rep2(maill, NULL);
                    free(courant);
                }
            }
        }
        return resultat;
    }
}