#include "logical_operations.h"

/* Binary transformation */
ptrmailli_rep2 transformation_binaire_ligne(ptrmailli_rep2 tete) {
    ptrmail_rep2 courant, nouveau, precedant;
    ptrmailli_rep2 resultat;
    ptrmailli_rep2 ligne_courante = tete;
    resultat = allouer_li_rep2();
    
    if (ligne_courante->suivcol != NULL) {
        courant = ligne_courante->suivcol;
    } else {
        resultat->suivcol = NULL;
        return resultat;
    }
    
    int cpt = 0;
    precedant = NULL;
    
    while (courant != NULL) {
        if (courant->val > 0) {
            nouveau = allouer_rep2();
            aff_val_rep2(nouveau, 1);
            nouveau->colo = courant->colo;
            if (cpt == 0) {
                resultat->suivcol = nouveau;
            } else {
                aff_adr_rep2(precedant, nouveau);
            }
            precedant = nouveau;
            cpt++;
        }
        courant = suiv_rep2(courant);
    }
    
    if (precedant != NULL) {
        aff_adr_rep2(precedant, NULL);
    } else {
        resultat->suivcol = NULL;
    }
    return resultat;
}

/* OR operations */
ptrmailli_rep2 or_entre_deux_lignes(ptrmailli_rep2 first, ptrmailli_rep2 second, int col) {
    int i;
    if (first->suivcol == NULL) {
        return transformation_binaire_ligne(second);
    } else if (second->suivcol == NULL) {
        return transformation_binaire_ligne(first);
    }
    
    bool existe1, existe2;
    ptrmailli_rep2 resultat;
    resultat = allouer_li_rep2();
    resultat->suivcol = NULL;
    ptrmail_rep2 courant, current_first, current_second;
    ptrmail_rep2 pre = NULL;
    
    for (i = 1; i <= col; i++) {
        current_first = rech_col_ptr_rep2(first, i, &existe1);
        current_second = rech_col_ptr_rep2(second, i, &existe2);
        
        if ((existe1 == true || existe2 == true)) {
            if (existe1 == true && existe2 == true) {
                if (current_first->val > 0 || current_second->val > 0) {
                    courant = allouer_rep2();
                    aff_val_rep2(courant, 1);
                    courant->colo = i;
                    if (resultat->suivcol == NULL) {
                        resultat->suivcol = courant;
                    } else {
                        aff_adr_rep2(pre, courant);
                    }
                    pre = courant;
                }
            } else if (existe1 == false && existe2 == true) {
                if (current_second->val > 0) {
                    courant = allouer_rep2();
                    aff_val_rep2(courant, 1);
                    courant->colo = i;
                    if (resultat->suivcol == NULL) {
                        resultat->suivcol = courant;
                    } else {
                        aff_adr_rep2(pre, courant);
                    }
                    pre = courant;
                }
            } else {
                if (current_first->val > 0) {
                    courant = allouer_rep2();
                    aff_val_rep2(courant, 1);
                    courant->colo = i;
                    if (resultat->suivcol == NULL) {
                        resultat->suivcol = courant;
                    } else {
                        aff_adr_rep2(pre, courant);
                    }
                    pre = courant;
                }
            }
        }
    }
    if (pre != NULL) {
        aff_adr_rep2(pre, NULL);
    }
    return resultat;
}

ptrmailli_rep2 or_operation(ptrmailli_rep2 first, ptrmailli_rep2 second, int ligne, int col) {
    int i;
    ptrmailli_rep2 ligne_courante_first = first;
    ptrmailli_rep2 ligne_courante_second = second;
    ptrmailli_rep2 result = or_entre_deux_lignes(ligne_courante_first, ligne_courante_second, col);
    ptrmailli_rep2 precedant = result;
    ptrmailli_rep2 current;
    
    for (i = 1; i < ligne; i++) {
        ligne_courante_first = suiv_li_rep2(ligne_courante_first);
        ligne_courante_second = suiv_li_rep2(ligne_courante_second);
        current = or_entre_deux_lignes(ligne_courante_first, ligne_courante_second, col);
        aff_adr_li_rep2(precedant, current);
        precedant = current;
    }
    return result;
}

/* NOT operations */
ptrmailli_rep2 non_ligne(ptrmailli_rep2 tete, int col) {
    int i;
    bool existe1;
    ptrmailli_rep2 resultat;
    resultat = allouer_li_rep2();
    resultat->suivcol = NULL;
    ptrmail_rep2 courant, current_first;
    ptrmail_rep2 pre = NULL;
    
    for (i = 1; i <= col; i++) {
        current_first = rech_col_ptr_rep2(tete, i, &existe1);
        if ((existe1 == false) || (existe1 == true && current_first->val <= 0)) {
            courant = allouer_rep2();
            aff_val_rep2(courant, 1);
            courant->colo = i;
            if (resultat->suivcol == NULL) {
                resultat->suivcol = courant;
            } else {
                aff_adr_rep2(pre, courant);
            }
            pre = courant;
        }
    }
    if (pre != NULL) {
        aff_adr_rep2(pre, NULL);
    }
    return resultat;
}

ptrmailli_rep2 non_operation(ptrmailli_rep2 first, int ligne, int col) {
    int i;
    ptrmailli_rep2 ligne_courante = first;
    ptrmailli_rep2 result = non_ligne(ligne_courante, col);
    ptrmailli_rep2 precedant = result;
    ptrmailli_rep2 current;
    
    for (i = 1; i < ligne; i++) {
        ligne_courante = suiv_li_rep2(ligne_courante);
        current = non_ligne(ligne_courante, col);
        aff_adr_li_rep2(precedant, current);
        precedant = current;
    }
    return result;
}

