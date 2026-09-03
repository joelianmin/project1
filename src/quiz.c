#include <stdio.h>
#include <string.h>
#include "quiz.h"
#include "difficulty.h"

void init_quiz(Quiz *quiz, Difficulty diff, int num_questions, const char *name) {
    quiz->difficulty = diff;
    quiz->total_questions = num_questions;
    quiz->current_question = 0;
    quiz->correct_answers = 0;
    strncpy(quiz->player_name, name, sizeof(quiz->player_name) - 1);
    quiz->player_name[sizeof(quiz->player_name) - 1] = '\0';

    DifficultyConfig config = get_difficulty_config(diff);

    for (int i = 0; i < num_questions; i++) {
        int num1 = get_random_int(config.min_num, config.max_num);
        int num2 = 0;

        Operator op = get_random_operator(diff);

        if (op == OP_DIVIDE) {
            while (num2 == 0 || num1 % num2 != 0) {
                num1 = get_random_int(config.min_num, config.max_num);
                num2 = get_random_int(1, config.max_num / 2);
            }
        } else if (op == OP_SUBTRACT) {
            if (num1 < num2) {
                int temp = num1;
                num1 = num2;
                num2 = temp;
            }
        } else {
            num2 = get_random_int(config.min_num, config.max_num);
        }

        quiz->questions[i] = create_question(num1, num2, op);
    }
}

Question get_next_question(Quiz *quiz) {
    return quiz->questions[quiz->current_question];
}

int submit_answer(Quiz *quiz, int answer) {
    int correct = check_answer(quiz->questions[quiz->current_question], answer);
    if (correct) {
        quiz->correct_answers++;
    }
    quiz->current_question++;
    return correct;
}

int is_quiz_finished(Quiz *quiz) {
    return quiz->current_question >= quiz->total_questions;
}

void show_quiz_result(Quiz *quiz) {
    printf("\n=== HASIL ===\n");
    printf("Skor: %d/%d\n", quiz->correct_answers, quiz->total_questions);
    printf("Level: %s\n", difficulty_to_string(quiz->difficulty));

    if (quiz->correct_answers == quiz->total_questions) {
        printf("JUARA! Kamu pintar sekali!\n");
    } else if (quiz->correct_answers >= quiz->total_questions * 0.6) {
        printf("Bagus! Terus berlatih ya!\n");
    } else {
        printf("Semangat! Coba lagi nanti!\n");
    }
}