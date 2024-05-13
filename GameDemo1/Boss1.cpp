#include "Boss1.h"
#include"GameControl.h"

void Boss1::Enter()
{
	MyMov->Pos = QPoint(800,100);
	GameControl::Instance()->GameScene.addItem(MyMov);
	MyMov->ChangeMov(EnMov);
	qDebug() << MyMov->pos();
}

Boss1::Boss1()
{
	MyMov = new RoleAni("D:\\Monster\\Boss.gif");
	AceMov1 = new QMovie("D:\\Monster\\Bossat1.gif");
	AceMov2 = new QMovie("D:\\Monster\\Bossat2.gif");
	AceMov3 = new QMovie("D:\\Monster\\Bossac3.gif");
	AceMov4 = new QMovie("D:\\Monster\\Bossat4.gif");
	EnMov = new QMovie("D:\\Monster\\Boss4EN.gif");
	DeMov = new QMovie("D:\\Monster\\BossDE.gif");
	QObject::connect(EnMov, &QMovie::finished, [this]() {
		EnMov->stop();
		MyMov->Play();
		MyMov->setPos(MyMov->Pos.x() - 170, MyMov->Pos.y() - 316);
		MyMov->ChangeMov(AceMov3);
		MyMov->setPos(0,-850);
		MyMov->Lab->resize(1800, 1800);
		});
}

Boss1::~Boss1()
{

	delete MyMov;
	delete AceMov1;
	delete AceMov2;
	delete AceMov3;
	delete AceMov4;
	delete EnMov;
	delete DeMov;
}
