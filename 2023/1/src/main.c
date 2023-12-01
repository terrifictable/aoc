#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "util/str.h"

#define INPUT "input.txt"


const char* num_words[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };


int main(void) {
    FILE* file = fopen(INPUT, "r");
    if (!file) {
        err("Failed to open '" INPUT "'");
        return 1;
    }
    
    int num = 0,
        num_p2 = 0;

    const int buf_len = 128;
    char *buf = calloc(buf_len+1, sizeof(char));    
    for (int i=1; fgets(buf, buf_len, file) != NULL; i++) {
        char* p = buf;

        str_t nums = str_new();
        str_t nums_p2 = str_new();
        for (; *p != '\n' && *p != '\0'; p++) {
            if (*p >= '0' && *p <= '9') {
                str_append(&nums, p, 1);
                str_append(&nums_p2, p, 1);
            }
        
            for (size_t wi = 0; wi < sizeof(num_words)/sizeof(*num_words); wi++) {
                if (strncmp(num_words[wi], p, strlen(num_words[wi])) == 0) {
                    str_appendf(&nums_p2, "%d", wi+1);
                }
            }
        }
        str_end(&nums, &nums_p2);

        char nstr[3] = {0};
        sprintf(nstr, "%c%c", *nums.str, *(nums.str + strlen(nums.str) - 1));
        num += atoi(nstr);
        // printf("-> (%d, %s) = %d + %d = %d\n", i, nstr, num, atoi(nstr), num + atoi(nstr));
        
        char nstr_p2[3] = {0};
        sprintf(nstr_p2, "%c%c", *nums_p2.str, *(nums_p2.str + strlen(nums_p2.str) - 1));
        num_p2 += atoi(nstr_p2);

        str_free(&nums, &nums_p2);
        memset(buf, 0, buf_len);
    }

    printf("===== PART 1 =====\n");
    printf("> Solution: %d\n", num);
    printf("===== PART 2 =====\n");
    printf("> Solution: %d\n", num_p2);

    free(buf);
    fclose(file);
    return 0;
}
