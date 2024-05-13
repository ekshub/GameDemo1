#include "Tower1.h"
#include"GameControl.h"

QList<Card*> Tower1::cardList ;
Tower1::Tower1() :MySide(GameDefine::TowBul1, GameDefine::TowHarm1)
{
	MaxHP = GameDefine::TowHP1;
	MaxMP = GameDefine::TowMP1;
	mObjectType = GameObject::OT_Tower1;
	MyMov = new RoleAni(GameDefine::TowMov1);
	AttMov = new QMovie(GameDefine::TowAttMov1);
	AceMov = new QMovie(GameDefine::TowAceMov1);
	this->setPixmap(GameDefine::TowerUrl1_1);
	Harm = GameDefine::TowHarm1;
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
}

void Tower1::MyAce(MyScene* TargetScene)
{

	MySide::MyAce();
	MyMov->ChangeMov(AceMov,RoleAni::CenterAlign);
	
}