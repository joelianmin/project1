#include <stdlib.h>
#include <time.h>
#include "difficulty.h"

static int random_initialized = 0;

void ensure_random_initialized() {
    if (!random_initialized) {
        srand(time(NULL));
        random_initialized = 1;
    }
}

int get_random_int(int min, int max) {
    ensure_random_initialized();
    return min + rand() % (max - min + 1);
}

DifficultyConfig get_difficulty_config(Difficulty diff) {
    DifficultyConfig config;
    config.level = diff;

    switch (diff) {
        case EASY:
            config.min_num = 1;
            config.max_num = 10;
            config.name = "MUDAH";
            config.allowed_ops[0] = OP_ADD;
            config.allowed_ops[1] = OP_SUBTRACT;
            config.ops_count = 2;
            break;
        case MEDIUM:
            config.min_num = 1;
            config.max_num = 20;
            config.name = "SEDANG";
            config.allowed_ops[0] = OP_ADD;
            config.allowed_ops[1] = OP_SUBTRACT;
            config.allowed_ops[2] = OP_MULTIPLY;
            config.ops_count = 3;
            break;
        case HARD:
            config.min_num = 1;
            config.max_num = 50;
            config.name = "SULIT";
            config.allowed_ops[0] = OP_ADD;
            config.allowed_ops[1] = OP_SUBTRACT;
            config.allowed_ops[2] = OP_MULTIPLY;
            config.allowed_ops[3] = OP_DIVIDE;
            config.ops_count = 4;
            break;
    }

    return config;
}

Operator get_random_operator(Difficulty diff) {
    DifficultyConfig config = get_difficulty_config(diff);
    int idx = get_random_int(0, config.ops_count - 1);
    return config.allowed_ops[idx];
}

const char* difficulty_to_string(Difficulty diff) {
    switch (diff) {
        case EASY: return "MUDAH";
        case MEDIUM: return "SEDANG";
        case HARD: return "SULIT";
        default: return "TIDAK DIKETAHUI";
    }
}