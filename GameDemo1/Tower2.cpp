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
		AttMov->stop();
		MyMov->Play();

		AttackTimer->start(2000);
		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {
		
		});
	QObject::connect(AttackTimer, &QTimer::timeout, [=]() {

		//BulletSendTimer->start(600);
		if (count < 5)
		{
			MyMov->ChangeMov(AttMov);
			MyMov->moveBy(-30, -93);
			AttackTimer->stop();
			count+=5;
		}
		else
		{
			MyAce(&GameControl::Instance()->GameScene);
			count = 0;
		}
		});
}
Tower2::~Tower2()
{
}
void Tower2::init(QPoint _Pos)
{
	MySide::init(_Pos);
	MyMov->moveBy(0,-30);
}

void Tower2::BulletMove()
{
}

void Tower2::MyAce(MyScene* TargetScene)
{
	AttackTimer->stop();
	MyMov->ChangeMov(AceMov);
	MyMov->moveBy(-20, -60);
	if (isBound == false)
	{
		isBound = true;
		QObject::connect(AceMov, &QMovie::finished, [=]() {
		int count = 0;
		for (auto i : AceBulletList)
		{
			i->Mov->start();
			i->setPos(QPoint(0, 100) * count);
			TargetScene->addItem(i);
			count++;
		}
		AceAttTimer->start(10);
		 });
		QObject::connect(AceAttTimer, &QTimer::timeout, [=]() {
			for (auto Bul : AceBulletList)
			{
				Bul->moveBy(2, 0);
				for(auto mon:GameControl::Instance()->MonList1)
				if (Bul->collidesWithItem(mon->MyMov))
				{
					Bul->count = rand() % GameControl::Instance()->MonList1.size();
					mon->BloodVolume -= 10;
					mon->BloodBar->setValue(mon->BloodVolume * 100 / mon->MaxBlood);
				}
			}
			if (AceBulletList[0]->pos().x()>1000)
			{
				AceMov->stop();
				MyMov->Play();
				for (auto i : AceBulletList)
				{
					TargetScene->removeItem(i);
				}
				AceAttTimer->stop();
				AttackTimer->start(3000);
			}
			});
		
	}

}
