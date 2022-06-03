#include <conio.h>
#include <iostream>
#include <vector>
using namespace std;

#include "snake.h"
#include "object.h"

int nBorderSize;

CSnake::CSnake()
{
    m_IsDead = false;
}

void CSnake::CreateSnake(int Start, int BorderSize, KEY &nKey)
{
    m_listTails.push_back(CnTails(Start, Start, true));
    int r = rand() % 4 + 1;
    if (r == 1)
    {
        m_listTails.push_back(CnTails(Start, Start - 1, false));
        m_listTails.push_back(CnTails(Start, Start - 2, false));
        nKey = DOWN;
    }
    else if (r == 2)
    {
        m_listTails.push_back(CnTails(Start, Start + 1, false));
        m_listTails.push_back(CnTails(Start, Start + 2, false));
        nKey = UP;
    }
    else if (r == 3)
    {
        m_listTails.push_back(CnTails(Start - 1, Start, false));
        m_listTails.push_back(CnTails(Start - 2, Start, false));
        nKey = RIGHT;
    }
    else
    {
        m_listTails.push_back(CnTails(Start + 1, Start, false));
        m_listTails.push_back(CnTails(Start + 2, Start, false));
        nKey = LEFT;
    }

    SetOppositeKey(nKey);
    nBorderSize = BorderSize;
}

bool CSnake::IsDead()
{
    return m_IsDead;
}

bool CSnake::IsHit(int x, int y)
{
    if (x > nBorderSize - 2 || x < 1 || y > nBorderSize - 2 || y < 1)
    {
        return true;
    }

    int TailX, TailY;

    for (int i = 1; i < m_listTails.size(); i++)
    {
        m_listTails[i].GetPosition(TailX, TailY);
        if (x == TailX && y == TailY) return true;
    }
    
    return false;
}

bool CSnake::AteFruit(int FruitX, int FruitY)
{
    CnTails& iTails = m_listTails[0];
    int HeadX = 0, HeadY = 0;
    iTails.GetPosition(HeadX, HeadY);
    
    if (FruitX == HeadX && FruitY == HeadY)
   {
        int x, y;
        int Last_Tail = m_listTails.size() - 1;
        m_listTails[Last_Tail].GetPosition(x, y);
        m_listTails.push_back(CnTails(x, y, false));
        
        return true;
    }
    
    return false;
}

void CSnake::SetOppositeKey(KEY nKey)
{
    switch (nKey)
    {
    case UP:
        m_OppositeKey = DOWN;
        break;
    case DOWN:
        m_OppositeKey = UP;
        break;
    case LEFT:
        m_OppositeKey = RIGHT;
        break;
    case RIGHT:
        m_OppositeKey = LEFT;
        break;
    default:
        break;
    }
}


void CSnake::Update(KEY nKey)
{
    if (nKey == NONE) return;
    int x, y;
    CnTails frontTail;

    for (int i = 0; i < m_listTails.size(); i++) {

        CnTails& iTails = m_listTails[i];

        if (iTails.IsHead()) {

            iTails.GetPosition(x, y);
            if (m_OppositeKey == nKey)
            {
                switch (nKey)
                {
                case UP:
                    nKey = DOWN;
                    break;
                case DOWN:
                    nKey = UP;
                    break;
                case LEFT:
                    nKey = RIGHT;
                    break;
                case RIGHT:
                    nKey = LEFT;
                    break;
                default:
                    break;
                }
            }

            if (IsHit(x, y))
            {
                m_IsDead = true;
                return;
            }

            frontTail = iTails;
            
            switch (nKey)
            {
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            default:
                break;
            }
            SetOppositeKey(nKey);
            
            
            iTails.SetPosition(x, y);
        }
        else {

           frontTail.GetPosition(x, y);
           frontTail = iTails;
           iTails.SetPosition(x, y);
        }
    }
}




void CSnake::Draw()
{
    for (CnTails iTails : m_listTails)
    {
        iTails.Draw();
    }
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