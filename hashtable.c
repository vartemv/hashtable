/*
 * Tabulka s rozptýlenými položkami
 *
 * S využitím datových typů ze souboru hashtable.h a připravených koster
 * funkcí implementujte tabulku s rozptýlenými položkami s explicitně
 * zretězenými synonymy.
 *
 * Při implementaci uvažujte velikost tabulky HT_SIZE.
 */

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>


int HT_SIZE = MAX_HT_SIZE;

/*
 * Rozptylovací funkce která přidělí zadanému klíči index z intervalu
 * <0,HT_SIZE-1>. Ideální rozptylovací funkce by měla rozprostírat klíče
 * rovnoměrně po všech indexech. Zamyslete sa nad kvalitou zvolené funkce.
 */
int get_hash(char *key) {
    int result = 1;
    int length = strlen(key);
    for (int i = 0; i < length; i++) {
        result += key[i];
    }
    return (result % HT_SIZE);
}

/*
 * Inicializace tabulky — zavolá sa před prvním použitím tabulky.
 */
void ht_init(ht_table_t *table) {
    if (table == NULL)
        return;

    for (int i = 0; i < HT_SIZE; ++i) {
        (*table)[i] = NULL;
    }
}

/*
 * Vyhledání prvku v tabulce.
 *
 * V případě úspěchu vrací ukazatel na nalezený prvek; v opačném případě vrací
 * hodnotu NULL.
 */
ht_item_t *ht_search(ht_table_t *table, char *key) {
    int id = get_hash(key);
    ht_item_t *temp_item = (*table)[id];

    while (temp_item != NULL) {
        if (strcmp(temp_item->key,key) == 0)
            return temp_item;
        temp_item = temp_item->next;
    }

    return NULL;
}

/*
 * Vložení nového prvku do tabulky.
 *
 * Pokud prvek s daným klíčem už v tabulce existuje, nahraďte jeho hodnotu.
 *
 * Při implementaci využijte funkci ht_search. Pri vkládání prvku do seznamu
 * synonym zvolte nejefektivnější možnost a vložte prvek na začátek seznamu.
 */
void ht_insert(ht_table_t *table, char *key, float value) {
    ht_item_t *new_item = ht_search(table, key);
    int id = get_hash(key);

    if (new_item == NULL) {
            new_item = (ht_item_t *) malloc(sizeof(ht_item_t));
            new_item->next = (*table)[id];
            (*table)[id] = new_item;
            new_item->key = key;
            new_item->value = value;
//            (*table)[id]->next = NULL;
    } else {
        if (strcmp(new_item->key,key) == 0)
            new_item->value = value;
    }
//    void ht_insert(ht_table_t *table, char *key, float value) {
//        if (table == NULL || key == NULL)
//            return;
//
//        ht_item_t *active = ht_search(table, key);
//        if (active != NULL) {
//            active->value = value;
//        } else {
//            int index = get_hash(key);
//            ht_item_t *newElem = malloc(sizeof(ht_item_t));
//            if (newElem != NULL) {
//                newElem->key = key;
//                newElem->value = value;
//                newElem->next = (*table)[index];
//                (*table)[index] = newElem;
//            } else {
//                return;
//            }
//        }
//    }
}

/*
 * Získání hodnoty z tabulky.
 *
 * V případě úspěchu vrací funkce ukazatel na hodnotu prvku, v opačném
 * případě hodnotu NULL.
 *
 * Při implementaci využijte funkci ht_search.
 */
float *ht_get(ht_table_t *table, char *key) {
    ht_item_t *temp_item = ht_search(table, key);

    if (temp_item != NULL)
        return &temp_item->value;

    return NULL;
}

/*
 * Smazání prvku z tabulky.
 *
 * Funkce korektně uvolní všechny alokované zdroje přiřazené k danému prvku.
 * Pokud prvek neexistuje, funkce nedělá nic.
 *
 * Při implementaci NEPOUŽÍVEJTE funkci ht_search.
 */
//void ht_delete(ht_table_t *table, char *key) {
//    int id = get_hash(key);
//    ht_item_t *cursor = (*table)[id];
//    ht_item_t *tmp;
//
//    while(cursor != NULL){
//        if(cursor->key == key){
//            tmp = cursor;
//            cursor = cursor->next;
//            free(tmp);
//        }
//
//    }
//}
void ht_delete(ht_table_t *table, char *key) {
    ht_item_t *cursor;
    ht_item_t *previous;

    int id = get_hash(key);
    cursor = (*table)[id];

    if (strcmp(cursor->key,key) == 0) {
        (*table)[id] = cursor->next;
        free(cursor);
        return;
    } else {
        while (cursor != NULL) {
            if (strcmp(cursor->key,key) == 0) {
                previous->next = cursor->next;
                free(cursor);
                return;
            }
            previous = cursor;
            cursor = cursor->next;
        }
    }
}

/*
 * Smazání všech prvků z tabulky.
 *
 * Funkce korektně uvolní všechny alokované zdroje a uvede tabulku do stavu po
 * inicializaci.
 */
void ht_delete_all(ht_table_t *table) {
    ht_item_t *tmp;
    ht_item_t *cursor;

    for (int i = 0; i < HT_SIZE; ++i) {
        cursor = (*table)[i];

        while (cursor != NULL) {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        (*table)[i] = NULL;
    }
}
