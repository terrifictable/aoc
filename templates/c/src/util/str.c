#include "str.h"

str_t str_new() {
    str_t str = {
        .str = NULL,
        .len = 0,
    };
    return str;
}

#define nstr(s) str_news(s)
str_t str_news(char* s) {
    str_t str = STR_INIT();
    str.str = calloc(strlen(s), sizeof(char));
    memcpy(str.str, s, strlen(s));
    str.len = strlen(s);
    return str;
}

void str_append(str_t *str, char* s, int len) {
    if (s == NULL) return;

    char* new_str = (char*) realloc(str->str, str->len + len);
    if (new_str == NULL) return;

    memcpy(&new_str[str->len], s, len);
    str->str = new_str;
    str->len += len;
}

void str_appends(str_t *str, char* s) {
    if (s == NULL) return;
    str_append(str, s, strlen(s));
}

void str_appendf(str_t *str, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    const int buf_len = 1024;
    char buf[buf_len];
    memset(buf, 0, buf_len); // 0 out buf
    vsprintf(buf, fmt, args);

    va_end(args);

    str_append(str, buf, strlen(buf));
}

void str_free(str_t *str) {
    free(str->str);
}
