#ifndef OBJECT_H
#define OBJECT_H

#include <conio.h>
#include <iostream>
#include <vector>
using namespace std;

class CObject
{
protected:
    int m_x, m_y;
public:
    void GoPosition();
    void SetPosition(int x, int y);
    void GetPosition(int &x, int &y);
};

#endif
