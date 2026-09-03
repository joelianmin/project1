#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

#define BOX_HEIGHT 15

void init_ui() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_WHITE);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
    }
}

void cleanup_ui() {
    endwin();
}

void clear_screen() {
    clear();
    refresh();
}

void draw_box(int y, int x, int height, int width) {
    attron(A_BOLD);
    mvaddch(y, x, ACS_ULCORNER);
    for (int i = 1; i < width - 1; i++) {
        mvaddch(y, x + i, ACS_HLINE);
    }
    mvaddch(y, x + width - 1, ACS_URCORNER);

    for (int i = 1; i < height - 1; i++) {
        mvaddch(y + i, x, ACS_VLINE);
        for (int j = 1; j < width - 1; j++) {
            mvaddch(y + i, x + j, ' ');
        }
        mvaddch(y + i, x + width - 1, ACS_VLINE);
    }

    mvaddch(y + height - 1, x, ACS_LLCORNER);
    for (int i = 1; i < width - 1; i++) {
        mvaddch(y + height - 1, x + i, ACS_HLINE);
    }
    mvaddch(y + height - 1, x + width - 1, ACS_LRCORNER);
    attroff(A_BOLD);
}

void print_centered(int y, const char *text, int width) {
    int len = strlen(text);
    int x = (width - len) / 2;
    mvprintw(y, x, "%s", text);
}

int menu_select(const char *title, const char *options[], int count) {
    int selected = 0;
    int key;

    while (1) {
        clear_screen();

        int start_y = (LINES - BOX_HEIGHT) / 2;
        int start_x = (COLS - BOX_WIDTH) / 2;

        draw_box(start_y, start_x, BOX_HEIGHT, BOX_WIDTH);

        attron(A_BOLD | COLOR_PAIR(5));
        print_centered(start_y + 2, title, BOX_WIDTH);
        attroff(A_BOLD | COLOR_PAIR(5));

        for (int i = 0; i < count; i++) {
            if (i == selected) {
                attron(A_BOLD | COLOR_PAIR(1));
                mvprintw(start_y + 5 + i, start_x + 5, "  > %s", options[i]);
                attroff(A_BOLD | COLOR_PAIR(1));
            } else {
                mvprintw(start_y + 5 + i, start_x + 5, "    %s", options[i]);
            }
        }

        print_centered(start_y + BOX_HEIGHT - 2, "Gunakan panah untuk memilih, ENTER untuk konfirmasi", BOX_WIDTH);

        refresh();

        key = getch();

        switch (key) {
            case KEY_UP:
                selected = (selected - 1 + count) % count;
                break;
            case KEY_DOWN:
                selected = (selected + 1) % count;
                break;
            case '\n':
            case KEY_ENTER:
                return selected;
            case 'q':
            case 'Q':
                return -1;
        }
    }
}

void show_message(const char *title, const char *message) {
    clear_screen();

    int msg_len = strlen(message);
    int title_len = strlen(title);
    int box_width = (msg_len > title_len ? msg_len : title_len) + 10;
    if (box_width < 30) box_width = 30;

    int start_y = (LINES - 8) / 2;
    int start_x = (COLS - box_width) / 2;

    draw_box(start_y, start_x, 8, box_width);

    attron(A_BOLD | COLOR_PAIR(4));
    print_centered(start_y + 2, title, box_width);
    attroff(A_BOLD | COLOR_PAIR(4));

    print_centered(start_y + 4, message, box_width);

    print_centered(start_y + 6, "Tekan ENTER untuk melanjutkan", box_width);

    refresh();
    getch();
}

int input_number(int y, int x, int max_digits) {
    char buffer[10] = {0};
    int pos = 0;
    int key;

    while (1) {
        mvprintw(y, x, "[%*s] ", max_digits, "");

        for (int i = 0; i < pos; i++) {
            mvprintw(y, x + 1 + i, "%c", buffer[i]);
        }

        refresh();
        key = getch();

        if (key >= '0' && key <= '9' && pos < max_digits) {
            buffer[pos++] = key;
        } else if (key == KEY_BACKSPACE || key == 127) {
            if (pos > 0) pos--;
        } else if (key == '\n' || key == KEY_ENTER) {
            return atoi(buffer);
        }
    }
}

void input_string(int y, int x, char *buffer, int max_len) {
    int pos = 0;
    int key;

    while (1) {
        mvprintw(y, x, "[%*s] ", max_len, "");

        for (int i = 0; i < pos; i++) {
            mvprintw(y, x + 1 + i, "%c", buffer[i]);
        }

        refresh();
        key = getch();

        if (key >= 32 && key <= 126 && pos < max_len) {
            buffer[pos++] = key;
        } else if (key == KEY_BACKSPACE || key == 127) {
            if (pos > 0) pos--;
        } else if (key == '\n' || key == KEY_ENTER) {
            buffer[pos] = '\0';
            return;
        }
    }
}

