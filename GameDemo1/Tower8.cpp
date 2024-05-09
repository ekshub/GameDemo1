#include "Tower8.h"
#include"GameControl.h"
QList<Card*> Tower8::cardList;
Tower8::Tower8() :MySide("", 200)
{
	mObjectType = GameObject::OT_Tower8;
	MyMov = new RoleAni("D:\\tower\\to8.gif", this);
	AttMov = new QMovie("D:\\tower\\to8at.gif");
	AttMov2=new QMovie("D:\\tower\\to8at2.gif");
	BulletSendTimer = new QTimer;
	this->setPixmap(GameDefine::TowerUrl8_1);
	Harm = 1000;
	Harm2 = 2000;
	InitHarm = 200;
	state = true;
	QObject::connect(AttackTimer, &QTimer::timeout, [=]()
		{
			if (!GameControl::Instance()->MonList1.isEmpty())
			{
				AttackTimer->stop();
				if (state)
				{
					MyMov->ChangeMov(AttMov);
					BulletSendTimer->start(2000);
				}
				else
				{
					MyMov->ChangeMov(AttMov2);
					BulletSendTimer->start(700);
				}
				state = !state;
				MyMov->setPos(GameControl::Instance()->MonList1[rand() % GameControl::Instance()->MonList1.size()]->MyMov->pos() - QPoint(150, 0));
				
			}
		});
	QObject::connect(AttMov, &QMovie::finished, [=]() {

		AttMov->stop();
		MyMov->Play();
		AttackTimer->start(1000);

		});
	QObject::connect(AttMov2, &QMovie::finished, [=]() {

		AttMov->stop();
		MyMov->Play();
		AttackTimer->start(1000);

		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {
		int temp;
		if (state)
			temp = Harm;
		else
			temp = Harm2;
		for (auto mon : GameControl::Instance()->MonList1)
		{
			if (mon->MyMov->collidesWithItem(MyMov));
			mon->hurted(temp);
			BulletSendTimer->stop();
		}});

}
Tower8::~Tower8()
{
}
void Tower8::init(QPoint _Pos)
{
	MySide::init(_Pos);
	AttackTimer->start(1000);
}

void Tower8::BulletMove()
{
}

void Tower8::MyAce(MyScene* TargetScene)
{
}

