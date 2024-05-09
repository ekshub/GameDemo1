#include "Tower3.h"
#include"GameControl.h"
QList<Card*> Tower3::cardList;
Tower3::Tower3() :MySide("D:\\tower\\toa3.gif", 200)
{
	mObjectType = GameObject::OT_Tower3;
	MyMov = new RoleAni("D:\\tower\\to3.gif", this);
	AttMov = new QMovie("D:\\tower\\to3at.gif");
	this->setPixmap(GameDefine::TowerUrl3_1);
	BulletSendTimer = new QTimer;
	Harm = 1000;
	InitHarm = 200;
	QObject::connect(AttMov, &QMovie::finished, [=]() {
		AttMov->stop();
		MyMov->Play();

		AttackTimer->start(2000);
		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {
		
		});
	QObject::connect(AttackTimer, &QTimer::timeout, [=]() {

		//BulletSendTimer->start(600);

		MyMov->ChangeMov(AttMov);

		MyMov->moveBy(0,30);
		AttackTimer->stop();
		});
	
}
Tower3::~Tower3()
{
}
void Tower3::init(QPoint _Pos)
{
	MySide::init(_Pos);
	AttackTimer->start(2000);
	MyMov->moveBy(0, -40);
}

void Tower3::BulletMove()
{
}

void Tower3::MyAce(MyScene* TargetScene)
{
}
