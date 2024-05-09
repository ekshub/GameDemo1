#include "Tower4.h"
#include"GameControl.h"
QList<Card*> Tower4::cardList;
void Tower4::Recover()
{
	MySide::Recover();
	BulletSendTimer->stop();
	AttMov->stop();
	qDebug() << "4";
}
Tower4::Tower4() :MySide("D:\\tower\\to4att.gif", 200)
{
	mObjectType = GameObject::OT_Tower4;
	MyMov = new RoleAni("D:\\tower\\too4.gif", this);
	AttMov = new QMovie("D:\\tower\\to4at.gif");
	this->setPixmap(GameDefine::TowerUrl4_1);
	Harm = 1000;
	InitHarm = 200;
	BulletSendTimer = new QTimer;
	QObject::connect(AttMov, &QMovie::finished, [=]() {
		AttMov->stop();
		MyMov->Play();
		AttackTimer->start(1000);
		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {
		Bullet* Bul = getBullet();
		GameControl::Instance()->GameScene.addItem(Bul);
		Bul->Mov->start();
		Bul->setPos(pos().x() + 70, pos().y() - 20);
		TracingBulletList.append(Bul);
		BulletSendTimer->stop();
		});
	QObject::connect(AttackTimer, &QTimer::timeout, [=]() {
		MyMov->ChangeMov(AttMov);
		BulletSendTimer->start(1200);
		MyMov->moveBy(-27, -34);

		AttackTimer->stop();
		});

}
Tower4::~Tower4()
{
	delete BulletSendTimer;
}
void Tower4::init(QPoint _Pos)
{
	MySide::init(_Pos);
	AttackTimer->start(1000);
}

void Tower4::BulletMove()
{
	for (auto Bul :TracingBulletList)
		Bul->moveBy(5, 0);
}

void Tower4::MyAce(MyScene* TargetScene)
{
	
}

