#pragma once
#include "EnemySide.h"

class Monster3 :
    public EnemySide
{
public:
    Monster3(QObject* parent);
    void MyAdjust();
};

