#include "Tower3.h"
#include"GameControl.h"
QList<Card*> Tower3::cardList;
Tower3::Tower3() :MySide("D:\\tower\\to3ac2.gif", 200)
{
	mObjectType = GameObject::OT_Tower3;
	MyMov = new RoleAni("D:\\tower\\to3.gif", this);
	AttMov = new QMovie("D:\\tower\\to3at.gif");
	AceMov = new QMovie("D:\\tower\\to3ac.gif");
	this->setPixmap(GameDefine::TowerUrl3_1);
	BulletSendTimer = new QTimer;
	Harm = 1000;
	InitHarm = 200;
	for (auto i : BulletList)
	{
		
		QObject::connect(i->Mov, &QMovie::finished, [=]() {
			if (AttState)
				return;
			i->Mov->stop();
			GameControl::Instance()->GameScene.removeItem(i);
			TracingBulletList.removeOne(i);
			BulletList.append(i);
			i->target->HP += Harm;
			((MySide*)(i->target))->MP += 200;
			i->target = nullptr;
			});
	}
	QObject::connect(AttMov, &QMovie::finished, [=]() {
		if (AttState)
		return;
		AttMov->stop();
		MyMov->Play();

		AttackTimer->start(2000);
		});
	QObject::connect(AceMov, &QMovie::finished, [=]() {
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
		if (AttState&& GameControl::Instance()->MonList1.isEmpty())
			return;
		AttackTimer->stop();
		//BulletSendTimer->start(600);
		if (MP >= MaxMP)
		{
			MyAce();
			return;
		}
		MyMov->ChangeMov(AttMov);
		if (level == 1)
			MP += 2000;
		});
	QObject::connect(AceStartTimer, &QTimer::timeout, [=]() {
		if (AttState)
			return;
		});
}
Tower3::~Tower3()
{
}
void Tower3::init(QPoint _Pos, MapItem* _Map)
{
	MySide::init(_Pos,  _Map);
	
	
}

void Tower3::BulletMove()
{
	for (auto Bul : TracingBulletList)
		Bul->setPos(((MySide*)(Bul->target))->MyMov->Pos - QPoint(82, 150));
}

void Tower3::Reset()
{
	MySide::Reset();
	if (MyMov->Pos.y() - MyMov->pos().y() ==359)
		MyMov->moveBy(65, 216);
}

void Tower3::MyAce(MyScene* TargetScene)
{
	MySide::MyAce();
	MyMov->ChangeMov(AceMov);
	for (auto tow : GameControl::Instance()->MySideList)
	{
		Bullet* Bul = getBullet();
		TracingBulletList.append(Bul);
		Bul->target = tow;
		Bul->Mov->start();
		GameControl::Instance()->GameScene.addItem(Bul);
		Bul->setPos(tow->MyMov->Pos-QPoint(82,150));
	}
}
