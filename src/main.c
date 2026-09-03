#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "quiz.h"
#include "difficulty.h"
#include "highscore.h"

int main() {
    init_ui();

    Difficulty current_difficulty = EASY;
    int running = 1;

    while (running) {
        show_main_menu_ui();
        int choice = ui_getch() - '0';

        switch (choice) {
            case 1: {
                char player_name[50] = {0};

                clear_screen();
                int start_y = get_center_y(10);
                int start_x = get_center_x(BOX_WIDTH);

                draw_box(start_y, start_x, 10, BOX_WIDTH);

                ui_bold_on();
                ui_color_on(UI_PAIR_5);
                print_centered(start_y + 2, "MASUKKAN NAMA KAMU", BOX_WIDTH);
                ui_color_off(UI_PAIR_5);
                ui_bold_off();

                print_centered(start_y + 4, "Nama: ", BOX_WIDTH);
                ui_refresh();
                input_string(start_y + 4, start_x + 20, player_name, 30);

                if (strlen(player_name) == 0) {
                    strcpy(player_name, "Pemain");
                }

                int questions_to_ask = show_num_questions_ui();
                if (questions_to_ask < 5) questions_to_ask = 5;
                if (questions_to_ask > 20) questions_to_ask = 20;

                Quiz quiz;
                init_quiz(&quiz, current_difficulty, questions_to_ask, player_name);

                while (!is_quiz_finished(&quiz)) {
                    Question q = get_next_question(&quiz);

                    show_question_ui(q, quiz.current_question + 1, quiz.total_questions, quiz.difficulty);

                    int answer = input_number(
                        get_center_y(12) + 9,
                        get_center_x(BOX_WIDTH) + 20,
                        3
                    );

                    int correct = submit_answer(&quiz, answer);

                    clear_screen();
                    int sy = get_center_y(12);
                    int sx = get_center_x(BOX_WIDTH);

                    draw_box(sy, sx, 12, BOX_WIDTH);

                    if (correct) {
                        ui_bold_on();
                        ui_color_on(UI_PAIR_2);
                        print_centered(sy + 4, q.feedback_correct, BOX_WIDTH);
                        ui_color_off(UI_PAIR_2);
                        ui_bold_off();
                    } else {
                        ui_bold_on();
                        ui_color_on(UI_PAIR_3);
                        print_centered(sy + 4, q.feedback_wrong, BOX_WIDTH);
                        ui_color_off(UI_PAIR_3);
                        ui_bold_off();
                    }

                    print_centered(sy + 6, "Tekan ENTER untuk soal berikutnya...", BOX_WIDTH);
                    ui_refresh();
                    ui_getch();
                }

                int result_choice = show_result_ui(quiz.correct_answers, quiz.total_questions, quiz.difficulty);

                if (result_choice == 2) {
                    int questions_to_ask_new = show_num_questions_ui();
                    if (questions_to_ask_new < 5) questions_to_ask_new = 5;
                    if (questions_to_ask_new > 20) questions_to_ask_new = 20;
                } else if (result_choice == 3) {
                    running = 0;
                }
                break;
            }
            case 2: {
                current_difficulty = show_difficulty_menu_ui();
                show_message("INFO", "Level telah diubah!");
                break;
            }
            case 3: {
                HighScore scores[MAX_HIGHSCORES];
                int count;
                load_highscores(scores, &count);
                show_highscore_ui(scores, count);
                break;
            }
            case 4: {
                show_about_ui();
                break;
            }
            case 5: {
                running = 0;
                break;
            }
        }
    }

    cleanup_ui();
    return 0;
}