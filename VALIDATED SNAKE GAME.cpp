#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>  
#include <conio.h>   
using namespace std;
void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main() {
    char choice;
    srand(time(0));  
    do {
        int width = 100; 
        int height = 20;
        int snakeX = width / 2;
        int snakeY = height / 2;
        int fruitX = rand() % (width - 2) + 1;
        int fruitY = rand() % (height - 2) + 1;
        int score = 0;
        char direction = 'R';
        int snakeLength = 1;
        int snakeXPos[100];
        int snakeYPos[100];
        snakeXPos[0] = snakeX;
        snakeYPos[0] = snakeY;
        bool gameOver = false;
        bool invalidKey = false; 
        while (!gameOver) {
            if (_kbhit()) { 
                char input = _getch(); 
                invalidKey = false; 
                if ((input == 'w' || input=='W') && direction != 'S')
                    direction = 'W';
                else if ((input == 's' || input=='S') && direction != 'W')
                    direction = 'S';
                else if ((input == 'a' || input=='A') && direction != 'D')
                    direction = 'A';
                else if ((input == 'd' || input=='D') && direction != 'A')
                    direction = 'D';
                else
                    invalidKey = true; 
            }
            for (int i = snakeLength - 1; i > 0; i--) {
                snakeXPos[i] = snakeXPos[i - 1];
                snakeYPos[i] = snakeYPos[i - 1];
            }
            if (direction == 'W') 
                snakeY--;
            else if (direction == 'S') 
                snakeY++;
            else if (direction == 'A') 
                snakeX--;
            else if (direction == 'D') 
                snakeX++;
            snakeXPos[0] = snakeX;
            snakeYPos[0] = snakeY;
            if (snakeX == fruitX && snakeY == fruitY) {
                score++;
                snakeLength++;
                fruitX = rand() % (width - 2) + 1;
                fruitY = rand() % (height - 2) + 1;
            }

            if (snakeX < 1 || snakeX > width - 2 || snakeY < 1 || snakeY > height - 2) {
                gameOver = true;
            }
            for (int i = 1; i < snakeLength; i++) {
                if (snakeXPos[0] == snakeXPos[i] && snakeYPos[0] == snakeYPos[i]) {
                    gameOver = true;
                    break;
                }
            }
            setCursorPosition(0, 0); 
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    bool isSnake = false;
                    for (int k = 0; k < snakeLength; k++) {
                        if (snakeXPos[k] == j && snakeYPos[k] == i) {
                            isSnake = true;
                            break;
                        }
                    }
                    if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                        cout << "#";
                    }
                    else if (i == fruitY && j == fruitX) {
                        cout << "@";
                    }
                    else if (isSnake) {
                        cout << "o";
                    }
                    else {
                        cout << " ";
                    }
                }
                cout << endl;
            }
            cout << "Score: " << score << endl;
            if (invalidKey) {
                cout << "Invalid Key Entered!" << endl;
            } else {
                cout << "                         " << endl;
            }
            if (direction == 'W' || direction=='w' || direction == 'S' || direction=='s') {
                Sleep(400); 
            } else {
                Sleep(200); 
            }
        }
        system("cls"); 
        cout << "\n-----------------------------------------------------------------\n";
        cout << "|\t\t\t\t\t\t\t\t|";
        cout << "\n|\t\tGame Over! Final Score: " << score << "\t\t\t|"<< endl;
        cout << "|\t\t\t\t\t\t\t\t|";
        cout << "\n-----------------------------------------------------------------\n";
        cout << "\n\n\n Do You Want To Play Again (Y for yes / N for no) =  ";
        cin >> choice;
        c:
        if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
        {
           cout << "\n Invalid Choice Entered ";
           cout << "\n\n Enter Valid Choice Y for Yes / N for No = ";
           cin >> choice;
           goto c;
        }
        system("cls"); 
        cin.ignore(); 
    } while (choice == 'Y' || choice == 'y');
    system("cls");
    cout << "\n\n\t\t Thanks for Playing";
    return 0;
}

