#include <stdio.h>

int main() {
    float angka1, angka2, hasil;
    int pilihan;

    printf("=== Kalkulator Sederhana ===\n");
    printf("1. Penjumlahan\n");
    printf("2. Pengurangan\n");
    printf("3. Perkalian\n");
    printf("4. Pembagian\n");
    printf("Pilihan (1-4): ");
    scanf("%d", &pilihan);

    printf("Masukkan angka pertama: ");
    scanf("%f", &angka1);
    printf("Masukkan angka kedua: ");
    scanf("%f", &angka2);

    switch(pilihan) {
        case 1:
            hasil = angka1 + angka2;
            printf("Hasil: %.2f + %.2f = %.2f\n", angka1, angka2, hasil);
            break;
        case 2:
            hasil = angka1 - angka2;
            printf("Hasil: %.2f - %.2f = %.2f\n", angka1, angka2, hasil);
            break;
        case 3:
            hasil = angka1 * angka2;
            printf("Hasil: %.2f * %.2f = %.2f\n", angka1, angka2, hasil);
            break;
        case 4:
            if(angka2 != 0) {
                hasil = angka1 / angka2;
                printf("Hasil: %.2f / %.2f = %.2f\n", angka1, angka2, hasil);
            } else {
                printf("Error: Tidak bisa dibagi dengan nol!\n");
            }
            break;
        default:
            printf("Pilihan tidak valid!\n");
    }

    return 0;
}
