// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable : 4244) 
#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(pop)

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// 游戏配置
#define WIDTH 20
#define HEIGHT 20
#define INIT_SNAKE_LENGTH 3

// 方向枚举
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

// 游戏状态结构体
struct Game {
    int gameOver;
    int score;
    enum Direction dir;
    int snakeX[100], snakeY[100];
    int snakeLength;
    int fruitX, fruitY;
};

// 初始化游戏
void setup(struct Game* game) {
    game->gameOver = 0;
    game->score = 0;
    game->dir = RIGHT;  // 设置初始方向

    // 初始化蛇的位置（确保不在边界）
    game->snakeLength = INIT_SNAKE_LENGTH;
    int startX = WIDTH / 2;
    int startY = HEIGHT / 2;

    for (int i = 0; i < game->snakeLength; i++) {
        game->snakeX[i] = startX - i;  // 蛇头在右，蛇尾在左
        game->snakeY[i] = startY;
    }

    // 生成第一个食物（确保不在边界和蛇身上）
    srand(time(NULL));
    int validPosition;
    do {
        validPosition = 1;
        game->fruitX = rand() % (WIDTH - 2) + 1;  // 1 到 WIDTH-2
        game->fruitY = rand() % (HEIGHT - 2) + 1; // 1 到 HEIGHT-2

        // 检查是否与蛇身重叠
        for (int i = 0; i < game->snakeLength; i++) {
            if (game->fruitX == game->snakeX[i] && game->fruitY == game->snakeY[i]) {
                validPosition = 0;
                break;
            }
        }
    } while (!validPosition);
}

// 绘制游戏界面
void draw(struct Game* game) {
    system("cls");

    // 绘制上边界
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    // 绘制游戏区域
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) printf("#");

            int printed = 0;

            // 绘制蛇头
            if (j == game->snakeX[0] && i == game->snakeY[0]) {
                printf("O");
                printed = 1;
            }
            // 绘制蛇身
            else {
                for (int k = 1; k < game->snakeLength; k++) {
                    if (j == game->snakeX[k] && i == game->snakeY[k]) {
                        printf("o");
                        printed = 1;
                        break;
                    }
                }
            }

            // 绘制食物
            if (!printed && j == game->fruitX && i == game->fruitY) {
                printf("F");
                printed = 1;
            }

            // 绘制空白
            if (!printed) printf(" ");

            if (j == WIDTH - 1) printf("#");
        }
        printf("\n");
    }

    // 绘制下边界
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    printf("得分: %d\n", game->score);
    printf("控制: W-上, S-下, A-左, D-右, X-退出\n");
    printf("当前方向: ");
    switch (game->dir) {
    case LEFT: printf("左"); break;
    case RIGHT: printf("右"); break;
    case UP: printf("上"); break;
    case DOWN: printf("下"); break;
    case STOP: printf("停止"); break;
    }
    printf("\n");
}

// 处理输入
void input(struct Game* game) {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 'a': case 'A':
            if (game->dir != RIGHT) game->dir = LEFT;
            break;
        case 'd': case 'D':
            if (game->dir != LEFT) game->dir = RIGHT;
            break;
        case 'w': case 'W':
            if (game->dir != DOWN) game->dir = UP;
            break;
        case 's': case 'S':
            if (game->dir != UP) game->dir = DOWN;
            break;
        case 'x': case 'X':
            game->gameOver = 1;
            break;
        }
    }
}

// 游戏逻辑
void logic(struct Game* game) {
    // 如果游戏已结束或蛇未移动，直接返回
    if (game->gameOver || game->dir == STOP) return;

    // 保存蛇尾位置
    int prevX = game->snakeX[game->snakeLength - 1];
    int prevY = game->snakeY[game->snakeLength - 1];

    // 移动蛇身
    for (int i = game->snakeLength - 1; i > 0; i--) {
        game->snakeX[i] = game->snakeX[i - 1];
        game->snakeY[i] = game->snakeY[i - 1];
    }

    // 移动蛇头
    switch (game->dir) {
    case LEFT: game->snakeX[0]--; break;
    case RIGHT: game->snakeX[0]++; break;
    case UP: game->snakeY[0]--; break;
    case DOWN: game->snakeY[0]++; break;
    }

    // 检测撞墙
    if (game->snakeX[0] < 0 || game->snakeX[0] >= WIDTH ||
        game->snakeY[0] < 0 || game->snakeY[0] >= HEIGHT) {
        game->gameOver = 1;
        return;
    }

    // 检测撞到自己
    for (int i = 1; i < game->snakeLength; i++) {
        if (game->snakeX[0] == game->snakeX[i] && game->snakeY[0] == game->snakeY[i]) {
            game->gameOver = 1;
            return;
        }
    }

    // 检测吃到食物
    if (game->snakeX[0] == game->fruitX && game->snakeY[0] == game->fruitY) {
        game->score += 10;

        // 增加蛇长度
        game->snakeLength++;
        game->snakeX[game->snakeLength - 1] = prevX;
        game->snakeY[game->snakeLength - 1] = prevY;

        // 生成新食物
        int validPosition;
        do {
            validPosition = 1;
            game->fruitX = rand() % (WIDTH - 2) + 1;
            game->fruitY = rand() % (HEIGHT - 2) + 1;

            // 确保食物不在蛇身上
            for (int i = 0; i < game->snakeLength; i++) {
                if (game->fruitX == game->snakeX[i] && game->fruitY == game->snakeY[i]) {
                    validPosition = 0;
                    break;
                }
            }
        } while (!validPosition);
    }
}

int main() {
    struct Game game;

    printf("=== 贪吃蛇游戏 ===\n");
    printf("控制键: W-上, S-下, A-左, D-右, X-退出\n");
    printf("按任意键开始游戏...");
    _getch();

    setup(&game);

    while (!game.gameOver) {
        draw(&game);
        input(&game);
        logic(&game);
        Sleep(400);  // 控制游戏速度
    }

    printf("\n游戏结束！最终得分: %d\n", game.score);
    printf("按任意键退出...");
    _getch();

    return 0;
}
