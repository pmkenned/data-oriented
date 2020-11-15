#ifndef PKCL_H
#define PKCL_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>

#define DEFAULT_STR_CAP 32
#define DEFAULT_DYN_ARR_CAP 16

#ifndef MAX
    #define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
    #define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

/* TODO:
 *   consider whether it is better to allocate objects on the heap or to return copies of objects created on the stack
 *   consider adding a compare function that checks for exact equivalence by compares len first and returning false if lengths differ
 */

typedef struct {
    void * array;
    size_t item_size;
    size_t num_items;
    size_t cap;
    uint8_t flags; /* TODO: sorted flag */
} dyn_arr_t;

dyn_arr_t * dyn_arr_make_cap(size_t item_size, size_t init_cap);
dyn_arr_t * dyn_arr_make(size_t item_size);
void        dyn_arr_append();
void        dyn_arr_remove();
void        dyn_arr_insert();
void        dyn_arr_insert_sorted();
void        dyn_arr_find();
void        dyn_arr_sort();
void        dyn_arr_destroy(dyn_arr_t * da);
/* TODO: dyn_arr_shrink_to_fit() */

typedef struct {
    char * s;
    size_t len; /* excluding null */
    size_t cap; /* includes null */
} string_t;

string_t *  string_make_cap(size_t init_cap);
string_t *  string_make();
string_t *  string_make_from(const char * s);
void        string_concat_existing(string_t * s1, string_t * s2);
string_t *  string_concat_new(string_t * s1, string_t * s2);
int         string_cmp_exact(string_t * s1, string_t * s2);
void        string_copy(string_t * dst, string_t * src);
dyn_arr_t * string_split(string_t * s, const char * delim);
void        string_destroy(string_t * str);

#endif
