#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "question.h"

Question create_question(int num1, int num2, Operator op) {
    Question q;
    q.num1 = num1;
    q.num2 = num2;
    q.op = op;

    switch (op) {
        case OP_ADD:
            q.answer = num1 + num2;
            snprintf(q.question_str, sizeof(q.question_str), "%d + %d", num1, num2);
            snprintf(q.feedback_correct, sizeof(q.feedback_correct), "BENAR! Kamu hebat!");
            snprintf(q.feedback_wrong, sizeof(q.feedback_wrong), "Salah nih, jawabannya %d", q.answer);
            break;
        case OP_SUBTRACT:
            q.answer = num1 - num2;
            snprintf(q.question_str, sizeof(q.question_str), "%d - %d", num1, num2);
            snprintf(q.feedback_correct, sizeof(q.feedback_correct), "BENAR! Pintar sekali!");
            snprintf(q.feedback_wrong, sizeof(q.feedback_wrong), "Salah nih, jawabannya %d", q.answer);
            break;
        case OP_MULTIPLY:
            q.answer = num1 * num2;
            snprintf(q.question_str, sizeof(q.question_str), "%d x %d", num1, num2);
            snprintf(q.feedback_correct, sizeof(q.feedback_correct), "BENAR! Kamu jenius!");
            snprintf(q.feedback_wrong, sizeof(q.feedback_wrong), "Salah nih, jawabannya %d", q.answer);
            break;
        case OP_DIVIDE:
            q.answer = num1 / num2;
            snprintf(q.question_str, sizeof(q.question_str), "%d / %d", num1, num2);
            snprintf(q.feedback_correct, sizeof(q.feedback_correct), "BENAR! Mantap!");
            snprintf(q.feedback_wrong, sizeof(q.feedback_wrong), "Salah nih, jawabannya %d", q.answer);
            break;
    }

    return q;
}

void display_question(Question q) {
    printf("%s = ? ", q.question_str);
}

int check_answer(Question q, int user_answer) {
    return user_answer == q.answer;
}

const char* operator_to_string(Operator op) {
    switch (op) {
        case OP_ADD: return "+";
        case OP_SUBTRACT: return "-";
        case OP_MULTIPLY: return "x";
        case OP_DIVIDE: return "/";
        default: return "?";
    }
}