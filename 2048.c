#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <time.h>


int step = 0;
int score = 0;
long int Time;          //游戏运行时间
int BOX[4][4] = {0, 0, 0, 0,
                 0, 0, 0, 0,
                 0, 0, 0, 0,
                 0, 0, 0, 0};
HANDLE hOut;            //控制台句柄


void gotoxy(int x, int y);
int color(int c);
int TextColors(int i);          //根据数字修改颜色
void drawTheGameBox();           //绘制游戏界面
int *add(int item[]);           //合并数字
int ifMove(int item[]);
void Gameplay();
void Replay();
int if2n(int x);
int ifup();
int ifdown();
int ifright();
int BOXmax();
int Gamefaile();
int Gamewin();
int keyboardControl(int key);
void close();
void title();
void choice();
void Rabbit();
void regulation();
void explation();


void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);   //定位光标位置
}

int color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);    //更改文字颜色
    return 0;
}

void title() {
    color(11);
    gotoxy(19, 2);
    printf("⬛⬛⬛      ⬛⬛⬛⬛      ⬛  ⬛      ⬛⬛⬛⬛");
    gotoxy(19, 3);
    printf("     ⬛      ⬛     ⬛      ⬛  ⬛      ⬛     ⬛");
    gotoxy(19, 4);
    printf("⬛⬛⬛      ⬛     ⬛      ⬛  ⬛      ⬛⬛⬛⬛");
    gotoxy(19, 5);
    printf("⬛           ⬛     ⬛      ⬛⬛⬛⬛   ⬛     ⬛");
    gotoxy(19, 6);
    printf("⬛⬛⬛      ⬛⬛⬛⬛           ⬛      ⬛⬛⬛⬛");
}

void choice() {
    int n;
    int i, j = 1;

    gotoxy(32, 8);
    color(13);
    printf("挑 战 2 0 4 8");
    color(14);

    for(i = 9; i <= 20; i++) {
        for(j = 15; j <= 60; j++) {
            gotoxy(j, i);
            if(i == 9 || i == 20)   printf("=");
            else if(j == 15 || j == 59) printf("||");
        }
    }

    color(12);
    gotoxy(25, 12);
    printf("1.开始游戏");
    gotoxy(40, 12);
    printf("2.游戏规则");
    gotoxy(25, 16);
    printf("3.按键说明");
    gotoxy(40, 16);
    printf("4.退出");
    gotoxy(21, 22);
    color(5);
    printf("请选择[1 2 3 4]:[]\b\b");
    scanf("%d", &n);

    switch(n) {
        case 1:
            Gameplay();
            break;
        case 2:
            regulation();
            break;
        case 3:
            explation();
            break;
        case 4:
            exit(0);            //退出游戏
            break;
    }
}

void Rabbit()
{
    color(3);
    gotoxy(64,10);
    printf(" ┌─┐  ┌─┐");
    gotoxy(64,11);
    printf("|  |  |  |");
    gotoxy(64,12);
    printf("|  |  |  |");
    gotoxy(63,13);
    printf("_| ");
    gotoxy(74,13);
    printf("|_");
    gotoxy(62,14);
    printf("|");
    gotoxy(76,14);
    printf("|");
    gotoxy(62,15);
    printf("|        |");
    gotoxy(62,16);
    printf("| ");
    gotoxy(76,16);
    printf(" |");
    gotoxy(62,17);
    printf("|        |");
    gotoxy(62,18);
    printf("└ ─ ─ ─ ─ ┘");
    gotoxy(64,19);
    printf("┌ ┐    ┌ ┐");
    gotoxy(62,20);
    printf("└ ┴ ┴ ┴ ┴ ┘");
    color(5);
    gotoxy(67,13);
    printf("~ ' ~");
    color(4);
    gotoxy(67,14);
    printf("o   o");
    color(13);
    gotoxy(65,15);
    printf("\"");
    gotoxy(74,15);
    printf("\"");
    color(12);
    gotoxy(69,17);
    printf("┴");
}

int main() {
    SetConsoleOutputCP(65001);  // 设置控制台编码为UTF-8，防止中文乱码
    title();
    Rabbit();
    choice();
}

