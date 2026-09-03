#ifndef QUIZ_H
#define QUIZ_H

#include "question.h"
#include "difficulty.h"

#define MAX_QUESTIONS 20
#define DEFAULT_QUESTIONS 5

typedef struct {
    Question questions[MAX_QUESTIONS];
    int total_questions;
    int current_question;
    int correct_answers;
    Difficulty difficulty;
    char player_name[50];
} Quiz;

void init_quiz(Quiz *quiz, Difficulty diff, int num_questions, const char *name);
Question get_next_question(Quiz *quiz);
int submit_answer(Quiz *quiz, int answer);
int is_quiz_finished(Quiz *quiz);
void show_quiz_result(Quiz *quiz);

#endif