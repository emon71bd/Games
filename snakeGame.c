#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define WIDTH 20
#define HEIGHT 20

int gameOver;
int x, y, fruitX, fruitY, score;

int flag;

int tailX[100], tailY[100];
int CountTail = 0;
void setup() {
    gameOver = 0;
    x = WIDTH/2;
    y = HEIGHT/2;

    label1:
        fruitX = rand()%20;
        if(fruitX == 0) goto label1;

    label2:
        fruitY = rand()%20;
        if(fruitY == 0) goto label2;

    score = 0;
}
void drawBoard() {
    int i, j;
    system("cls");
    for(i = 0; i < WIDTH; i++) {
        for(j = 0; j < HEIGHT; j++) {
            if(i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                printf("*"); // Print the border
            } else {
                if(i == x && j == y)
                    printf("@");
                else if(i==fruitX && j == fruitY)
                    printf("o");
                else {
                    int ch = 0;
                    for(int k=0; k<CountTail; k++) {
                        if(i == tailX[k] && j == tailY[k]) {
                            printf("o");
                            ch = 1;
                        }
                    }
                    if(ch == 0) {
                        printf(" "); // Print the empty space
                    }
                }

            }
        }
        printf("\n"); // Newline at the end of each row
    }
    printf("\nSCORE = %d", score);
}

void input() {
    if(kbhit()) {
        switch(getch()) {
            // Button 'aswz'
            case 'j' : flag = 1; break; // GoToleft
            case 'l' : flag = 2; break; // GoToRight
            case 'i' : flag = 3; break; // Up
            case 'k' : flag = 4; break; // Down
            case 'x' : gameOver = -1; break;
        }
    }
}

void MakeLogic() {
    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for(int i=1; i<CountTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(flag) {
        case 1: y--; break;
        case 2: y++; break;
        case 3: x--; break;
        case 4: x++; break;
        default: break;
    }
    if(x<0 || x>WIDTH || y<0 || y>HEIGHT) gameOver = 1;
    for(int i=0; i<CountTail; i++) {
        if(x == tailX[i] && y == tailY[i]) gameOver = 1;
    }
    if(x == fruitX && y == fruitY) {
        label3:
            fruitX = rand()%20;
            if(fruitX == 0) goto label3;

        label4:
            fruitY = rand()%20;
            if(fruitY == 0) goto label4;

            score += 5;
            CountTail++;
    }
}
int main() {
    int m,n;
    char c;

    label5:
    setup();

    while(!gameOver) {
        drawBoard(); // Call the function to draw the game board
        input();
        MakeLogic();
        Sleep(100);
    }
    printf("\nPress Y to continue again: ");
    scanf("%c", &c);
    if(c == 'y' || c == 'Y') goto label5;
    return 0;
}