void drawTheGameBox() {
    int i, j, k;
    color(14);

    for(j = 2; j <= 22; j+=5) {
        gotoxy(15, j);
        for(k = 1; k < 42; k++) {
            printf("-");
        }printf("\n");
    }
    for(i = 3; i < 7; i++) {
        gotoxy(15, i);
        printf("|         |         |         |         |");
    }
    for(i = 8; i < 12; i++) {
        gotoxy(15, i);
        printf("|         |         |         |         |");
    }
    for(i = 13; i < 17; i++) {
        gotoxy(15, i);
        printf("|         |         |         |         |");
    }
    for(i = 18; i < 22; i++) {
        gotoxy(15, i);
        printf("|         |         |         |         |");
    }

    gotoxy(16, 1);
    color(11);
    printf("游戏分数：%d", score);

    color(13);
    gotoxy(42, 1);
    printf("执行步数：%d\n", step);

    gotoxy(44, 23);
    color(10);
    printf("已用时：%ld s", time(NULL) - Time);
}

int TextColors(int number) {
    switch (number) {
        case 2:
            return color(12);
            break;
        case 4:
            return color(11);
            break;
        case 8:
            return color(10);
            break;
        case 16:
            return color(14);
            break;
        case 32:
            return color(6);
            break;
        case 64:
            return color(5);
            break;
        case 128:
            return color(4);
            break;
        case 256:
            return color(3);
            break;
        case 512:
            return color(2);
            break;
        case 1024:
            return color(9);
            break;
        case 2048:
            return color(7);
            break;
    }
    return 0;
}

int* add(int item[]) {
    int i = 0, j = 0;
    int tep[4] = {0, 0, 0, 0};
    static int tmp[4] = {0, 0, 0, 0};

    for(i = 0; i < 4; i++) {
        if(item[i] != 0) {
            tep[j++] = item[i];
        }
    }
    for(i = 0; i < 3; i++) {
        if(tep[i] == tep[i+1]) {
            tep[i] *= 2;
            tep[i+1] = 0;
            score += tep[i];
        }
    }
    j = 0;
    for(i = 0; i < 4; i++) {
        if(tep[i] != 0) {
            tmp[j++] = tep[i];
        }
    }
    return (int *)(&tmp);
}

int ifMove(int item[]) {
    int i = 0;
    for(i = 0; i < 3; i++) {
        if(item[i] != 0 && item[i] == item[i+1]) {
            return 1;
        }
        if(item[i] == 0 && item[i+1] != 0) {
            return 1;
        }
    }
    return 0;
}

int if2n(int x) {
    int flag = 0;
    int n;
    int N = 1;

    for(n = 1; n <= 11; n++) {
        if(x == pow(2, n)) {
            flag = 1;

            if(n > N) {
                N = n;
            }

            return flag;
        }
    }
    return flag;
}

int ifup() {
    int i, j;
    int flag = 0;
    for(j = 0; j < 4; j++) {
        for(i = 0; i < 3; i++) {
            if(BOX[i+1][j] && (if2n(BOX[i][j] + BOX[i+1][j]) == 1)) {
                flag = 1;
            }
        }
    }
    return flag;
}

int ifdown() {
    int i, j;
    int flag = 0;

    for(j = 0; j < 4; j++) {
        for(i = 3; i > 0; i--) {
            if(BOX[i-1][j] && if2n(BOX[i][j] + BOX[i-1][j]) == 1) {
                flag = 1;
            }
        }
    }
    return flag;
}

int ifleft() {
    int i, j;
    int flag = 0;

    for(i = 0; i < 4; i++) {
        for(j = 0; j < 3; j++) {
            if(BOX[i][j+1] && if2n(BOX[i][j] + BOX[i][j+1]) == 1) {
                flag = 1;
            }
        }
    }
    return flag;
}

int ifright() {
    int i, j;
    int flag = 0;

    for(i = 0; i < 4; i++) {
        for(j = 3; j > 0; j--) {
            if(BOX[i][j-1] && if2n(BOX[i][j] + BOX[i][j-1]) == 1) {
                flag = 1;
            }
        }
    }
    return flag;
}

int BOXmax() {
    int max = BOX[0][0];
    int i, j;

    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(BOX[i][j] > max) {
                max = BOX[i][j];
            }
        }
    }
    return max;
}

