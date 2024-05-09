#include "EnemySide.h"

EnemySide::EnemySide(QObject* parent)
{
    MoveSpeed = 1;
    BloodBar = nullptr;
    MyMov = new RoleAni("D:\\Qt_code\\spritesheets\\spritesheets\\Monster-1.gif", this);
    Actived=true;
    
}

EnemySide::~EnemySide()
{
    if(BloodBar!=nullptr)
    delete BloodBar;
    delete MyMov;
}

void EnemySide::Move()
{
    
  /*  if (_dir == QPoint(1, 0) * MoveSpeed)
    {
        
        Pos += _dir;
        MyMov->moveBy(_dir.x() , _dir.y());
        if ((Pos + _dir).x() > 800 - img.width())
            _dir = QPoint(0, 1) * MoveSpeed;

    }
    else if (_dir == QPoint(0, 1) * MoveSpeed)
    {

        Pos += _dir;
        MyMov->moveBy(_dir.x() , _dir.y());
        if ((Pos + _dir).y() > 505 - img.height())
            _dir = QPoint(-1, 0) * MoveSpeed;

    }
    else if (_dir == QPoint(-1, 0) * MoveSpeed)
    {

        Pos += _dir;
        MyMov->moveBy(_dir.x(), _dir.y() );
        if ((Pos + _dir).x() < 50)
            _dir = QPoint(0, -1) * MoveSpeed;

    }
    else if (_dir == QPoint(0, -1) * MoveSpeed )
    {

        Pos += _dir;
        MyMov->moveBy(_dir.x() , _dir.y() );
        if ((Pos + _dir).y() < 70)
            _dir = QPoint(1, 0) * MoveSpeed;

    }*/
    Pos += QPoint(-1,0) * MoveSpeed;
    MyMov->moveBy(-MoveSpeed,0);
    BloodBar->move(Pos + QPoint(0, -20));
}

bool EnemySide::IsBloodEmpty()
{
    if (this->BloodVolume <= 0)
        return true;
    return false;
}

void EnemySide::hurted(int Harm)
{
    BloodVolume -= Harm;
    BloodBar->setValue(BloodVolume * 100 /MaxBlood);
}
