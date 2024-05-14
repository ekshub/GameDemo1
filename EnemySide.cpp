#include "EnemySide.h"
#include"GameControl.h"

EnemySide::EnemySide(QObject* parent)
{
    MyMov = nullptr;
    MoveSpeed = 1;
    HPBar = nullptr;
    AttMov = nullptr;
    Actived=true;
    isAlive = false;
}
void EnemySide::init(QPoint _Pos)
{

    Pos = _Pos;
    setPos(_Pos);
    MyMov->setPos(Pos);
    MyMov->Pos = (Pos);
    HP = MaxHP;
    HPBar = new QProgressBar;
    HPBar->setValue(100);
    HPBar->setFixedSize(50, 10);
    HPBar->setStyleSheet("QProgressBar{border:0px}");
    MyMov->Play();
}
EnemySide::~EnemySide()
{
    if(HPBar!=nullptr)
    delete HPBar;
    delete MyMov;
}

void EnemySide::Move()
{
    if (Actived == false|| isAtting==true)
    {

        Actived = true;
        return;
    }
    for (auto tow : GameControl::Instance()->MySideList)
    {
        if (MyMov->Pos.x()  - tow->MyMov->Pos.x() < 100 && MyMov->Pos.x() - tow->MyMov->Pos.x() > -20 && -MyMov->Pos.y()  + tow->MyMov->Pos.y() < 100 && -MyMov->Pos.y()  + tow->MyMov->Pos.y() > -20)
        {
            Actived = false;
            isAtting = true;
            MyMov->ChangeMov(AttMov);
            MyAdjust();

            break;
        }
    }
    if (Actived)
    {
        Pos += QPoint(-1, 0) * MoveSpeed;
        MyMov->moveBy(-MoveSpeed, 0);
        MyMov->Pos -= QPoint(MoveSpeed, 0);
        HPBar->move(MyMov->Pos + QPoint(-50, -120));
    }

    
}



void EnemySide::hurted(int Harm)
{
    HP -= Harm;
    HPBar->setValue(HP * 100 /MaxHP);
}

void EnemySide::MyAdjust()
{
}

void EnemySide::death()
{

}


