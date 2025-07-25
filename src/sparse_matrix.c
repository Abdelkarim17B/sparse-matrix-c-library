#include "sparse_matrix.h"

/* Basic memory management functions */
ptrmail_rep2 allouer_rep2(void) {
    return ((ptrmail_rep2)malloc(sizeof(struct maillon_rep2)));
}

ptrmailli_rep2 allouer_li_rep2(void) {
    return ((ptrmailli_rep2)malloc(sizeof(struct maillon_ligne)));
}

/* Linking functions */
void aff_adr_rep2(ptrmail_rep2 p, ptrmail_rep2 q) {
    p->suiv = q;
}

void aff_val_rep2(ptrmail_rep2 p, int valeur) {
    p->val = valeur;
}

void aff_adr_li_rep2(ptrmailli_rep2 p, ptrmailli_rep2 q) {
    p->suivli = q;
}

/* Traversal functions */
ptrmail_rep2 suiv_rep2(ptrmail_rep2 p) {
    return (p->suiv);
}

ptrmailli_rep2 suiv_li_rep2(ptrmailli_rep2 p) {
    return (p->suivli);
}

/* Search functions */
ptrmail_rep2 rech_col_ptr_rep2(ptrmailli_rep2 tete, int col, bool *existe) {
    *existe = false;
    if (tete->suivcol == NULL) {
        return NULL;
    } else {
        ptrmail_rep2 courant = tete->suivcol;
        while (*existe == false && courant != NULL) {
            if (courant->colo == col) {
                *existe = true;
                return courant;
            } else {
                courant = suiv_rep2(courant);
            }
        }
        return NULL;
    }
}

ptrmail_rep2 rech_pos_ptr_rep2(ptrmailli_rep2 tete, int col, int ligne, bool *existe) {
    ptrmailli_rep2 ligne_courante = tete;
    int i;
    for (i = 1; i <= ligne - 1; i++) {
        ligne_courante = suiv_li_rep2(ligne_courante);
    }
    return rech_col_ptr_rep2(ligne_courante, col, existe);
}

/* Matrix creation functions */
ptrmailli_rep2 creation_matrice_rep2(int li, int col) {
    ptrmail_rep2 tete, q, p;
    ptrmailli_rep2 teteli, qli, pli;
    int i, j, valeur;
    teteli = NULL;
    
    for (i = 1; i <= li; i++) {
        tete = NULL;
        for (j = 1; j <= col; j++) {
            printf("ENTRER [%d,%d] : ", i, j);
            scanf("%d", &valeur);
            if (valeur != 0) {
                p = allouer_rep2();
                if (tete == NULL) {
                    tete = p;
                } else {
                    aff_adr_rep2(q, p);
                }
                q = p;
                aff_val_rep2(p, valeur);
                (p->colo) = j;
            }
        }
        if (tete != NULL) {
            aff_adr_rep2(q, NULL);
        }
        
        pli = allouer_li_rep2();
        if (teteli == NULL) {
            teteli = pli;
        } else {
            aff_adr_li_rep2(qli, pli);
        }
        qli = pli;
        pli->suivcol = tete;
    }
    if (teteli != NULL) {
        aff_adr_li_rep2(qli, NULL);
    }
    return teteli;
}

ptrmailli_rep2 creation_mat_rep2(int li) {
    ptrmailli_rep2 teteli, qli, pli;
    int i;
    teteli = NULL;
    
    for (i = 1; i <= li; i++) {
        pli = allouer_li_rep2();
        pli->suivcol = NULL;
        if (teteli == NULL) {
            teteli = pli;
        } else {
            aff_adr_li_rep2(qli, pli);
        }
        qli = pli;
    }
    if (teteli != NULL) {
        aff_adr_li_rep2(qli, NULL);
    }
    return teteli;
}

/* Display function */
void affichage_mat_rep2(ptrmailli_rep2 teteli, int li, int col) {
    int i, j;
    ptrmail_rep2 p;
    ptrmailli_rep2 qli;
    qli = teteli;
    
    for (i = 1; i <= li; i++) {
        p = qli->suivcol;
        printf("\n");
        for (j = 1; j <= col; j++) {
            if (p != NULL) {
                if (p->colo == j) {
                    printf("|  %d  |", p->val);
                    if (suiv_rep2(p) != NULL) {
                        p = suiv_rep2(p);
                    }
                } else if ((suiv_rep2(p) == NULL) || (p->colo != j)) {
                    printf("|  0  |");
                }
            } else {
                printf("|  0  |");
            }
        }
        qli = suiv_li_rep2(qli);
    }
    printf("\n");
}

