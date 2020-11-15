#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define INIT_KEY_TABLE_CAP 10

/* TODO: decide whether values must each be the same size and type */

typedef struct {
    char ** key_table;
    size_t key_table_cap;
    char * value_table;
    size_t value_size;
} dict_t;

dict_t * dict_make();
size_t dict_hash(const char * s);
void * dict_get(dict_t * d, const char * k);
void * dict_add(dict_t * d, const char * k, int value);
void dict_remove(dict_t * d, const char * k);
void dict_destroy(dict_t * d);

/* TODO: may be efficient to simply return "copy" of local struct */
/* see: https://en.wikipedia.org/wiki/Copy_elision */
dict_t * dict_make(size_t value_size) {
    size_t i;
    dict_t * new_dict = malloc(sizeof(*new_dict));
    new_dict->key_table_cap = INIT_KEY_TABLE_CAP;
    new_dict->key_table = malloc(sizeof(*new_dict->key_table) * INIT_KEY_TABLE_CAP);
    for (i=0; i<INIT_KEY_TABLE_CAP; i++) {
        new_dict->key_table[i] = NULL;
    }
    new_dict->value_size = value_size;
    return NULL;
}

/* TODO: maybe should use ptrdiff_t */
size_t dict_hash(const char * s) {
    return 0;
}

void * dict_get(dict_t * d, const char * k) {
    return NULL;
}

void * dict_add(dict_t * d, const char * k, int value) {
    size_t idx = dict_hash(k);
    size_t k_l = strlen(k);
    d->key_table[idx] = malloc(sizeof(*d->key_table[idx]) * (k_l+1));
    strncpy(d->key_table[idx], k, k_l);
    memcpy(d->value_table+(idx*d->value_size), &value, d->value_size);
    return NULL;
}

void dict_remove(dict_t * d, const char * k) {
}

void dict_destroy(dict_t * d) {
    size_t i;
    for (i=0; i<d->key_table_cap; i++) {
        char * k = d->key_table[i];
        if (k != NULL) {
            free(k);
        }
    }
    free(d->key_table);
    free(d);
}

int main(int argc, char * argv[])
{
    dict_t * my_dict = dict_make(sizeof(int));

    dict_add(my_dict, "hi there", 2);

    printf("%p\n", (void *) my_dict);

    return 0;
}