void show_question_ui(Question q, int question_num, int total, Difficulty diff) {
    clear_screen();

    int start_y = (LINES - 12) / 2;
    int start_x = (COLS - BOX_WIDTH) / 2;

    draw_box(start_y, start_x, 12, BOX_WIDTH);

    char header[100];
    snprintf(header, sizeof(header), "Soal %d dari %d", question_num, total);
    attron(A_BOLD | COLOR_PAIR(5));
    print_centered(start_y + 2, header, BOX_WIDTH);
    attroff(A_BOLD | COLOR_PAIR(5));

    char diff_str[20];
    snprintf(diff_str, sizeof(diff_str), "Level: %s", difficulty_to_string(diff));
    attron(COLOR_PAIR(4));
    print_centered(start_y + 3, diff_str, BOX_WIDTH);
    attroff(COLOR_PAIR(4));

    char question_display[100];
    snprintf(question_display, sizeof(question_display), "%s = ?", q.question_str);
    attron(A_BOLD | A_UNDERLINE);
    print_centered(start_y + 6, question_display, BOX_WIDTH);
    attroff(A_BOLD | A_UNDERLINE);

    print_centered(start_y + 8, "Masukkan jawaban kamu:", BOX_WIDTH);
}

int show_result_ui(int correct, int total, Difficulty diff) {
    clear_screen();

    int start_y = (LINES - 14) / 2;
    int start_x = (COLS - BOX_WIDTH) / 2;

    draw_box(start_y, start_x, 14, BOX_WIDTH);

    attron(A_BOLD | COLOR_PAIR(5));
    print_centered(start_y + 2, "HASIL AKHIR", BOX_WIDTH);
    attroff(A_BOLD | COLOR_PAIR(5));

    char score_str[50];
    snprintf(score_str, sizeof(score_str), "Skor: %d/%d", correct, total);
    attron(A_BOLD | COLOR_PAIR(2));
    print_centered(start_y + 4, score_str, BOX_WIDTH);
    attroff(A_BOLD | COLOR_PAIR(2));

    char diff_str[20];
    snprintf(diff_str, sizeof(diff_str), "Level: %s", difficulty_to_string(diff));
    print_centered(start_y + 5, diff_str, BOX_WIDTH);

    const char *status;
    if (correct == total) {
        status = "JUARA! Kamu pintar sekali!";
        attron(COLOR_PAIR(2));
    } else if (correct >= total * 0.6) {
        status = "Bagus! Terus berlatih ya!";
        attron(COLOR_PAIR(4));
    } else {
        status = "Semangat! Coba lagi nanti!";
        attron(COLOR_PAIR(3));
    }
    print_centered(start_y + 7, status, BOX_WIDTH);
    attroff(COLOR_PAIR(2) | COLOR_PAIR(3) | COLOR_PAIR(4));

    print_centered(start_y + 10, "1. Kembali ke Menu Utama", BOX_WIDTH);
    print_centered(start_y + 11, "2. Main Lagi", BOX_WIDTH);
    print_centered(start_y + 12, "3. Keluar", BOX_WIDTH);

    print_centered(start_y + BOX_HEIGHT - 2, "Pilih menu (1-3): ", BOX_WIDTH);

    refresh();
    return getch() - '0';
}

void show_highscore_ui(HighScore *scores, int count) {
    clear_screen();

    int start_y = (LINES - 18) / 2;
    int start_x = (COLS - BOX_WIDTH) / 2;

    draw_box(start_y, start_x, 18, BOX_WIDTH);

    attron(A_BOLD | COLOR_PAIR(5));
    print_centered(start_y + 2, "HIGH SCORE", BOX_WIDTH);
    attroff(A_BOLD | COLOR_PAIR(5));

    if (count == 0) {
        print_centered(start_y + 6, "Belum ada skor tersimpan", BOX_WIDTH);
    } else {
        for (int i = 0; i < count && i < 5; i++) {
            char score_line[100];
            snprintf(score_line, sizeof(score_line), "%d. %s - %d/%d (%s)",
                    i + 1, scores[i].name, scores[i].score,
                    scores[i].total_questions,
                    difficulty_to_string(scores[i].difficulty));
            print_centered(start_y + 4 + i, score_line, BOX_WIDTH);
        }
    }

    print_centered(start_y + BOX_HEIGHT - 2, "Tekan ENTER untuk kembali", BOX_WIDTH);

    refresh();
    getch();
}

