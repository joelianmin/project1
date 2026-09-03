#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "highscore.h"

void load_highscores(HighScore *scores, int *count) {
    FILE *file = fopen(HIGHSCORE_FILE, "r");
    *count = 0;

    if (file == NULL) {
        return;
    }

    while (*count < MAX_HIGHSCORES &&
           fscanf(file, "%49[^:]:%d:%d:%d:%19[^\n]",
                  scores[*count].name,
                  &scores[*count].score,
                  &scores[*count].total_questions,
                  (int*)&scores[*count].difficulty,
                  scores[*count].date) == 5) {
        (*count)++;
    }

    fclose(file);
    sort_highscores(scores, *count);
}

void save_highscore(HighScore score) {
    HighScore scores[MAX_HIGHSCORES];
    int count;

    load_highscores(scores, &count);

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(score.date, sizeof(score.date), "%Y-%m-%d %H:%M", t);

    if (count < MAX_HIGHSCORES) {
        scores[count] = score;
        count++;
    } else {
        if (score.score > scores[count-1].score) {
            scores[count-1] = score;
        }
    }

    sort_highscores(scores, count);

    FILE *file = fopen(HIGHSCORE_FILE, "w");
    if (file == NULL) {
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s:%d:%d:%d:%s\n",
                scores[i].name,
                scores[i].score,
                scores[i].total_questions,
                (int)scores[i].difficulty,
                scores[i].date);
    }

    fclose(file);
}

void sort_highscores(HighScore *scores, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[j].score > scores[i].score) {
                HighScore temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }
}

int is_highscore(int score, Difficulty diff) {
    (void)diff;
    HighScore scores[MAX_HIGHSCORES];
    int count;

    load_highscores(scores, &count);

    if (count < MAX_HIGHSCORES) {
        return 1;
    }

    return score > scores[count - 1].score;
}