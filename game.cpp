#include <conio.h>
#include <iostream>
#include <vector>
using namespace std;

#include "game.h"
#include "windows.h"
#include "object.h"

CGame::CGame(int nBorderSize)
{
    HideCursor();
    m_iBorder.CreateBorder(nBorderSize);
    m_iFruit.CreateFruit(rand() % (nBorderSize - 2) + 1, rand() % (nBorderSize - 2) + 1);
    m_iSnake.CreateSnake(rand() % (18 - 13) + 13, nBorderSize, m_nKey);
    m_BorderSize = nBorderSize;
}

void CGame::SetGameOver(bool IsOver)
{
    m_GameOver = IsOver;
}

bool CGame::GetGameOver()
{
    return m_GameOver;
}

void CGame::GetInput()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            m_nKey = UP;
            break;
        case 's':
            m_nKey  = DOWN;
            break;
        case 'a':
            m_nKey = LEFT;
            break;
        case 'd':
            m_nKey = RIGHT;
            break;
        default:
            break;
        }
   }
}
void CGame::Update()
{
    m_iSnake.Update(m_nKey);

    if (m_iSnake.IsDead()) {
        m_GameOver = true;
    }

    int x, y;
    m_iFruit.GetPosition(x, y);

    if (m_iSnake.AteFruit(x, y))
    {
        m_iScore.m_Score += 100000;
        m_iFruit.CreateFruit(rand() % (m_BorderSize - 2) + 1, rand() % (m_BorderSize - 2) + 1);
    }
}
void CGame::Draw()
{
    system("cls");
    m_iBorder.Draw();
    m_iFruit.Draw();
    m_iSnake.Draw();
    m_iScore.Draw();                                                                     
}

void CGame::HideCursor()
{
   CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}















































































/*bool gameover;
const int HEIGHT = 20;
const int WIDTH = 50;
int x, y, appleX, appleY, score = 0, num_tails = 0;
int tailX[100], tailY[100];
enum directions {STOP = 0, UP, DOWN, LEFT, RIGHT};
directions dir;
void setup()
{
    x = WIDTH / 2;
    y = HEIGHT / 2;
    srand(static_cast<unsigned int> (time(0)));
    appleX = rand() % WIDTH - 3;
    appleY = rand() % HEIGHT;
}

void print()
{
    cout << "SCORE: " << score << endl << endl;
    for (int i = 0; i < WIDTH; i++)
    {
        cout << "#";
    }

    cout << endl;

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {

            if (j == 0) cout << "#";
            else if (j == WIDTH - 2) cout << "#";

            if (i == appleY && j == appleX) cout << "A";
            else if (i == y && j == x) cout << "O";
            else
            {
                bool print = false;
                for (int k = 0; k < num_tails; k++)
                {  
                    print = false;
                    if (tailX[k] == j && tailY[k] == i) cout << "o"; print = true; 
                }
                if (!print)
                {
                    cout << " ";
                    print = false;
                }
            }
            
        }
        cout << endl;
    }
    for (int i = 0; i < WIDTH; i++)
    {
        cout << "#";
    }
   
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        default:
            break;
        }
    }

 
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    
    for (int i = 1; i < num_tails; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case UP:
        y--;
        break;
    case LEFT:
        x--;
        break;
    case DOWN:
        y++;
        break;
    case RIGHT:
        x++;
        break;
    }

    if (x > WIDTH - 3 || x < 0 || y > HEIGHT || y < 0) gameover = true;
 
    if (x == appleX && y == appleY)
    {
        score += 100;
        appleX = rand() % WIDTH - 3;
        appleY = rand() % HEIGHT;
        num_tails++;
    }
    
}

int main()
{
    setup();
    
    while (!gameover)
    {
        system("cls");
        print();
        input();
        logic();
    }
}
*/