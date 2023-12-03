#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "util/str.h"

#define INPUT "input.txt"

typedef int bool;
#define true 1
#define false 0


typedef struct _seg {
    int red;
    int green;
    int blue;
} seg_t;

typedef struct _game {
    str_t str;
    str_t segs[16];
    seg_t num_segs[16];
    int segs_count;

    int id;
    bool valid;
} game_t;


                 /* r   g   b  */
const int max[] = { 12, 13, 14 };

void solve_game(game_t* game);


int main(void) {
    FILE* file = fopen(INPUT, "r");
    if (!file) {
        err("Failed to open '" INPUT "'");
        return 1;
    }
    
    game_t games[128] = { {
        .str = str_new(),
        .segs = { str_new() },
        .segs_count = 0,

        .id = -1,
        .valid = false,
    } };

    const int buf_len = 256;
    char *buf = calloc(buf_len+1, sizeof(char));
    for (int i=0; fgets(buf, buf_len, file) != NULL; i++) {
        *strchr(buf, '\n') = 0; // remove newline

        games[i].id = i+1;
        str_appendf(&games[i].str, "%s", buf);
        str_end(&games[i].str, NULL);
        // printf("[%d] %s\n", games[i].id, games[i].str.str);

        char* cp = calloc(buf_len+1, sizeof(char));
        mempcpy(cp, buf, buf_len+1);
        
        int seg = 0;
        for (char* c = strchr(cp, ':')+2; *c != 0; c++) {
            if (*c == ';') {
                str_end(&games[i].segs[seg], NULL);
                // printf(" > seg %d: %s\n", seg+1, games[i].segs[seg].str);
                seg++; c++;
                continue;
            }
            str_appendf(&games[i].segs[seg], "%c", *c);
        }
        str_end(&games[i].segs[seg], NULL);
        // printf(" > seg %d: %s\n", seg+1, games[i].segs[seg].str);
        games[i].segs_count = seg+2;
        
        free(cp);
    }

    for (size_t i=0; i < sizeof(games)/sizeof(*games) && games[i].id != -1; i++) {
        solve_game(&games[i]);
    }

    int num = 0,
        sum = 0;
    for (size_t i=0; i < sizeof(games)/sizeof(*games); i++) {
        if (games[i].valid == true) {
            num += games[i].id;
        }

        seg_t max = { 0, 0, 0 };
        for (int j=0; j < games[i].segs_count; j++) {
            if (games[i].num_segs[j].red > max.red) {
                max.red = games[i].num_segs[j].red;
            }
            if (games[i].num_segs[j].green > max.green) {
                max.green = games[i].num_segs[j].green;
            }
            if (games[i].num_segs[j].blue > max.blue) {
                max.blue = games[i].num_segs[j].blue;
            }
        }

        int power = max.red * max.green * max.blue;
        sum += power;
        // printf("[%d] power: (%d * %d * %d) %d\n", games[i].id, max.red, max.green, max.blue, power);
    }


    printf("===== PART 1 =====\n");
    printf(" > Solution: %d\n", num);
    printf("===== PART 2 =====\n");
    printf(" > Solution: %d\n", sum);


    for (size_t i=0; i < sizeof(games)/sizeof(*games); i++) {
        str_free(&games[i].str, NULL);
        for (size_t j=0; j < sizeof(games[i].segs)/sizeof(*games[i].segs); j++) {
            str_free(&games[i].segs[j], NULL);
        }
    }

    free(buf);
    fclose(file);
    return 0;
}

seg_t parse_seg(str_t* seg_str) {
    seg_t seg = { 0, 0, 0 };

    char* cp = calloc(seg_str->len+1, sizeof(char));
    memcpy(cp, seg_str->str, seg_str->len);

    char* tok = strtok(cp, " ");
    int num;
    for (int i=0; tok; i++) {
        if (atoi(tok)) {
            num = atoi(tok);
        } else {
            if (strncmp(tok, "red", 3) == 0) {
                seg.red = num;
            } else if (strncmp(tok, "green", 5) == 0) {
                seg.green = num;
            } else if (strncmp(tok, "blue", 4) == 0) {
                seg.blue = num;
            }
        }

        tok = strtok(NULL, " ");
    }

    free(cp);
    return seg;
}

void solve_game(game_t* game) {
    bool f = false;
    for (int seg=0; seg < game->segs_count; seg++) {
        seg_t segment = parse_seg(&game->segs[seg]);


        if (segment.red > max[0] || segment.green > max[1] || segment.blue > max[2]) {
            game->valid = false;
            f = true;
        }
        game->num_segs[seg] = segment;
    }
    if (!f)
        game->valid = true;
}
