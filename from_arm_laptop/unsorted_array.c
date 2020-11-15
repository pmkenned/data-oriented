#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_LINE 1024

char * get_full_line(FILE * fp, char * line, size_t * line_cap)
{
    char buf[MAX_LINE];
    char * dest = NULL;
    size_t total_l = 0;
    line[0] = '\0';
    while(1) {
        size_t l;
        if (fgets(buf, MAX_LINE, fp) == NULL) {
            break;
        }
        l = strlen(buf);
        total_l += l;
        if (*line_cap < total_l) {
            *line_cap *= 2;
            /* fprintf(stderr, "reallocating to %ld\n", *line_cap); */
            line = realloc(line, sizeof(*line)*(*line_cap+1));
        }
        dest = line + total_l - l;
        /*strncat(dest, buf, l);*/
        memcpy(dest, buf, l);
        dest[l] = '\0';
        if (buf[l-1] == '\n') {
            break;
        }
    }
    if (total_l > 0) {
        return line;
    }
    return NULL;
}

/* TODO: consider including word length for formatting purposes */
/* TODO: think about SOA vs AOS */
typedef struct {
    char * word;
    uint32_t count;
} word_count_t;

int main(int argc, char * argv[])
{
    size_t line_cap = MAX_LINE;
    char * line = malloc(sizeof(*line)*(line_cap+1));
    word_count_t * word_counts = NULL;
    size_t word_count_cap = 1024;
    size_t num_words = 0;
    FILE * fp = NULL;
    size_t i;
    size_t cmp_cnt = 0;

    if (argc < 2) {
        fprintf(stderr, "usage: %s [FILE]\n", argv[0]);
        exit(0);
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        perror("unable to open file");
        exit(1);
    }

    word_counts = malloc(sizeof(*word_counts)*word_count_cap);
    while((line = get_full_line(fp, line, &line_cap)) != NULL) {
        const char * delim = " \n";
        char * token = strtok(line, delim);
        while(token != NULL) {
            size_t token_l = strlen(token);
            int found = 0;
            /*printf("%s\n", token);*/

            /* LINEAR SEARCH */
            for(i=0; i<num_words; i++) {
                cmp_cnt++;
                if (strcmp(word_counts[i].word, token) == 0) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                word_counts[i].count++;
            } else {
                num_words++;
                if (num_words > word_count_cap) {
                    word_count_cap *= 2;
                    word_counts = realloc(word_counts, sizeof(*word_counts) * word_count_cap);
                }
                word_counts[num_words-1].word = malloc(sizeof(char) * token_l);
                strncpy(word_counts[num_words-1].word, token, token_l);
                word_counts[num_words-1].count = 1;
            }
 
            token = strtok(NULL, delim);
        }
    }

    for (i=0; i<num_words; i++) {
        printf("%d %s\n", word_counts[i].count, word_counts[i].word);
    }

    fprintf(stderr, "%ld comparisons\n", cmp_cnt);

    fclose(fp);

    return 0;
}
