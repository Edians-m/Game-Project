#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>


#define FrameX 13
#define FrameY 3
#define Frame_height 20
#define Frame_width 18


int i, j, Temp, Temp1, Temp2;
int a[80][80] = {0};
int b[4] = {0};


struct Tetris {
    int x;
    int y;
    int flag;
    int next;
    int speed;
    int number;
    int score;
    int level;
};
HANDLE hOut;


int color(int c);
void gotoxy(int x, int y);
void DrwaGamefeame();
void flag(struct Tetris*);
void MakeTetris(struct Tetris*);
void PrintTetris(struct Tetris*);
void CleanTetris(struct Tetris*);
int ifMove(struct Tetris*);
void Del_Fullline(struct Tetris*);
void Gameplay();
void regulation();
void explation();
void welcom();
void Replay(struct Tetris* tetris);
void title();
void flower();
void close();


int color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return 0;
}

void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void title() {
    color(15);                               //亮白色
    gotoxy(24, 3);
    printf("趣 味 俄 罗 斯 方 块\n");
    color(11);
    gotoxy(18, 5);
    printf("⬛");
    gotoxy(18, 6);
    printf("⬛⬛");
    gotoxy(18, 7);
    printf("⬛");

    color(14);                              //黄色
    gotoxy(26, 6);
    printf("⬛⬛");
    gotoxy(28, 7);
    printf("⬛⬛");

    color(10);                              //绿色
    gotoxy(36, 6);
    printf("⬛⬛");
    gotoxy(36, 7);
    printf("⬛⬛");

    color(13);                              //粉色
    gotoxy(45, 5);
    printf("⬛");
    gotoxy(45, 6);
    printf("⬛");
    gotoxy(45, 7);
    printf("⬛");
    gotoxy(45, 8);
    printf("⬛");

    color(12);                              //亮红色
    gotoxy(56, 6);
    printf("⬛");
    gotoxy(52, 7);
    printf("⬛⬛⬛");
}

int main() {
    SetConsoleOutputCP(65001);  // 设置控制台编码为UTF-8，防止中文乱码
    title();
    flower();
    welcom();
}

void flower() {
    gotoxy(66, 11);
    color(12);
    printf("(_)");          //红花上边花瓣

    gotoxy(64, 12);
    printf("(_)");          //红花左边花瓣

    gotoxy(68, 12);
    printf("(_)");          //红花右边花瓣

    gotoxy(66, 13);
    printf("(_)");          //红花下边花瓣

    gotoxy(67, 12);         //红花花蕊
    color(6);
    printf("@");

    gotoxy(72, 10);
    color(13);
    printf("(_)");          //粉花左边花瓣

    gotoxy(76, 10);
    printf("(_)");          //粉花右边花瓣

    gotoxy(74, 9);
    printf("(_)");

    gotoxy(74, 11);
    printf("(_)");          //粉花上边花瓣

    gotoxy(75, 10);
    color(6);
    printf("@");            //粉花花蕊

    gotoxy(71, 12);
    printf("|");

    gotoxy(72, 11);
    printf("/");

    gotoxy(70, 13);
    printf("\\|");

    gotoxy(70, 14);
    printf("|/");

    gotoxy(70, 15);
    printf("\\|");

    gotoxy(70, 16);
    printf("| /");

    gotoxy(70, 17);
    printf("|");

    gotoxy(67, 17);
    color(10);
    printf("\\\\\\\\");          //草地

    gotoxy(73, 17);
    printf("//");

    gotoxy(67, 18);
    color(2);
    printf("^^^^^^^^");

    gotoxy(65, 19);
    color(5);
    printf("明 日 科 技");

    gotoxy(68, 20);
    printf("Edians");
}

void welcom() {
    int n;
    int i, j = 1;
    color(14);
    for(i = 9; i <= 20; i++) {
        for(j = 15; j <= 60; j++) {
            gotoxy(j, i);
            if(i == 9 || i == 20)   printf("=");
            else if(j == 5 || j == 59)  printf("||");
        }
    }

    color(12);
    gotoxy(25, 12);
    printf("1.开始游戏");
    gotoxy(40, 12);
    printf("2.按键说明");
    gotoxy(25, 17);
    printf("3.游戏规则");
    gotoxy(40, 17);
    printf("4.退出游戏");
    gotoxy(21, 22);
    color(3);
    printf("请选择[1 2 3 4]:[ ]\b\b");
    color(14);
    scanf("%d", &n);
    switch(n) {
        case 1:
            system("cls");
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
    }
}

