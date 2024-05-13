#pragma once
#include "EnemySide.h"
class Boss1 :
    public EnemySide
{
    public:
    Boss1();
    ~Boss1();
 
    QMovie* AceMov1;
    QMovie* AceMov2;
    QMovie* AceMov3;
    QMovie* AceMov4;
    QMovie* EnMov;
    QMovie* DeMov;
    void Enter();
};

