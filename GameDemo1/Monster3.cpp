#include "Monster3.h"
#include"GameControl.h"
Monster3::Monster3(QObject* parent):EnemySide(parent)
{
	mObjectType = GameObject::OT_Monster1;
    MaxHP = GameDefine::MonHP3;
	MyMov = new RoleAni(GameDefine::MonMov3);
	AttMov = new QMovie(GameDefine::MonAtt3);
    QObject::connect(AttMov, &QMovie::finished, [=]() {
        for (auto tow : GameControl::Instance()->MySideList)
        {
            if (MyMov->Pos.x() + MyMov->size().width() / 2 - tow->MyMov->Pos.x() < 100 && MyMov->Pos.x() + MyMov->size().width() / 2 - tow->MyMov->Pos.x() > -20 && -MyMov->Pos.y()  + tow->MyMov->Pos.y() < 100 && -MyMov->Pos.y()  + tow->MyMov->Pos.y() > -20)
            {
                tow->HP -= 200;
            }

        }
        AttMov->stop();
        MyMov->Play();
        isAtting = false;
        });
}

void Monster3::MyAdjust()
{
	
}