/* AND operations */
ptrmailli_rep2 and_entre_deux_lignes(ptrmailli_rep2 first, ptrmailli_rep2 second, int col) {
    int i;
    if (first->suivcol == NULL || second->suivcol == NULL) {
        ptrmailli_rep2 resultat;
        resultat = allouer_li_rep2();
        resultat->suivcol = NULL;
        return resultat;
    } else {
        bool existe1, existe2;
        ptrmailli_rep2 resultat;
        resultat = allouer_li_rep2();
        resultat->suivcol = NULL;
        ptrmail_rep2 courant, current_first, current_second;
        ptrmail_rep2 pre = NULL;
        
        for (i = 1; i <= col; i++) {
            current_first = rech_col_ptr_rep2(first, i, &existe1);
            current_second = rech_col_ptr_rep2(second, i, &existe2);
            if (existe1 == true && existe2 == true) {
                if (current_first->val > 0 && current_second->val > 0) {
                    courant = allouer_rep2();
                    aff_val_rep2(courant, 1);
                    courant->colo = i;
                    if (resultat->suivcol == NULL) {
                        resultat->suivcol = courant;
                    } else {
                        aff_adr_rep2(pre, courant);
                    }
                    pre = courant;
                }
            }
        }
        if (pre != NULL) {
            aff_adr_rep2(pre, NULL);
        }
        return resultat;
    }
}

ptrmailli_rep2 and_operation(ptrmailli_rep2 first, ptrmailli_rep2 second, int ligne, int col) {
    int i;
    ptrmailli_rep2 ligne_courante_first = first;
    ptrmailli_rep2 ligne_courante_second = second;
    ptrmailli_rep2 result = and_entre_deux_lignes(ligne_courante_first, ligne_courante_second, col);
    ptrmailli_rep2 precedant = result;
    ptrmailli_rep2 current;
    
    for (i = 1; i < ligne; i++) {
        ligne_courante_first = suiv_li_rep2(ligne_courante_first);
        ligne_courante_second = suiv_li_rep2(ligne_courante_second);
        current = and_entre_deux_lignes(ligne_courante_first, ligne_courante_second, col);
        aff_adr_li_rep2(precedant, current);
        precedant = current;
    }
    return result;
}

/* XOR operations */
ptrmailli_rep2 xor_entre_deux_lignes(ptrmailli_rep2 first, ptrmailli_rep2 second, int col) {
    int i;
    if (first->suivcol == NULL) {
        return transformation_binaire_ligne(second);
    } else if (second->suivcol == NULL) {
        return transformation_binaire_ligne(first);
    }
    
    bool existe1, existe2;
    ptrmailli_rep2 resultat;
    resultat = allouer_li_rep2();
    resultat->suivcol = NULL;
    ptrmail_rep2 courant, current_first, current_second;
    ptrmail_rep2 pre = NULL;
    
    for (i = 1; i <= col; i++) {
        current_first = rech_col_ptr_rep2(first, i, &existe1);
        current_second = rech_col_ptr_rep2(second, i, &existe2);
        
        if ((existe1 == true || existe2 == true)) {
            if (existe1 == true && existe2 == true) {
                if ((current_first->val <= 0 && current_second->val > 0) || 
                    (current_first->val > 0 && current_second->val <= 0)) {
                    courant = allouer_rep2();
                    aff_val_rep2(courant, 1);
                    courant->colo = i;
                    if (resultat->suivcol == NULL) {
                        resultat->suivcol = courant;
                    } else {
                        aff_adr_rep2(pre, courant);
                    }
                    pre = courant;
                }
            } else if (existe1 == false && existe2 == true) {
                if (current_second->val > 0) {
                    courant = allouer_rep2();
                    aff_val_rep2(courant, 1);
                    courant->colo = i;
                    if (resultat->suivcol == NULL) {
                        resultat->suivcol = courant;
                    } else {
                        aff_adr_rep2(pre, courant);
                    }
                    pre = courant;
                }
            } else {
                if (current_first->val > 0) {
                    courant = allouer_rep2();
                    aff_val_rep2(courant, 1);
                    courant->colo = i;
                    if (resultat->suivcol == NULL) {
                        resultat->suivcol = courant;
                    } else {
                        aff_adr_rep2(pre, courant);
                    }
                    pre = courant;
                }
            }
        }
    }
    if (pre != NULL) {
        aff_adr_rep2(pre, NULL);
    }
    return resultat;
}

ptrmailli_rep2 xor_operation(ptrmailli_rep2 first, ptrmailli_rep2 second, int ligne, int col) {
    int i;
    ptrmailli_rep2 ligne_courante_first = first;
    ptrmailli_rep2 ligne_courante_second = second;
    ptrmailli_rep2 result = xor_entre_deux_lignes(ligne_courante_first, ligne_courante_second, col);
    ptrmailli_rep2 precedant = result;
    ptrmailli_rep2 current;
    
    for (i = 1; i < ligne; i++) {
        ligne_courante_first = suiv_li_rep2(ligne_courante_first);
        ligne_courante_second = suiv_li_rep2(ligne_courante_second);
        current = xor_entre_deux_lignes(ligne_courante_first, ligne_courante_second, col);
        aff_adr_li_rep2(precedant, current);
        precedant = current;
    }
    return result;
}