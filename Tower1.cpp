#include "Tower1.h"
#include"GameControl.h"

QList<Card*> Tower1::cardList ;
Tower1::Tower1() :MySide("D:\\tower\\to1att.gif", 200)
{
	mObjectType = GameObject::OT_Tower1;
	MyMov = new RoleAni("D:\\tower\\to1.gif");
	AttMov = new QMovie("D:\\tower\\to1at.gif");
	AceMov = new QMovie("D:\\tower\\to1ace.gif");
	BulletSendTimer = new QTimer;
	this->setPixmap(GameDefine::TowerUrl1_1);
	InitHarm = 200;
	Harm = 200;
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
		if (AttState)
			return;
		AttackTimer->stop();
		//BulletSendTimer->start(600);
		if (MP >= MaxMP)
		{
			MyAce();
			return;
		}
		MyMov->ChangeMov(AttMov);
		MyMov->moveBy(29, 0);
		if (level == 3)
			MP += 2000;
		});
	QObject::connect(AceStartTimer, &QTimer::timeout, [=]() {
		if (AttState)
			return;
		});
}
void Tower1::init(QPoint _Pos, MapItem* _Map)
{
	MySide::init(_Pos, _Map);
	
}

void Tower1::Reset()
{

}

void Tower1::BulletMove()
{
	for (auto Bul : TracingBulletList)
		Bul->moveBy(5, 0);
}

Tower1::~Tower1()
{
	

	for (auto i : TracingBulletList)
	{
		TracingBulletList.removeOne(i);
		delete i;
	}
	
}

void Tower1::MyAce(MyScene* TargetScene)
{

	MySide::MyAce();
	MyMov->ChangeMov(AceMov,RoleAni::CenterAlign);
	
}