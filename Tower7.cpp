#include "Tower7.h"
#include"GameControl.h"
QList<Card*> Tower7::cardList;
Tower7::Tower7() :MySide("D:\\tower\\too7at.gif", 1)
{
	mObjectType = GameObject::OT_Tower7;
	MyMov = new RoleAni("D:\\tower\\to7.gif", this);
	BulletSendTimer = new QTimer;
	AttMov = new QMovie("D:\\tower\\to7at.gif");
	AceMov = new QMovie("D:\\tower\\to7ac.gif");
	this->setPixmap(GameDefine::TowerUrl7_1);
	Harm = 1;
	InitHarm = 1;
	int acount;
	
	for (auto i : BulletList)
	{
		QObject::connect(i->Mov, &QMovie::finished, [=]() {if (AttState)
			return;
			i->Mov->stop();
			GameControl::Instance()->GameScene.removeItem(i);
			TracingBulletList.removeOne(i);
			BulletList.append(i);
			
			});
	}
	QObject::connect(AttackTimer, &QTimer::timeout, [=]()
		{if (AttState|| GameControl::Instance()->MonList1.isEmpty())
		return;
			AttackTimer->stop();
			MyMov->ChangeMov(AttMov);
			MyMov->moveBy(0, 34);
			BulletSendTimer->start(2600);
		});
	QObject::connect(AttMov, &QMovie::finished, [=]() {if (AttState)
		return;
		if (MP >= MaxMP)
		{
			MyAce();
			return;
		}
		if (level == 3)
		{
			MP += 2000;
		}
		AttMov->stop();
		MyMov->Play();
		AttackTimer->start(5000);
		
		});
	QObject::connect(AceMov, &QMovie::finished, [=]() {if (AttState)
		return;
		for (int i = 0; i < 5; i++)
		{
			Bullet* Bul = getBullet();
			GameControl::Instance()->GameScene.addItem(Bul);
			Bul->Mov->start();
			TracingBulletList.append(Bul);
			Bul->setPos(GameControl::Instance()->MonList1[0]->MyMov->pos().x()-100  , i * 100);
		}
		AceMov->stop();
		MyMov->Play();
		AttackTimer->start(5000);
		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {if (AttState|| GameControl::Instance()->MonList1.isEmpty())
		return;
			Bullet* Bul = getBullet();
			GameControl::Instance()->GameScene.addItem(Bul);
			Bul->Mov->start();
			Bul->setPos(GameControl::Instance()->MonList1[0]->MyMov->pos()-QPoint(50,0));
			TracingBulletList.append(Bul);
		BulletSendTimer->stop();
		});

}
Tower7::~Tower7()
{
	
}
void Tower7::init(QPoint _Pos, MapItem* _Map)
{
	MySide::init(_Pos,_Map);
	
}

void Tower7::BulletMove()
{
}

void Tower7::MyAce(MyScene* TargetScene)
{
	MySide::MyAce();
	MyMov->ChangeMov(AceMov);
	MyMov->moveBy(25, 164);
}

void Tower7::Reset()
{
	MySide::Reset();
	if (MyMov->Pos.y() - MyMov->pos().y() > 100)
		MyMov->moveBy(39, 58);
}

