#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>

#define HEIGHT 20
#define WIDTH 20
#define GAME_SPEED 100000

int i, j, height = HEIGHT, width = WIDTH, gameover, score;
int x, y, fruitx, fruity, direction;

void draw() {
    system("cls");
    printf("\e[?25l"); //Hides the cursor

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                printf("#");
            else if (i == x && j == y)
                printf("0");
            else if (i == fruitx && j == fruity)
                printf("*");
            else
                printf(" ");
        }

        printf("\n");
    }

    printf("\rScore = %d\n", score);
    printf("Press X to quit the game");
    fflush(stdout);
}

void setup() {
    gameover = 0;
    x = height / 2;
    y = width / 2;
    fruitx = rand() % (height - 2) + 1;
    fruity = rand() % (width - 2) + 1;
    score = 0;
    direction = 0;
}

void input() {
    if (kbhit()) {
        switch (getch()) {
            case 'a':
                direction = 1;
                break;
            case 's':
                direction = 2;
                break;
            case 'd':
                direction = 3;
                break;
            case 'w':
                direction = 4;
                break;
            case 'x':
                gameover = 1;
                break;
        }
    }
}

void logic() {

    usleep(GAME_SPEED);

    switch (direction) {
        case 1:
            y--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y++;
            break;
        case 4:
            x--;
            break;
        default:
            break;
    }

    if (x < 0 || x >= height || y < 0 || y >= width)
        gameover = 1;

    if (x == fruitx && y == fruity) {
        fruitx = rand() % (height - 2) + 1;
        fruity = rand() % (width - 2) + 1;
        score += 10;
    }
}

int main() {
    setup();
    while (!gameover) {
        draw();
        input();
        logic();
    }

    return 0;
}
