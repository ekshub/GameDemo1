#include "Tower2.h"
#include"GameControl.h"

QList<Card*> Tower2::cardList;
Tower2::Tower2() :MySide("",200)
{
	count = 0;
	mObjectType = GameObject::OT_Tower2;
	MyMov = new RoleAni("D:\\tower\\to2.gif", this);
	AttMov = new QMovie("D:\\tower\\to2at.gif");
	AceMov = new QMovie("D:\\tower\\to2ace.gif");
	this->setPixmap(GameDefine::TowerUrl1_1);
	Harm = 1000;
	InitHarm = 200;
	for (int i = 0; i < 5; i++)
	{
		Bullet* Bul = new Bullet("D:\\Monster\\wolf2.gif", this);
		Bul->Harm = this->Harm;
		AceBulletList.append(Bul);
	}
	BulletSendTimer = new QTimer;
	QObject::connect(AttMov, &QMovie::finished, [=]() {
		if (AttState)
			return;
		AttMov->stop();
		MyMov->Play();

		AttackTimer->start(2000);
		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {
		if (AttState)
			return;
		});
	QObject::connect(AttackTimer, &QTimer::timeout, [=]() {
		if (AttState)
			return;
		//BulletSendTimer->start(600);
		if (count < 5)
		{
			MyMov->ChangeMov(AttMov);
			AttackTimer->stop();
			if(level==3)
			count+=1;
		}
		else
		{
			MyAce();
			count = 0;
		}
		});
	QObject::connect(AceMov, &QMovie::finished, [=]() {
		if (AttState)
			return;
		int count = 0;
		for (auto i : AceBulletList)
		{
			i->Mov->start();
			i->setPos(QPoint(0, 100) * count);
			GameControl::Instance()->GameScene.addItem(i);
			count++;
		}
		AceAttTimer->start(10);
		});
	QObject::connect(AceAttTimer, &QTimer::timeout, [=]() {
		if (AttState)
			return;
		for (auto Bul : AceBulletList)
		{
			Bul->moveBy(2, 0);
			for (auto mon : GameControl::Instance()->MonList1)
				if (Bul->collidesWithItem(mon->MyMov))
				{
					Bul->count = rand() % GameControl::Instance()->MonList1.size();
					mon->HP -= 10;
					mon->HPBar->setValue(mon->HP * 100 / mon->MaxHP);
				}
		}
		if (AceBulletList[0]->pos().x() > 1000)
		{
			AceMov->stop();
			MyMov->Play();
			for (auto i : AceBulletList)
			{
				GameControl::Instance()->GameScene.removeItem(i);
			}
			AceAttTimer->stop();
			AttackTimer->start(3000);
		}
		});

}
Tower2::~Tower2()
{
}
void Tower2::Reset()
{
	MySide::Reset();
	if (MyMov->Pos.y() - MyMov->pos().y() > 250)
		MyMov->moveBy(50, 145);
}
void Tower2::init(QPoint _Pos, MapItem* _Map)
{
	MySide::init(_Pos,  _Map);
}

void Tower2::BulletMove()
{
}

void Tower2::MyAce(MyScene* TargetScene)
{
	MySide::MyAce();
	AttackTimer->stop();
	MyMov->ChangeMov(AceMov);
	MyMov->moveBy(-20, -60);
}

void Tower2::Upgrade()
{
	MySide::Upgrade();
	
}
