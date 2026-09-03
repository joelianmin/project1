#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include "question.h"

typedef enum {
    EASY,
    MEDIUM,
    HARD
} Difficulty;

typedef struct {
    Difficulty level;
    int min_num;
    int max_num;
    const char* name;
    Operator allowed_ops[4];
    int ops_count;
} DifficultyConfig;

DifficultyConfig get_difficulty_config(Difficulty diff);
Operator get_random_operator(Difficulty diff);
int get_random_int(int min, int max);
const char* difficulty_to_string(Difficulty diff);

#endif