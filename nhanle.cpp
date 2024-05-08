#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

#define chieurong 90
#define chieudai 26
#define chieurongwin 70
#define menu 20
#define kichco 7

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD C;

int a[3];
int b[3];
int c[3];
char chim[2][6] = { {'/','-','-','o','\\',' '},
                    {'|','_','_','_',' ','>'} };
int n = 6;
int diem = 0;
void chon(int x, int y) {
    C.X = x;
    C.Y = y;
    SetConsoleCursorPosition(console, C);
}

void se(int visible, DWORD size) {
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO l;
    l.bVisible = visible;
    l.dwSize = size;
    SetConsoleCursorInfo(console, &l);
}

void khung() {
    for (int i = 0; i < chieurong; i++) {
        chon(i, 0); 
		printf("±");
        chon(i, chieudai); 
		printf("±");
    }

    for (int i = 0; i < chieudai; i++) {
        chon(0, i); 
		printf("±");
        chon(chieurong, i);
		 printf("±");
    }
    for (int i = 0; i < chieudai; i++) {
        chon(chieurongwin, i); 
		printf("±");
    }
}

void g(int ind) {
    b[ind] = 3 + rand() % 14;
}

void vecot(int ind) {
    if (c[ind] == 1) {
        for (int i = 0; i < b[ind]; i++) {
            chon(chieurongwin - a[ind], i + 1); 
			printf("III");
        }
        for (int i = b[ind] + kichco; i < chieudai - 1; i++) {
            chon(chieurongwin - a[ind], i + 1); 
			printf("III");
        }
    }
}

void xoacot(int ind) {
    if (c[ind] == 1) {
        for (int i = 0; i < b[ind]; i++) {
            chon(chieurongwin - a[ind], i + 1);
			 printf("   ");
        }
        for (int i = b[ind] + kichco; i < chieudai - 1; i++) {
            chon(chieurongwin - a[ind], i + 1);
			 printf("   ");
        }
    }
}

void vechim() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            chon(j + 2, i + n); 
			printf("%c", chim[i][j]);
        }
    }
}

void xoachim() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            chon(j + 2, i + n);
			 printf(" ");
        }
    }
}

int collision() {
    if (a[0] >= 61) {
        if (n < b[0] || n > b[0] + kichco) {
            return 1;
        }
    }
    return 0;
}

void gameover() {
    system("cls");
    printf("\n\n");
    printf("\t\t----------------------------------\n");
    printf("\t\t-------- Choi Ngu vc -------\n");
    printf("\t\t----------------------------------\n\n");
    printf("\t\tNhan phim bat ky de quay lai menu");
    getch();
}

void updatediem() {
    chon(chieurongwin + 7, 5); printf("Diem: %d\n", diem);
}

void m() {
    system("cls");
    printf("Huong dan\n");
    printf("----------------\n");
    printf(" Nhan phim cach de chim bay\n\n");
    printf("Nhan phim bat ky de quay lai menu");
    getch();
}

void play() {
    n = 6;
    diem = 0;
    c[0] = 1;
    c[1] = 0;
    a[0] = a[1] = 4;

    system("cls");
    khung();
    g(0);
    updatediem();

    chon(chieurongwin + 5, 2); printf("NHANLEE");
    chon(chieurongwin + 6, 4); printf("----------");
    chon(chieurongwin + 6, 6); printf("----------");
    chon(chieurongwin + 7, 12); printf("Dieu Khien ");
    chon(chieurongwin + 7, 13); printf("---------- ");
    chon(chieurongwin + 2, 14); printf(" Phim cach la  Nhay");
    chon(10, 5); printf("bam gi cung duoc");
    getch();
    chon(10, 5); printf("                           ");

    while (1) {

        if (_kbhit()) {
            char ch = _getch();
            if (ch == 32) {
                if (n > 3)
                    n -= 3;
            }
            if (ch == 27) {
                break;
            }
        }

        vechim();
        vecot(0);
        vecot(1);
        if (collision() == 1) {
            gameover();
            return;
        }
        Sleep(100);
        xoachim();
        xoacot(0);
        xoacot(1);
        n += 1;

        if (n > chieudai - 2) {
            gameover();
            return;
        }

        if (c[0] == 1)
            a[0] += 2;

        if (c[1] == 1)
            a[1] += 2;

        if (a[0] >= 40 && a[0] < 42) {
            c[1] = 1;
            a[1] = 4;
            g(1);
        }
        if (a[0] > 68) {
            diem++;
            updatediem();
            c[1] = 0;
            a[0] = a[1];
            b[0] = b[1];
        }
    }
}

int main() {
    se(0, 0);
    srand((unsigned)time(NULL));

    do {
        system("cls");
        chon(10, 5); printf(" -------------------------- ");
        chon(10, 6); printf(" |     Nhanle    | ");
        chon(10, 7); printf(" --------------------------");
        chon(10, 9); printf("1. Choi");
        chon(10, 10); printf("2. Huong dan");
        chon(10, 11); printf("3. cut");
        chon(10, 13); printf("Chon tuy chon: ");
        char op = _getche();

        if (op == '1') play();
        else if (op == '2') m();
        else if (op == '3') exit(0);

    } while (1);

    return 0;
}

