#include "Tower6.h"
#include"GameControl.h"
QList<Card*> Tower6::cardList;
Tower6::Tower6() :MySide("D:\\tower\\to6ac2.gif", 200)
{
	Harm = 400;
	InitHarm = 200;
	mObjectType = GameObject::OT_Tower6;
	MyMov = new RoleAni("D:\\tower\\to6.gif", this);
	AttMov = new QMovie("D:\\tower\\to6at.gif");
	AceMov = new QMovie("D:\\tower\\to6ac.gif");
	BulletSendTimer = new QTimer;
	
	
	QObject::connect(AttackTimer, &QTimer::timeout, [=]()
		{if (AttState)
		return;
			AttackTimer->stop();
			MyMov->ChangeMov(AttMov);
			MyMov->moveBy(24, 128);
			BulletSendTimer->start(2600);
		});
	QObject::connect(AceEndTimer, &QTimer::timeout, [=]()
		{if (AttState)
		return;
			for (auto Bul : AceBulletList)
			{
				if (Bul->target != nullptr&& ((EnemySide*)(Bul->target))->isAlive)
					((EnemySide*)(Bul->target))->hurted(10000);
				Bul->Mov->stop();
				GameControl::Instance()->GameScene.removeItem(Bul);
				AceBulletList.removeOne(Bul);
				BulletList.append(Bul);
				Bul->target = nullptr;
			}
			AceEndTimer->stop();
			AceStartTimer->stop();
		});
	QObject::connect(AttMov, &QMovie::finished, [=]() {if (AttState)
		return;
		if (MP >= MaxMP)
		{
			MyAce();
			return;
		}
		AttMov->stop();
		MyMov->Play();
		AttackTimer->start(1000);
		if (level == 3)
			MP += 2000;
		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {if (AttState)
		return;
		for (auto mon : GameControl::Instance()->MonList1)
		{
			if (mon->MyMov->collidesWithItem(MyMov))
				mon->hurted(Harm);
			BulletSendTimer->stop();
		}});
	
	QObject::connect(AceStartTimer, &QTimer::timeout, [=]() {if (AttState)
		return;
	for (auto Bul : AceBulletList)
	{
		if(((EnemySide*)(Bul->target))->isAlive)
		Bul->setPos(((EnemySide*)(Bul->target))->MyMov->pos());
		else
		{
			Bul->Mov->stop();
			GameControl::Instance()->GameScene.removeItem(Bul);
			AceBulletList.removeOne(Bul);
			BulletList.append(Bul);
			Bul->target = nullptr;
		}
	}
		
		});
	QObject::connect(AceAttTimer, &QTimer::timeout, [=]() {if (AttState)
		return;
		for (auto mon : GameControl::Instance()->MonList1)
		{
			Bullet* Bul = getBullet();
			GameControl::Instance()->GameScene.addItem(Bul);
			Bul->Mov->start();
			Bul->target = (GameObject*)mon;
			Bul->setPos(mon->MyMov->pos());
			AceBulletList.append(Bul);
			AceAttTimer->stop();
			AceStartTimer->start(10);
		}
		AceAttTimer->stop();
		});
	QObject::connect(AceMov, &QMovie::finished, [=]() {if (AttState)
		return;
		
		
		AceMov->stop();
		MyMov->Play();
		AttackTimer->start(1000);
		});
		
	this->setPixmap(GameDefine::TowerUrl6_1);
	


}
Tower6::~Tower6()
{
}
void Tower6::init(QPoint _Pos, MapItem* _Map)
{
	MySide::init(_Pos,  _Map);
	
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

void Tower6::Reset()
{
	MySide::Reset();
	if(abs(MyMov->pos().y()-MyMov->Pos.y())>250)
		MyMov->moveBy(257, 198);
}

void Tower6::MyAce(MyScene* TargetScene)
{
	MySide::MyAce();
	MyMov->ChangeMov(AceMov);
	MyMov->moveBy(23, 30);
	
	AceAttTimer->start(500);
	
	AceEndTimer->start(4000);
}

