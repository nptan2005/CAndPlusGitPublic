#include <stdio.h>

void main()
{
    FILE *fp1, *fp2, *fpout;
    char sf1[50], sf2[50], sfout[50];
    int c;

    printf("\nNhap ten tap tin thu nhat : ");
    scanf("%s", &sf1);
    printf("\nNhap ten tap tin thu hai : ");
    scanf("%s", &sf2);
    printf("\nNhap ten tap tin ket qua : ");
    scanf("%s", &sfout);

    if ((fp1 = fopen(sf1, "r")) == NULL)
      fprintf(stderr, "Khong the mo tap tin %s\n", sf1);
    if ((fp2 = fopen(sf2, "r")) == NULL)
      fprintf(stderr, "Khong the mo tap tin %s\n", sf2);
    if ((fpout = fopen(sfout, "w")) == NULL)
      fprintf(stderr, "Khong the mo tap tin %s\n", sfout);

    while ((c = getc(fp1)) != EOF)
        putc(c, fpout);
    while ((c = getc(fp2)) != EOF)
        putc(c, fpout);
    fclose(fp1);
    fclose(fp2);
    fclose(fpout);

    printf("\nHoan tat! Nhan phim bat ky de ket thuc.");
    getch();
}