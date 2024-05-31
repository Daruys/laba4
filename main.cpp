#include <iostream>
#include <vector>
#include <conio.h>  // Для _kbhit() и _getch()
#include <windows.h>  // Для Sleep()
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point {
    int x, y;
};

class SnakeGame {
public:
    SnakeGame() {
        width = 40;
        height = 20;
        snake.push_back({width / 2, height / 2});
        direction = 'R';

        placeFood();
        srand(time(0));
    }

    void run() {
        while (true) {
            if (_kbhit()) {
                processInput();
            }
            moveSnake();
            if (checkCollision()) {
                break;
            }
            draw();
            Sleep(100); // Sleep for 100 milliseconds
        }
        cout << "Game Over" << endl;
    }

private:
    int width, height;
    vector<Point> snake;
    Point food;
    char direction;

    void placeFood() {
        while (true) {
            food.x = rand() % width;
            food.y = rand() % height;
            bool onSnake = false;
            for (const auto& p : snake) {
                if (p.x == food.x && p.y == food.y) {
                    onSnake = true;
                    break;
                }
            }
            if (!onSnake) {
                break;
            }
        }
    }

    void processInput() {
        char ch = _getch();
        switch (ch) {
            case 'w':
                if (direction != 'D') direction = 'U';
                break;
            case 's':
                if (direction != 'U') direction = 'D';
                break;
            case 'a':
                if (direction != 'R') direction = 'L';
                break;
            case 'd':
                if (direction != 'L') direction = 'R';
                break;
            case 'q':
                exit(0);
        }
    }

    void moveSnake() {
        Point newHead = snake.front();
        switch (direction) {
            case 'U': newHead.y--; break;
            case 'D': newHead.y++; break;
            case 'L': newHead.x--; break;
            case 'R': newHead.x++; break;
        }
        snake.insert(snake.begin(), newHead);

        if (newHead.x == food.x && newHead.y == food.y) {
            placeFood();
        } else {
            snake.pop_back();
        }
    }

    bool checkCollision() {
        const Point& head = snake.front();
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) {
            return true;
        }
        for (size_t i = 1; i < snake.size(); i++) {
            if (snake[i].x == head.x && snake[i].y == head.y) {
                return true;
            }
        }
        return false;
    }

    void draw() {
        system("cls"); // Clear the console
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (x == food.x && y == food.y) {
                    cout << 'X';
                } else {
                    bool isSnake = false;
                    for (const auto& p : snake) {
                        if (p.x == x && p.y == y) {
                            cout << 'O';
                            isSnake = true;
                            break;
                        }
                    }
                    if (!isSnake) {
                        cout << ' ';
                    }
                }
            }
            cout << endl;
        }
    }
};

int main() {
    SnakeGame game;
    game.run();
    return 0;
}