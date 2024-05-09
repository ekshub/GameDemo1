#include "Monster1.h"
Monster1::Monster1(QObject* parent)
{
	this->mObjectType = GameObject::OT_Monster1;
	this->img = QPixmap(GameDefine::MonsterUrl1);
	this->MaxBlood = 10000;
	this->setPixmap(img);
	
}
void Monster1::init(QPoint _Pos)
{
	_dir = QPoint(1, 0) * MoveSpeed;
	this->Pos = _Pos;
	setPos(_Pos);
	this->MyMov->setPos(Pos);
	this->BloodVolume = 10000;
	BloodBar = new QProgressBar;
	BloodBar->setValue(100);
	
	this->BloodBar->setFixedSize(50, 10);
	this->BloodBar->setStyleSheet("QProgressBar{border:0px}");
	MyMov->Mov->start();
}