int Gamewin() {
    int flag = 0;
    if(BOXmax() == 2048) {
        system("cls");
        gotoxy(1, 6);
        color(2);

        // 用 ⬛ 拼出 WIN
        // W
        gotoxy(23, 6);  printf("⬛   ⬛");
        gotoxy(23, 7);  printf("⬛   ⬛");
        gotoxy(23, 8);  printf("⬛ ⬛ ⬛");
        gotoxy(23, 9);  printf("⬛ ⬛ ⬛");
        gotoxy(23, 10); printf("⬛   ⬛");

        // I
        gotoxy(31, 6);  printf("⬛⬛⬛");
        gotoxy(31, 7);  printf("  ⬛  ");
        gotoxy(31, 8);  printf("  ⬛  ");
        gotoxy(31, 9);  printf("  ⬛  ");
        gotoxy(31, 10); printf("⬛⬛⬛");

        // N
        gotoxy(38, 6);  printf("⬛  ⬛");
        gotoxy(38, 7);  printf("⬛⬛ ⬛");
        gotoxy(38, 8);  printf("⬛ ⬛⬛");
        gotoxy(38, 9);  printf("⬛  ⬛");
        gotoxy(38, 10); printf("⬛  ⬛");

        printf("胜利了，你真牛逼！！！");
        flag = 1;
    }
    return flag;
}

int Gamefaile() {
    int flag = 0;

    if(ifup() + ifdown() + ifleft() + ifright() == 0) {
        system("cls");
        gotoxy(1, 6);
        color(4);

        // 用 ⬛ 拼出 FAIL
        // F
        gotoxy(23, 6);  printf("⬛⬛⬛");
        gotoxy(23, 7);  printf("⬛   ");
        gotoxy(23, 8);  printf("⬛⬛ ");
        gotoxy(23, 9);  printf("⬛   ");
        gotoxy(23, 10); printf("⬛   ");

        // A
        gotoxy(31, 6);  printf(" ⬛ ");
        gotoxy(31, 7);  printf("⬛ ⬛");
        gotoxy(31, 8);  printf("⬛⬛⬛");
        gotoxy(31, 9);  printf("⬛ ⬛");
        gotoxy(31, 10); printf("⬛ ⬛");

        // I
        gotoxy(38, 6);  printf("⬛⬛⬛");
        gotoxy(38, 7);  printf("  ⬛  ");
        gotoxy(38, 8);  printf("  ⬛  ");
        gotoxy(38, 9);  printf("  ⬛  ");
        gotoxy(38, 10); printf("⬛⬛⬛");

        // L
        gotoxy(45, 6);  printf("⬛   ");
        gotoxy(45, 7);  printf("⬛   ");
        gotoxy(45, 8);  printf("⬛   ");
        gotoxy(45, 9);  printf("⬛   ");
        gotoxy(45, 10); printf("⬛⬛⬛");

        printf("无法移动，游戏失败！！！");
        flag = 1;
    }
    return flag;
}

int keyboardControl(int key) {
    int i = 0, j = 0;
    int *p;
    int tp[4] = {0, 0, 0, 0};

    switch(key) {
        case 72:
            j = 0;
            for(i = 0; i < 4; i++) {
                tp[0] = BOX[0][i];
                tp[1] = BOX[1][i];
                tp[2] = BOX[2][i];
                tp[3] = BOX[3][i];
                p = add(tp);

                if(ifMove(tp)) {
                    j++;
                }

                BOX[0][i] = p[0];
                BOX[1][i] = p[1];
                BOX[2][i] = p[2];
                BOX[3][i] = p[3];
            }
            return (j == 0);

        case 80:
            j = 0;
            for(i = 0; i < 4; i++) {
                tp[0] = BOX[0][i];
                tp[1] = BOX[1][i];
                tp[2] = BOX[2][i];
                tp[3] = BOX[3][i];
                p = add(tp);

                if(ifMove(tp)) {
                    j++;
                }

                BOX[3][i] = p[0];
                BOX[2][i] = p[1];
                BOX[1][i] = p[2];
                BOX[0][i] = p[3];
            }
            return (j == 0);

        case 75:
            j = 0;
            for(i = 0; i < 4; i++) {
                tp[0] = BOX[i][0];
                tp[1] = BOX[i][1];
                tp[2] = BOX[i][2];
                tp[3] = BOX[i][3];
                p = add(tp);

                if(ifMove(tp)) {
                    j++;
                }

                BOX[i][0] = p[0];
                BOX[i][1] = p[1];
                BOX[i][2] = p[2];
                BOX[i][3] = p[3];
            }
            return (j == 0);

        case 77:
            j = 0;
            for(i = 0; i < 4; i++) {
                tp[0] = BOX[i][3];
                tp[1] = BOX[i][2];
                tp[2] = BOX[i][1];
                tp[3] = BOX[i][0];
                p = add(tp);

                if(ifMove(tp)) {
                    j++;
                }

                BOX[i][3] = p[0];
                BOX[i][2] = p[1];
                BOX[i][1] = p[2];
                BOX[i][0] = p[3];
            }
            return (j == 0);

        case 27:
            gotoxy(20, 23);
            color(12);
            printf("确定要退出游戏么？(y/n)");
            char c = getch();
            if(c == 'y' || c == 'Y') {
                exit(0);
            }
            if(c == 'n' || c == 'N') {
                gotoxy(20, 23);
                printf("                                    ");
            }
            break;

            default: return 0;
    }
}

