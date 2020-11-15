#include <stdio.h>
#include "pkcl.h"

typedef struct {
    string_t word;
    uint32_t count;
} word_count_t;

void get_line_from_file()
{
}

int main(int argc, char * argv[])
{
    size_t i, j;
    dyn_arr_t * word_count_arr = dyn_arr_make(sizeof(word_count_t));
    dyn_arr_t * tokens = NULL;

    string_t * line = string_make();
    get_line_from_file();
    tokens = string_split(line, " \n");

    for (i=0; i<tokens->num_items; i++) {
        string_t * token = (string_t *) tokens->array+i;
        int found = 0;

        for (j=0; j<word_count_arr->num_items; j++) {
            word_count_t * word_count_i = (word_count_t *) tokens->array+i;
            int equal = string_cmp_exact(word_count_i->word, token);
            if (equal) {
                found = 1;
                break;
            }
        }

        if (found) {
            ((word_count_t *) word_count_arr->array+i)->count++;
        } else {
            word_count_t new_word_count;
            new_word_count.word = string_make_cap(token->len+1);
            new_word_count.word = string_copy(token);
            new_word_count.count = 1;
            dyn_arr_append(word_count_arr, new_word_count);
        }
    }

    dyn_arr_destroy(word_count_arr);

    return 0;
}
