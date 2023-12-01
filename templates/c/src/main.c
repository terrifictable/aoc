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
    
    const int buf_len = 1;
    char *buf = calloc(buf_len, sizeof(char));
    while (fread(buf, sizeof(char), buf_len, file)) {
        printf("%s", buf);
    }


    free(buf);
    fclose(file);
    return 0;
}
