#include <stdio.h>

int main() {
    int angka1, angka2, jawaban, skor = 0;

    printf("=== KUIS MATH BUAT KAMU ===\n\n");
    printf("Siap berhitung? Ayo kita mulai!\n\n");

    // Soal 1
    angka1 = 3;
    angka2 = 4;
    printf("1. %d + %d = ? ", angka1, angka2);
    scanf("%d", &jawaban);
    if (jawaban == angka1 + angka2) {
        printf("BENAR! Kamu hebat!\n\n");
        skor++;
    } else {
        printf("Salah nih, jawabannya %d\n\n", angka1 + angka2);
    }

    // Soal 2
    angka1 = 10;
    angka2 = 5;
    printf("2. %d - %d = ? ", angka1, angka2);
    scanf("%d", &jawaban);
    if (jawaban == angka1 - angka2) {
        printf("BENAR! Pintar sekali!\n\n");
        skor++;
    } else {
        printf("Salah nih, jawabannya %d\n\n", angka1 - angka2);
    }

    // Soal 3
    angka1 = 2;
    angka2 = 3;
    printf("3. %d x %d = ? ", angka1, angka2);
    scanf("%d", &jawaban);
    if (jawaban == angka1 * angka2) {
        printf("BENAR! Kamu jenius!\n\n");
        skor++;
    } else {
        printf("Salah nih, jawabannya %d\n\n", angka1 * angka2);
    }

    // Soal 4
    angka1 = 8;
    angka2 = 2;
    printf("4. %d / %d = ? ", angka1, angka2);
    scanf("%d", &jawaban);
    if (jawaban == angka1 / angka2) {
        printf("BENAR! Mantap!\n\n");
        skor++;
    } else {
        printf("Salah nih, jawabannya %d\n\n", angka1 / angka2);
    }

    // Soal 5
    angka1 = 7;
    angka2 = 3;
    printf("5. %d + %d = ? ", angka1, angka2);
    scanf("%d", &jawaban);
    if (jawaban == angka1 + angka2) {
        printf("BENAR! Hebat!\n\n");
        skor++;
    } else {
        printf("Salah nih, jawabannya %d\n\n", angka1 + angka2);
    }

    // Hasil
    printf("=== HASIL SKOR KAMU ===\n");
    printf("Skor: %d dari 5\n\n", skor);

    if (skor == 5) {
        printf("JUARA! Kamu pintar sekali!\n");
    } else if (skor >= 3) {
        printf("Bagus! Terus berlatih ya!\n");
    } else {
        printf("Semangat! Coba lagi nanti!\n");
    }

    return 0;
}