#include "Tower8.h"
#include"GameControl.h"
QList<Card*> Tower8::cardList;
Tower8::Tower8() :MySide(GameDefine::TowBul8, GameDefine::TowHarm8)
{
	MaxHP = GameDefine::TowHP8;
	MaxMP = GameDefine::TowMP8;
	mObjectType = GameObject::OT_Tower8;
	MyMov = new RoleAni(GameDefine::TowMov8, this);
	AttMov = new QMovie(GameDefine::TowAttMov8);
	AceMov = new QMovie(GameDefine::TowAceMov8);
	AttMov2=new QMovie(GameDefine::TowAtt2Mov8);
	BulletSendTimer = new QTimer;
	this->setPixmap(GameDefine::TowerUrl8_1);
	Harm = GameDefine::TowHarm5;
	Harm2 = GameDefine::TowHarm5*2;
	state = true;
	QObject::connect(AttackTimer, &QTimer::timeout, [=]()
		{if (AttState)
		return;
			if (!GameControl::Instance()->MonList1.isEmpty())
			{
				AttackTimer->stop();
				if (state)
				{
					MyMov->ChangeMov(AttMov);
					BulletSendTimer->start(1700);
					if (level == 3)
						AceStartTimer->start(1700);
				}
				else
				{
					MyMov->ChangeMov(AttMov2);
					BulletSendTimer->start(700);
					if (level == 3)
						AceStartTimer->start(700);
				}
				state = !state;
				MyMov->setPos(GameControl::Instance()->MonList1[rand() % GameControl::Instance()->MonList1.size()]->MyMov->pos() - QPoint(150, 0));
				
					
			}
		});
	QObject::connect(AceStartTimer, &QTimer::timeout, [=]()
		{if (AttState)
		return;
			MyAce();
			AceStartTimer->stop();
		});
	QObject::connect(AttMov, &QMovie::finished, [=]() {
		if (AttState)
			return;
		AttMov->stop();
		MyMov->Play();
		AttackTimer->start(1000);

		});
	QObject::connect(AttMov2, &QMovie::finished, [=]() {
		if (AttState)
			return;
		AttMov->stop();
		MyMov->Play();
		AttackTimer->start(1000);

		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {if (AttState)
		return;
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
	delete AttMov2;
}
void Tower8::init(QPoint _Pos,  MapItem* _Map )
{
	MySide::init(_Pos,  _Map);
	
}

void Tower8::BulletMove()
{
	for (auto Bul : TracingBulletList)
		Bul->moveBy(5,0);
}

void Tower8::MyAce(MyScene* TargetScene)
{
	MySide::MyAce();
	if (state) {
		Bullet* Bul = getBullet();
		GameControl::Instance()->GameScene.addItem(Bul);
		Bul->Mov->start();
		Bul->setPos(MyMov->pos() + QPoint(70, 0));
		TracingBulletList.append(Bul);
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			Bullet* Bul = getBullet();
			GameControl::Instance()->GameScene.addItem(Bul);
			Bul->Mov->start();
			Bul->setPos(MyMov->pos() + QPoint(70, (i-1)*100));
			TracingBulletList.append(Bul);
		}
	}
}

void Tower8::Reset()
{
	
}

