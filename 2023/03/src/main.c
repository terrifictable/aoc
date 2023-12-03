#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "util/str.h"
#include "util/types.h"
#include "util/util.h"

#define INPUT "input.txt"

__attribute__((weak))
bool is_symbol(char c) { return !is_digit(c) && c != '.'; }

str_t get_adjacent(int, int, str_t lines[], int lines_count);

/* TODO: Part 2 */
int main(void) {
    FILE* file = fopen(INPUT, "r");
    if (!file) {
        err("Failed to open '" INPUT "'");
        return 1;
    }
    
    #define LINES_COUNT 155
    str_t lines[LINES_COUNT] = { str_new() };

    const int buf_len = 256;
    char *buf = calloc(buf_len+1, sizeof(char));
    for (int i=0; fgets(buf, buf_len, file) != NULL; i++) {
        char* cp = calloc(buf_len+1, sizeof(char));
        memcpy(cp, buf, buf_len);

        *strchr(cp, '\n') = 0;
        str_appends(&lines[i], cp);
        str_end(&lines[i], NULL);

        free(cp);
        memset(buf, 0, buf_len+1);
    }
    free(buf);
    fclose(file);

    int sum = 0;
    for (size_t i=0; i < LINES_COUNT && lines[i].str != NULL; i++) { 
        str_t num_str[32] = { str_new() };
        int n = 0;

        bool last_was_num = false,
             valid = false;
        for (size_t j=0; j < lines[i].len; j++) {
            char c = lines[i].str[j];
            
            if (is_digit(c)) {
                str_append(&num_str[n], &c, 1);
                last_was_num = true;

                str_t adjacent = get_adjacent(i, j, lines, LINES_COUNT-1);
                char* str = adjacent.str;
                for (; *str; str++) {
                    if (is_symbol(*str)) {
                        valid = true;
                        break;
                    }
                }
            }

            if (last_was_num && !is_digit(c)) {
                str_end(&num_str[n], NULL);
                if (valid) {
                    sum += atoi(num_str[n].str);                
                    n++;
                    valid = false;
                } else {
                    str_free(&num_str[n], NULL);
                    num_str[n] = str_new();
                }
                last_was_num = false;
            }
        }

        for (size_t x=0; x < 4; x++) {
            str_free(&num_str[x], NULL);
        }
    }

    printf("===== PART 1 =====\n");
    printf("> Solution: %d\n", sum);
    printf("===== PART 2 =====\n");
    printf("> Solution: \n");

    for (size_t i=0; i < LINES_COUNT; i++) { 
        str_free(&lines[i], NULL);
    }

    return 0;
}


str_t get_adjacent(int i, int j, str_t lines[], [[maybe_unused]] int lines_count) {
    str_t str = str_new();
    /* nw n ne
     *  w c  e
     * sw s se
     */
    
    char nw = '.',
         n  = '.',
         ne = '.', 
         e  = '.',
         se = '.',
         s  = '.', 
         sw = '.',
         w  = '.';
    
    str_t line = lines[i];
    char c = line.str[j];
    
    if (i-1 > 0) {
        n = lines[i-1].str[j];
        
        if (j-1 >= 0) 
            nw = lines[i-1].str[j-1];
        if (j+1 <= (int)lines[i-1].len)
            ne = lines[i-1].str[j+1];
    }
    if (j+1 <= (int)line.len)
        e = line.str[j+1];
    if (i+1 < lines_count && lines[i+1].str != NULL) {
        s = lines[i+1].str[j];
        // printf("s = lines[%d+1].str[%d]\n", i, j);

        if (j-1 >= 0) 
            // printf("sw = lines[%d+1].str[%d+1]\n", i, j);
            sw = lines[i+1].str[j-1];
        if (j+1 <= (int)lines[i+1].len)
            // printf("se = lines[%d+1].str[%d-1]\n", i, j);
            se = lines[i+1].str[j+1];
    }
    if (j-1 >= 0)
        w = line.str[j-1];

    // printf("[%d][%d] -> %c\n", i, j, c);
    // printf(" %c | %c | %c\n", nw, n, ne);
    // printf("---|---|---\n");
    // printf(" %c | %c | %c\n", w, c, e);
    // printf("---|---|---\n");
    // printf(" %c | %c | %c\n", sw, s, se);

    str_appendf(&str, "%c%c%c", nw, n, ne);
    str_appendf(&str, "%c%c%c", w, c, e);
    str_appendf(&str, "%c%c%c", sw, s, se);

    str_end(&str, NULL);
    return str;
}