/* Extraction functions */
ptrmailli_rep2 extract_ligne_rep2(ptrmailli_rep2 tete_ligne, int col_dep, int col_arr) {
    ptrmailli_rep2 nv_tete;
    nv_tete = allouer_li_rep2();
    int cnd = 0;
    int pos = col_dep;
    bool existe = false;
    ptrmail_rep2 courant, first_existe_ptr_in_intervalle, current, p;
    
    if (tete_ligne->suivcol == NULL) {
        nv_tete->suivcol = NULL;
    } else {
        if ((tete_ligne->suivcol)->colo > col_arr) {
            nv_tete->suivcol = NULL;
        } else {
            while (existe == false && pos <= col_arr) {
                courant = rech_pos_ptr_rep2(tete_ligne, pos, 1, &existe);
                pos = pos + 1;
            }
            if (existe == false) {
                nv_tete->suivcol = NULL;
            } else {
                first_existe_ptr_in_intervalle = courant;
                current = allouer_rep2();
                current->colo = first_existe_ptr_in_intervalle->colo - col_dep + 1;
                current->val = first_existe_ptr_in_intervalle->val;
                nv_tete->suivcol = current;
                
                while (courant->colo <= col_arr && cnd == 0) {
                    if (suiv_rep2(courant) != NULL) {
                        courant = suiv_rep2(courant);
                        if (courant->colo <= col_arr) {
                            p = allouer_rep2();
                            p->val = courant->val;
                            p->colo = courant->colo - col_dep + 1;
                            aff_adr_rep2(current, p);
                            current = p;
                        }
                    } else {
                        cnd = 1;
                    }
                }
                aff_adr_rep2(current, NULL);
            }
        }
    }
    return nv_tete;
}

ptrmailli_rep2 extract_matrice_rep2(ptrmailli_rep2 tete, int ligne_dep, int col_dep, int ligne_arr, int col_arr) {
    ptrmailli_rep2 nv_tete, nv_ligne, line;
    int i, j;
    ptrmailli_rep2 ligne_courante = tete;
    
    for (j = 1; j <= ligne_dep - 1; ++j) {
        ligne_courante = suiv_li_rep2(ligne_courante);
    }
    
    nv_tete = extract_ligne_rep2(ligne_courante, col_dep, col_arr);
    line = nv_tete;
    
    for (i = 1; i <= ligne_arr - ligne_dep; ++i) {
        nv_ligne = extract_ligne_rep2(suiv_li_rep2(ligne_courante), col_dep, col_arr);
        aff_adr_li_rep2(line, nv_ligne);
        ligne_courante = suiv_li_rep2(ligne_courante);
        line = nv_ligne;
    }
    return nv_tete;
}

/* Matrix division */
void div_sous_mat_rep2(ptrmailli_rep2 mat, int sco, int sli, int ligne, int col) {
    int i, j;
    ptrmailli_rep2 tete;
    
    if (col % sco != 0) {
        printf("ERREUR CO");
    } else if (ligne % sli != 0) {
        printf("ERREUR li");
    } else {
        int extrco1;
        int extrli1 = 1;
        int extrco2;
        int extrli2 = sli;
        
        for (i = 1; i <= (ligne / sli); i++) {
            extrco2 = sco;
            extrco1 = 1;
            for (j = 1; j <= (col / sco); j++) {
                tete = extract_matrice_rep2(mat, extrli1, extrco1, extrli2, extrco2);
                affichage_mat_rep2(tete, sli, sco);
                extrco1 = extrco1 + sco;
                extrco2 = extrco2 + sco;
            }
            extrli1 = extrli1 + sli;
            extrli2 = extrli2 + sli;
        }
    }
}

/* Utility functions */
ptrmailli_rep2 ligne_rep2(ptrmailli_rep2 tete, int ligne) {
    ptrmailli_rep2 ligne_courant = tete;
    for (int i = 1; i < ligne; ++i) {
        ligne_courant = suiv_li_rep2(ligne_courant);
    }
    return ligne_courant;
}

void last_element_rep2(ptrmailli_rep2 tete, ptrmail_rep2 *courant, int *type) {
    if (tete->suivcol == NULL) {
        *type = 0;
    } else {
        *courant = tete->suivcol;
        while (suiv_rep2(*courant) != NULL) {
            *courant = suiv_rep2(*courant);
        }
        *type = 1;
    }
}

void aff_case_rep2(ptrmailli_rep2 nv_tete, ptrmailli_rep2 tete, int ligne_courante, int col_courante, int nv_ligne, int nv_col) {
    bool existe;
    int type;
    ptrmail_rep2 current, maill;
    ptrmail_rep2 courant = rech_pos_ptr_rep2(tete, col_courante, ligne_courante, &existe);
    
    if (existe == true) {
        last_element_rep2(ligne_rep2(nv_tete, nv_ligne), &current, &type);
        maill = allouer_rep2();
        if (type == 0 || nv_col == 1) {
            ligne_rep2(nv_tete, nv_ligne)->suivcol = maill;
        } else {
            aff_adr_rep2(current, maill);
        }
        maill->colo = nv_col;
        maill->val = courant->val;
        aff_adr_rep2(maill, NULL);
    }
}