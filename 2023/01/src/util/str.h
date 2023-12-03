#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "common.h"


typedef struct _str_t {
    char* str;
    size_t len;
} str_t;

#define STR_INIT() { NULL, 0 }
#define nstr(s) str_news(s)

str_t str_new();
str_t str_news(char* s);
void str_append(str_t *str, char* s, int len);
void str_appends(str_t *str, char* s);
void str_appendf(str_t *str, char* fmt, ...);
void str_end(str_t* str, ...);
void str_free(str_t* str, ...);
