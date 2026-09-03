#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "difficulty.h"

#define MAX_HIGHSCORES 10
#define HIGHSCORE_FILE "data/highscore.txt"

typedef struct {
    char name[50];
    int score;
    int total_questions;
    Difficulty difficulty;
    char date[20];
} HighScore;

void load_highscores(HighScore *scores, int *count);
void save_highscore(HighScore score);
void display_highscores();
int is_highscore(int score, Difficulty diff);
void sort_highscores(HighScore *scores, int count);

#endif