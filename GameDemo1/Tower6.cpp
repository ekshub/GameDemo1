#include "Tower6.h"
#include"GameControl.h"
QList<Card*> Tower6::cardList;
Tower6::Tower6() :MySide("", 200)
{
	Harm = 400;
	InitHarm = 200;
	mObjectType = GameObject::OT_Tower6;
	MyMov = new RoleAni("D:\\tower\\to6.gif", this);
	AttMov = new QMovie("D:\\tower\\to6at.gif");
	BulletSendTimer = new QTimer;
	QObject::connect(AttackTimer, &QTimer::timeout, [=]()
		{
			AttackTimer->stop();
			MyMov->ChangeMov(AttMov);
			MyMov->moveBy(-230, -70);
			BulletSendTimer->start(2600);
		});
	QObject::connect(AttMov, &QMovie::finished, [=]() {
		
		AttMov->stop();
		MyMov->Play();
		AttackTimer->start(1000);
		
		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {
		for (auto mon : GameControl::Instance()->MonList1)
		{
			if (mon->MyMov->collidesWithItem(MyMov));
			mon->hurted(Harm);
			BulletSendTimer->stop();
		}});
		
		
	this->setPixmap(GameDefine::TowerUrl6_1);
	


}
Tower6::~Tower6()
{
}
void Tower6::init(QPoint _Pos)
{
	MySide::init(_Pos);
	AttackTimer->start(1000);
	MyMov->moveBy(0, -10);
}

void Tower6::BulletMove()
{
}

void Tower6::Recover()
{
	MySide::Recover();
	BulletSendTimer->stop();
	AttMov->stop();
}

void Tower6::MyAce(MyScene* TargetScene)
{
}

