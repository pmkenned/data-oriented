#include <stdio.h>
#include "pkcl.h"

/*
 * tests:
 *  create empty string
 *  concatenate two strings, compare result
 *  destroy string
 */

int main(int argc, char * argv[])
{
    size_t i;
    dyn_arr_t * my_arr = dyn_arr_make_cap(sizeof(int), 10);

    string_t * hello = string_make_from("hello, ");
    string_t * name = string_make_from("Paul");

    for (i=0; i<10; i++) {
        *((int*)my_arr->array+i) = i;
    }
    for (i=0; i<10; i++) {
        printf("%d, ", *((int*)my_arr->array+i));
    }
    printf("\n");

    printf("'%s' len: %ld, cap: %ld\n", hello->s, hello->len, hello->cap);
    printf("'%s' len: %ld, cap: %ld\n", name->s, name->len, name->cap);

    string_concat_existing(hello, name);
    printf("'%s' len: %ld, cap: %ld\n", hello->s, hello->len, hello->cap);

    string_destroy(hello);
    string_destroy(name);

    return 0;
}
