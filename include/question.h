#ifndef QUESTION_H
#define QUESTION_H

typedef enum {
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE
} Operator;

typedef struct {
    int num1;
    int num2;
    Operator op;
    int answer;
    char question_str[50];
    char feedback_correct[100];
    char feedback_wrong[100];
} Question;

Question create_question(int num1, int num2, Operator op);
void display_question(Question q);
int check_answer(Question q, int user_answer);
const char* operator_to_string(Operator op);

#endif