void DrwaGamefeame() {
    gotoxy(FrameX+Frame_width-7, FrameY-2);
    color(11);
    printf("趣味俄罗斯方块");
    gotoxy(FrameX+2*Frame_width+3, FrameY+7);
    color(2);
    printf("**********");
    gotoxy(FrameX+2*Frame_width+13, FrameY+7);
    color(3);
    printf("下一出现方块：");
    gotoxy(FrameX+2*Frame_width+3, FrameY+13);
    color(2);
    printf("**********");
    gotoxy(FrameX+2*Frame_width+3, FrameY+17);
    color(14);
    printf("f键：旋转");
    gotoxy(FrameX+2*Frame_width+3, FrameY+19);
    printf("空格：暂停游戏");
    gotoxy(FrameX+2*Frame_width+3, FrameY+15);
    printf("Esc：退出游戏");
    gotoxy(FrameX, FrameY);
    color(12);
    printf("┌");
    gotoxy(FrameX+2*Frame_width-2, FrameY);
    printf("┐");
    gotoxy(FrameX, FrameY+Frame_height);
    printf("└");
    gotoxy(FrameX+2*Frame_width-2, FrameY+Frame_height);
    printf("┘");
    a[FrameX][FrameY+Frame_height] = 2;
    a[FrameX+2*Frame_width-2][FrameY+Frame_height] = 2;
    for(i = 2; i < 2*Frame_width-2; i+=2) {
        gotoxy(FrameX+i, FrameY);
        printf("─");
    }
    for(i = 2; i < 2*Frame_width-2; i+=2) {
        gotoxy(FrameX+i, FrameY+Frame_height);
        printf("─");
        a[FrameX+i][FrameY+Frame_height] = 2;
    }
    for(i = 1; i < Frame_height; i++) {
        gotoxy(FrameX, FrameY+i);
        printf("│");
        a[FrameX][FrameY+i] = 2;
    }
    for(i = 1; i < Frame_height; i++) {
        gotoxy(FrameX+2*Frame_width-2, FrameY+i);
        printf("│");
        a[FrameX+2*Frame_width-2][FrameY+i] = 2;
    }

}

void MakeTetris(struct Tetris *tetris) {
    a[tetris->x][tetris->y] = b[0];
    switch(tetris->flag) {
        case 1:
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x+2][tetris->y-1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        case 2:
            color(13);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x+2][tetris->y] = b[2];
            a[tetris->x+4][tetris->y] = b[3];
            break;
        case 3:
            color(13);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x][tetris->y-2] = b[2];
            a[tetris->x][tetris->y+1] = b[3];
            break;
        case 4:
            color(11);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x+2][tetris->y] = b[2];
            a[tetris->x][tetris->y+1] = b[3];
            break;
        case 5:
            color(11);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x-2][tetris->y] = b[3];
            break;
        case 6:
            color(11);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x-2][tetris->y] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        case 7:
            color(11);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        case 8:
            color(11);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x-2][tetris->y] = b[3];
            break;
        case 9:
            color(14);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x-2][tetris->y] = b[2];
            a[tetris->x+2][tetris->y+1] = b[3];
            break;
        case 10:
            color(14);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x-2][tetris->y-1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        case 11:
            color(14);
            a[tetris->x][tetris->y+1] = b[1];
            a[tetris->x-2][tetris->y-1] = b[2];
            a[tetris->x-2][tetris->y] = b[3];
            break;
        case 12:
            color(12);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x-2][tetris->y-1] = b[3];
            break;
        case 13:
            color(12);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x+2][tetris->y-1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        case 14:
            color(12);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x+2][tetris->y+1] = b[3];
            break;
        case 15:
            color(12);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x-2][tetris->y+1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        case 16:
            color(12);
            a[tetris->x][tetris->y+1] = b[1];
            a[tetris->x][tetris->y-1] = b[2];
            a[tetris->x+2][tetris->y-1] = b[3];
            break;
        case 17:
            color(12);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x+2][tetris->y+1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        case 18:
            color(12);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x-2][tetris->y+1] = b[3];
            break;
        case 19:
            color(12);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x-2][tetris->y-1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
    }
}

