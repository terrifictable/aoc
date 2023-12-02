#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "util/str.h"

#define INPUT "input.txt"

int main(void) {
    FILE* file = fopen(INPUT, "r");
    if (!file) {
        err("Failed to open '" INPUT "'");
        return 1;
    }
    
    const int buf_len = 128;
    char *buf = calloc(buf_len+1, sizeof(char));
    for (int i=0; fgets(buf, buf_len, file) != NULL; i++) {
        printf("%s", buf);
    }


    free(buf);
    fclose(file);
    return 0;
}
