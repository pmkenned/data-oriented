#include "pkcl.h"

/* TODO:
 * linked list
 * hashmap
 * matrix
 * sparse matrix
 * vector
 * graph
 * networking
 */

/* TODO:
 * consider whether it is better to allocate objects on the heap
 * or to return copies of objects created on the stack
 */

dyn_arr_t * dyn_arr_make_cap(size_t item_size, size_t init_cap)
{
    dyn_arr_t * new_dyn_arr = malloc(sizeof(*new_dyn_arr));
    new_dyn_arr->cap = init_cap;
    new_dyn_arr->item_size = item_size;
    new_dyn_arr->num_items = 0;
    new_dyn_arr->array = (init_cap > 0) ? malloc(item_size*init_cap) : NULL;
    return new_dyn_arr;
}

dyn_arr_t * dyn_arr_make(size_t item_size)
{
    return dyn_arr_make_cap(item_size, DEFAULT_DYN_ARR_CAP);
}

void dyn_arr_append()
{
}

void dyn_arr_remove()
{
}

void dyn_arr_insert()
{
}

void dyn_arr_insert_sorted()
{
}

void dyn_arr_find()
{
}

void dyn_arr_sort()
{
}

void dyn_arr_destroy(dyn_arr_t * da)
{
    if (da->array != NULL) {
        free(da->array);
    }
    free(da);
}

string_t * string_make_cap(size_t init_cap)
{
    /* assert(init_cap > 0)? */
    string_t * new_str = malloc(sizeof(*new_str));
    new_str->len = 0;
    new_str->cap = init_cap;
    new_str->s = (init_cap > 0) ? malloc(sizeof(*new_str->s)*init_cap) : NULL;
    new_str->s[0] = '\0';
    return new_str;
}

/* TODO: decide whether to make this inline (static inline?) */
string_t * string_make()
{
    return string_make_cap(DEFAULT_STR_CAP);
}

string_t * string_make_from(const char * s)
{
    size_t len = strlen(s);
    size_t cap = len*1.5;
    string_t * new_str = string_make_cap(cap);
    new_str->len = len;
    new_str->cap = cap;
    strcpy(new_str->s, s);
    return new_str;
}

void string_concat_existing(string_t * s1, string_t * s2)
{
    size_t s1_len_orig = s1->len;
    s1->len += s2->len;
    if (s1->len >= s1->cap-1) {
        size_t new_cap = s1->len * 1.5; /* see: https://archive.li/Z2R8w */
        s1->cap = new_cap;
        s1->s = realloc(s1->s, sizeof(*s1->s)*new_cap);
    }
    strcpy(s1->s + s1_len_orig, s2->s);
}

string_t * string_concat_new(string_t * s1, string_t * s2)
{
    size_t new_len = s1->len + s2->len;
    size_t new_cap = new_len * 1.5;
    string_t * new_str = string_make_cap(new_cap);
    /* TODO: perform the string copies */
    return new_str;
}

int string_cmp_exact(string_t * s1, string_t * s2)
{
    return 0;
}

void string_copy(string_t * dst, string_t * src)
{
    /* TODO */
    if (dst->s == NULL) {
        dst->s = string_make_cap(src->cap);
    }
}

dyn_arr_t * string_split(string_t * s, const char * delim)
{
    return NULL;
}

void string_destroy(string_t * str)
{
    if (str == NULL)
        return;
    if (str->s != NULL) {
        free(str->s);
    }
    free(str);
}
