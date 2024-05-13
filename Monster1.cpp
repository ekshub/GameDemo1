#include "Monster1.h"
Monster1::Monster1(QObject* parent)
{
	this->mObjectType = GameObject::OT_Monster1;
	this->MaxHP = 10000;
}
void Monster1::init(QPoint _Pos)
{
	
	this->Pos = _Pos;
	setPos(_Pos);
	this->MyMov->setPos(Pos);
	this->HP = 10000;
	HPBar = new QProgressBar;
	HPBar->setValue(100);
	
	this->HPBar->setFixedSize(50, 10);
	this->HPBar->setStyleSheet("QProgressBar{border:0px}");
	MyMov->Mov->start();
}