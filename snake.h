#ifndef SNAKE_H
#define SNAKE_H

#include <conio.h>
#include <iostream>
#include <vector>
using namespace std;

#include "nTails.h"
#include "key.h"

class CSnake : public CObject
{
private:
    vector<CnTails> m_listTails;
    bool m_IsDead;
    bool m_AteFruit;
    KEY m_OppositeKey;

public:
    CSnake();

    void CreateSnake(int Middle, int BorderSize, KEY &nKey);
    void Update(KEY nKey);
    void Draw();
    bool IsHit(int x, int y);
    bool IsDead();
    bool AteFruit(int HeadX, int HeadY);
    void SetOppositeKey(KEY nKey);

};


#endif


































































