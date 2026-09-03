#ifndef UI_H
#define UI_H

#include "question.h"
#include "difficulty.h"
#include "quiz.h"
#include "highscore.h"

#define BOX_WIDTH 50

#define UI_BOLD      1
#define UI_UNDERLINE 2
#define UI_PAIR_1    1
#define UI_PAIR_2    2
#define UI_PAIR_3    3
#define UI_PAIR_4    4
#define UI_PAIR_5    5

void init_ui();
void cleanup_ui();
void clear_screen();
void draw_box(int y, int x, int height, int width);
void print_centered(int y, const char *text, int width);
int menu_select(const char *title, const char *options[], int count);
void show_message(const char *title, const char *message);
int input_number(int y, int x, int max_digits);
void input_string(int y, int x, char *buffer, int max_len);
void show_question_ui(Question q, int question_num, int total, Difficulty diff);
int show_result_ui(int correct, int total, Difficulty diff);
void show_highscore_ui(HighScore *scores, int count);
void show_main_menu_ui();
Difficulty show_difficulty_menu_ui();
int show_num_questions_ui();
void show_about_ui();
int get_screen_lines();
int get_screen_cols();
int get_center_y(int height);
int get_center_x(int width);
int ui_getch();
void ui_refresh();
void ui_color_on(int pair);
void ui_color_off(int pair);
void ui_bold_on();
void ui_bold_off();
void ui_underline_on();
void ui_underline_off();

#endif