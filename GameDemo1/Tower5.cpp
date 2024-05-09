#include "Tower5.h"
#include"GameControl.h"
QList<Card*> Tower5::cardList;
Tower5::Tower5() :MySide("D:\\tower\\toa3.gif", 200)
{
	mObjectType = GameObject::OT_Tower5;
	MyMov = new RoleAni("D:\\tower\\to5.gif", this);
	AttMov = new QMovie("D:\\tower\\to5at.gif");
	AttMov->setSpeed(150);
	AceMov = new QMovie("D:\\tower\\to5ace.gif");
	this->setPixmap(GameDefine::TowerUrl5_1);
	BulletSendTimer = new QTimer;
	Harm = 1000;
	InitHarm = 200;

	QObject::connect(AttMov, &QMovie::finished, [=]() {
		AttMov->stop();
		MyMov->Play();
		
		AttackTimer->start(200);
		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {
		for (auto mon : GameControl::Instance()->MonList1)
		{
			if (mon->MyMov->collidesWithItem(MyMov));
			mon->hurted(Harm);
			BulletSendTimer->stop();
		}
		});
	QObject::connect(AttackTimer, &QTimer::timeout, [=]() {
		
		BulletSendTimer->start(600);
		
		MyMov->ChangeMov(AttMov);
		
		MyMov->moveBy(-150, -82);
		AttackTimer->stop();
		});
}
Tower5::~Tower5()
{
}
void Tower5::init(QPoint _Pos)
{
	MySide::init(_Pos);
	AttackTimer->start(1000);
	MyMov->moveBy(0,-34);
}

void Tower5::BulletMove()
{
}

void Tower5::MyAce(MyScene* TargetScene)
{
	MyMov->setPos(0, 0);
	MyMov->ChangeMov(AceMov);
	MyMov->Lab->resize(1400, 800);
}

