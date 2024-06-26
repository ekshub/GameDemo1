#include "Monster2.h"
#include"GameControl.h"
Monster2::Monster2(QObject* parent):EnemySide(parent)
{
	this->mObjectType = GameObject::OT_Monster1;
	MaxHP = GameDefine::MonHP2;
	MyMov = new RoleAni(GameDefine::MonMov2);
	AttMov = new QMovie(GameDefine::MonAtt2);
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

void Monster2::MyAdjust()
{
	moveBy(-34, 36);

}
