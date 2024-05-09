#include "Tower7.h"
#include"GameControl.h"
QList<Card*> Tower7::cardList;
Tower7::Tower7() :MySide("D:\\tower\\too7at.gif", 1)
{
	mObjectType = GameObject::OT_Tower7;
	MyMov = new RoleAni("D:\\tower\\to7.gif", this);
	BulletSendTimer = new QTimer;
	AttMov = new QMovie("D:\\tower\\to7at.gif");
	this->setPixmap(GameDefine::TowerUrl7_1);
	Harm = 1;
	InitHarm = 1;
	int acount;
	for (auto i : BulletList)
	{
		QObject::connect(i->Mov, &QMovie::finished, [=]() {
			i->Mov->stop();
			GameControl::Instance()->GameScene.removeItem(i);
			TracingBulletList.removeOne(i);
			BulletList.append(i);
			
			});
	}
	QObject::connect(AttackTimer, &QTimer::timeout, [=]()
		{
			AttackTimer->stop();
			MyMov->ChangeMov(AttMov);
			MyMov->moveBy(-30, -25);
			BulletSendTimer->start(2600);
		});
	QObject::connect(AttMov, &QMovie::finished, [=]() {

		AttMov->stop();
		MyMov->Play();
		AttackTimer->start(5000);

		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {
		for (auto mon : GameControl::Instance()->MonList1)
		{
			Bullet* Bul = getBullet();
			GameControl::Instance()->GameScene.addItem(Bul);
			Bul->Mov->start();
			Bul->setPos(GameControl::Instance()->MonList1[0]->MyMov->pos()-QPoint(50,0));
			TracingBulletList.append(Bul);
			BulletSendTimer->stop();
		}});

}
Tower7::~Tower7()
{
}
void Tower7::init(QPoint _Pos)
{
	MySide::init(_Pos);
	AttackTimer->start(1000);
}

void Tower7::BulletMove()
{
}

void Tower7::MyAce(MyScene* TargetScene)
{
}