void PrintTetris(struct Tetris *tetris) {
    for(i = 0; i < 4; i++) {
        b[i] = 1;
    }
    MakeTetris(tetris);
    for(i = tetris->x-2; i <= tetris->x+4; i+=2) {
        for(j = tetris->y-2; j <= tetris->y+1; j++) {
            if(a[i][j] == 1 && j > FrameY) {
                gotoxy(i, j);
                printf("■");
            }
        }
    }

    //打印菜单信息
    gotoxy(FrameX+2*Frame_width+3, FrameY+1);
    color(4);
    printf("level :");
    color(12);
    printf("%d", tetris->level);
    gotoxy(FrameX+2*Frame_width+3, FrameY+3);
    color(4);
    printf("score :");
    color(12);
    printf("%d", tetris->score);
    gotoxy(FrameX+2*Frame_width+3, FrameY+5);
    color(4);
    printf("speed :");
    color(12);
    printf("%dms", tetris->speed);
}

int ifMove(struct Tetris *tetris) {
    if(a[tetris->x][tetris->y] != 0) {
        return 0;
    }else {
        if(
          ( tetris->flag==1 && ( a[tetris->x][tetris->y-1]==0 &&
          a[tetris->x+2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
          ( tetris->flag==2 && ( a[tetris->x-2][tetris->y]==0 &&
          a[tetris->x+2][tetris->y]==0 && a[tetris->x+4][tetris->y]==0 ) ) ||
          ( tetris->flag==3 && ( a[tetris->x][tetris->y-1]==0 &&
          a[tetris->x][tetris->y-2]==0 && a[tetris->x][tetris->y+1]==0 ) ) ||
          ( tetris->flag==4 && ( a[tetris->x-2][tetris->y]==0 &&
          a[tetris->x+2][tetris->y]==0 && a[tetris->x][tetris->y+1]==0 ) ) ||
          ( tetris->flag==5 && ( a[tetris->x][tetris->y-1]==0 &&
          a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y]==0 ) ) ||
          ( tetris->flag==6 && ( a[tetris->x][tetris->y-1]==0 &&
          a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
          ( tetris->flag==7 && ( a[tetris->x][tetris->y-1]==0 &&
          a[tetris->x][tetris->y+1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
          ( tetris->flag==8 && ( a[tetris->x][tetris->y+1]==0 &&
          a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y+1]==0 ) ) ||
          ( tetris->flag==9 && ( a[tetris->x][tetris->y-1]==0 &&
          a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y+1]==0 ) ) ||
          ( tetris->flag==10 && ( a[tetris->x][tetris->y-1]==0 &&
          a[tetris->x-2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
          ( tetris->flag==11 && ( a[tetris->x][tetris->y+1]==0 &&
          a[tetris->x-2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
          ( tetris->flag==12 && ( a[tetris->x][tetris->y-1]==0 &&
          a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y-1]==0 ) ) ||
          ( tetris->flag==13 && ( a[tetris->x-2][tetris->y]==0 &&
          a[tetris->x+2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
          ( tetris->flag==14 && ( a[tetris->x][tetris->y-1]==0 &&
          a[tetris->x][tetris->y+1]==0 && a[tetris->x+2][tetris->y+1]==0 ) ) ||
          ( tetris->flag==15 && ( a[tetris->x-2][tetris->y]==0 &&
          a[tetris->x-2][tetris->y+1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
          ( tetris->flag==16 && ( a[tetris->x][tetris->y+1]==0 &&
          a[tetris->x][tetris->y-1]==0 && a[tetris->x+2][tetris->y-1]==0 ) ) ||
          ( tetris->flag==17 && ( a[tetris->x-2][tetris->y]==0 &&
          a[tetris->x+2][tetris->y+1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
          ( tetris->flag==18 && ( a[tetris->x][tetris->y-1]==0 &&
          a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y+1]==0 ) ) ||
          ( tetris->flag==19 && ( a[tetris->x-2][tetris->y]==0 &&
          a[tetris->x-2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) )
        ) {
            return 1;
        }
        return 0;
    }
}

void CleanTetris(struct Tetris *tetris) {
    for(i = 0; i < 4; i++) {
        b[i] = 0;
    }
    MakeTetris(tetris);
    for(i = tetris->x-2; i <= tetris->x+4; i+=2) {
        for(j = tetris->y-2; j <= tetris->y+1; j++) {
            if(a[i][j] == 0 && j > FrameY) {
                gotoxy(i, j);
                printf("  ");
            }
        }
    }
}

void Del_Fullline(struct Tetris *tetris) {
    int k, del_rows = 0;
    for(j = FrameY+Frame_height-1; j > FrameY+1; j--) {
        k = 0;
        for(i = FrameX+2; i < FrameX+2*Frame_width-2; i+=2) {
            if(a[i][j] == 1) {
                k++;
                if(k == Frame_width-2) {
                    for(k = FrameX+2; k < FrameX+2*Frame_width-2; k+=2) {
                        a[k][j] = 0;
                        gotoxy(k, j);
                        printf("  ");
                    }
                    for(k = j-1; k > FrameY; k--) {
                        for(i = FrameX+2; i < FrameX+2*Frame_width-2; i+=2) {
                            if(a[i][k] == 1) {
                                a[i][k] = 0;
                                gotoxy(i, k);
                                printf("  ");
                                a[i][k+1] = 1;
                                gotoxy(i, k+1);
                                printf("■");
                            }
                        }
                    }
                    j++;
                    del_rows++;
                }
            }
        }
    }
    tetris->score += del_rows * 100;
    if(del_rows > 0 && (tetris->score%1000==0 || tetris->score/1000 > tetris->level-1)) {
        tetris->speed -= 20;
        tetris->level++;
    }
}

void Flag(struct Tetris *tetris) {
    tetris->number++;
    srand(time(NULL));
    if(tetris->number == 1) {
        tetris->flag = rand()%19 + 1;
    }
    tetris->next = rand()%19 + 1;
}

void Gameplay() {
    int n;
    struct Tetris t, *tetris = &t;
    char ch;
    tetris->number = 0;
    tetris->speed = 300;
    tetris->score = 0;
    tetris->level = 1;
    while(1) {
        Flag(tetris);
        Temp = tetris->flag;
        tetris->x = FrameX + Frame_width + 6;
        tetris->y = FrameY + 10;
        tetris->flag = tetris->next;
        PrintTetris(tetris);
        tetris->x = FrameX + Frame_width;
        tetris->y = FrameY - 1;
        tetris->flag = Temp;

        while(1) {
            label:PrintTetris(tetris);
            Sleep(tetris->speed);
            CleanTetris(tetris);
            Temp = tetris->x;
            Temp2=tetris->flag;
            if(kbhit()) {
                ch = getch();
                if(ch == 75) {
                    tetris->x -= 2;
                }
                if(ch == 77) {
                    tetris->x += 2;
                }
                if(ch == 80) {
                    if(ifMove(tetris) != 0) {
                        tetris->y += 2;
                    }
                    if(ifMove(tetris) == 0) {
                        tetris->y = FrameY + Frame_height - 2;
                    }
                }
                if(ch == 72) {
                    if(tetris->flag >= 2 && tetris->flag <= 3) {
                        tetris->flag++;
                        tetris->flag %= 2;
                        tetris->flag += 2;
                    }
                    if(tetris->flag >= 4 && tetris->flag <= 7) {
                        tetris->flag++;
                        tetris->flag %= 4;
                        tetris->flag += 4;
                    }
                    if(tetris->flag >= 8 && tetris->flag <= 11) {
                        tetris->flag++;
                        tetris->flag %= 4;
                        tetris->flag += 8;
                    }
                    if(tetris->flag >= 12 && tetris->flag <= 15) {
                        tetris->flag++;
                        tetris->flag %= 4;
                        tetris->flag += 12;
                    }
                    if(tetris->flag >= 16 && tetris->flag <= 19) {
                        tetris->flag++;
                        tetris->flag %= 4;
                        tetris->flag += 16;
                    }
                }
                if(ch == 32) {
                    PrintTetris(tetris);
                    while(1) {
                        if(kbhit()) {
                            ch = getch();
                            if(ch == 32) {
                                goto label;
                            }
                        }
                    }
                }
                if(ch == 27) {
                    system("cls");
                    memset(a, 0, 6400*sizeof(int));
                    welcom();
                }
                if(ifMove(tetris) == 0) {
                    tetris->x = Temp1;
                    tetris->flag = Temp2;
                }else {
                    goto label;
                }
            }
            tetris->y++;
            if(ifMove(tetris) == 0) {
                tetris->y--;
                PrintTetris(tetris);
                Del_Fullline(tetris);
                break;
            }
        }
    }
}