void Gameplay() {
    system("cls");
    int i = 0, j = 0;
    Time = time(NULL);
    drawTheGameBox();

    int a, b;
    srand(time(NULL));
    do {
        a = rand() % 4;
        b = rand() % 4;
    }while(BOX[a][b] != 0);

    if(rand() % 4 == 0) {
        BOX[a][b] = 4;
    }else {
        BOX[a][b] = 2;
    }

    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(BOX[i][j] == 0)  continue;
            gotoxy(15 + j*10 + 5, 2 + i*5 + 3);
            int c = BOX[i][j];
            TextColors(c);
            printf("%d", c);
        }
    }

    while(1) {
        if(kbhit()) {
            int key = getch();
            if(key == 0xE0 || key == 0x00) {
                key = getch();
            }
            if(keyboardControl(key))    continue;
            drawTheGameBox();

            for(i = 0; i < 4; i++) {
                for(j = 0; j < 4; j++) {
                    if(BOX[i][j] == 0)  continue;
                    gotoxy(15 + j*10 + 5, 2 + i*5 + 3);
                    int c = BOX[i][j];
                    TextColors(c);
                    printf("%d", c);
                }
            }

            do {
                a = rand() % 4;
                b = rand() % 4;
            }while(BOX[a][b] !=  0);
            if(rand() % 4 == 0) {
                BOX[a][b] = 4;
            }else {
                BOX[a][b] = 2;
            }
            step++;
            gotoxy(15 + b*10 + 5, 2 + a*5 + 3);
            int c = BOX[a][b];
            TextColors(c);
            printf("%d", c);
        }

        if(Gamewin() + Gamefaile() != 0) {
            int n;
            gotoxy(20, 20);
            color(12);
            printf("重玩--------------1");
            gotoxy(45, 20);
            printf("退出--------------2");
            gotoxy(43, 21);
            color(11);
            scanf("%d", &n);
            switch(n) {
                case 1:
                    Replay();
                    break;
                case 2:
                    exit(0);
                    break;
            }
        }
    }
}

void Replay() {
    system("cls");
    score = 0, step = 0;
    memset(BOX, 0, 16*sizeof(int));
    Gameplay();
}

void regulation() {
    int i, j = 1;
    system("cls");
    color(13);
    gotoxy(34, 3);
    printf("游戏规则");
    color(2);
    for(i = 6; i <= 18; i++) {
        for(j = 15; j <=70; j++) {
            gotoxy(j, i);
            if(i == 6 || i == 18)   printf("=");
            else if(j == 15 || j == 69) printf("||");
        }
    }
    color(3);
    gotoxy(18, 7);
    printf("tips1：玩家可通过方向键来移动方块");
    color(10);
    gotoxy(18, 9);
    printf("tips2：按ESC推出以游戏");
    color(14);
    gotoxy(18, 13);
    printf("tips3：当两个相同的数字碰撞时，它们会合并成一个数字");
    color(11);
    gotoxy(18, 14);
    printf("tips4：每移动一步，空位随即出现一个2或4");
    color(4);
    gotoxy(18, 15);
    printf("tips5：棋盘被数字填满时游戏结束");
    color(5);
    gotoxy(18, 17);
    printf("tips6：当棋盘中出现2048时，游戏胜利");
    getch();
    system("cls");
    main();
}

void explation() {
    gotoxy(20, 22);
    color(13);
    printf("1、按方向键来进行游戏操作！");
    gotoxy(20, 24);
    printf("2、ESC退出游戏");
    getch();
    system("cls");
    main();
}