void show_main_menu_ui() {
    clear_screen();

    int start_y = (LINES - 16) / 2;
    int start_x = (COLS - BOX_WIDTH) / 2;

    draw_box(start_y, start_x, 16, BOX_WIDTH);

    attron(A_BOLD | COLOR_PAIR(5));
    print_centered(start_y + 2, "KUIS MATH BUAT KAMU", BOX_WIDTH);
    attroff(A_BOLD | COLOR_PAIR(5));

    attron(COLOR_PAIR(4));
    print_centered(start_y + 3, "Selamat datang di kuis matematika!", BOX_WIDTH);
    attroff(COLOR_PAIR(4));

    print_centered(start_y + 5, "1. Mulai Quiz", BOX_WIDTH);
    print_centered(start_y + 6, "2. Pilih Level", BOX_WIDTH);
    print_centered(start_y + 7, "3. Lihat High Score", BOX_WIDTH);
    print_centered(start_y + 8, "4. Tentang", BOX_WIDTH);
    print_centered(start_y + 9, "5. Keluar", BOX_WIDTH);

    print_centered(start_y + 12, "Gunakan angka untuk memilih menu", BOX_WIDTH);
}

Difficulty show_difficulty_menu_ui() {
    clear_screen();

    int start_y = (LINES - 14) / 2;
    int start_x = (COLS - BOX_WIDTH) / 2;

    draw_box(start_y, start_x, 14, BOX_WIDTH);

    attron(A_BOLD | COLOR_PAIR(5));
    print_centered(start_y + 2, "PILIH LEVEL KESULITAN", BOX_WIDTH);
    attroff(A_BOLD | COLOR_PAIR(5));

    print_centered(start_y + 4, "1. MUDAH (angka 1-10, + -)", BOX_WIDTH);
    print_centered(start_y + 5, "2. SEDANG (angka 1-20, + - x)", BOX_WIDTH);
    print_centered(start_y + 6, "3. SULIT (angka 1-50, + - x /)", BOX_WIDTH);

    print_centered(start_y + 9, "Pilih level (1-3): ", BOX_WIDTH);

    refresh();
    int choice = getch() - '0';

    switch (choice) {
        case 1: return EASY;
        case 2: return MEDIUM;
        case 3: return HARD;
        default: return EASY;
    }
}

int show_num_questions_ui() {
    clear_screen();

    int start_y = (LINES - 10) / 2;
    int start_x = (COLS - BOX_WIDTH) / 2;

    draw_box(start_y, start_x, 10, BOX_WIDTH);

    attron(A_BOLD | COLOR_PAIR(5));
    print_centered(start_y + 2, "JUMLAH SOAL", BOX_WIDTH);
    attroff(A_BOLD | COLOR_PAIR(5));

    print_centered(start_y + 4, "Masukkan jumlah soal (5-20):", BOX_WIDTH);

    print_centered(start_y + 6, "Jumlah: ", BOX_WIDTH);
    refresh();

    return input_number(start_y + 6, start_x + 20, 2);
}

void show_about_ui() {
    clear_screen();

    int start_y = (LINES - 12) / 2;
    int start_x = (COLS - BOX_WIDTH) / 2;

    draw_box(start_y, start_x, 12, BOX_WIDTH);

    attron(A_BOLD | COLOR_PAIR(5));
    print_centered(start_y + 2, "TENTANG PROGRAM", BOX_WIDTH);
    attroff(A_BOLD | COLOR_PAIR(5));

    print_centered(start_y + 4, "Kuis Math Buat Kamu", BOX_WIDTH);
    print_centered(start_y + 5, "Versi 1.0", BOX_WIDTH);
    print_centered(start_y + 7, "Program kuis matematika", BOX_WIDTH);
    print_centered(start_y + 8, "untuk anak-anak", BOX_WIDTH);
    print_centered(start_y + 10, "Dibuat dengan C dan ncurses", BOX_WIDTH);

    print_centered(start_y + BOX_HEIGHT - 2, "Tekan ENTER untuk kembali", BOX_WIDTH);

    refresh();
    getch();
}

int get_screen_lines() { return LINES; }
int get_screen_cols() { return COLS; }
int get_center_y(int height) { return (LINES - height) / 2; }
int get_center_x(int width) { return (COLS - width) / 2; }
int ui_getch() { return getch(); }
void ui_refresh() { refresh(); }
void ui_color_on(int pair) { attron(COLOR_PAIR(pair)); }
void ui_color_off(int pair) { attroff(COLOR_PAIR(pair)); }
void ui_bold_on() { attron(A_BOLD); }
void ui_bold_off() { attroff(A_BOLD); }
void ui_underline_on() { attron(A_UNDERLINE); }
void ui_underline_off() { attroff(A_UNDERLINE); }