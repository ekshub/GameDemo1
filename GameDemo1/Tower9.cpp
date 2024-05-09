#include "Tower9.h"
#include"GameControl.h"
QList<Card*> Tower9::cardList;
Tower9::Tower9() :MySide("D:\\tower\\too9ac.gif", 1000)
{
	mObjectType = GameObject::OT_Tower9;
	MyMov = new RoleAni("D:\\tower\\to9.gif", this);
	AttMov = new QMovie("D:\\tower\\to9at.gif");
	BulletSendTimer = new QTimer;
	this->setPixmap(GameDefine::TowerUrl9_1);
	Harm = 1000;
	InitHarm = 200;
	QObject::connect(AttMov, &QMovie::finished, [=]() {
		AttMov->stop();
		MyMov->Play();
		AttackTimer->start(1000);
		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {
		Bullet* Bul = getBullet();
		GameControl::Instance()->GameScene.addItem(Bul);
		Bul->Mov->start();
		Bul->setPos(pos().x() + 70, pos().y() - 100);
		TracingBulletList.append(Bul);
		BulletSendTimer->stop();
		});
	QObject::connect(AttackTimer, &QTimer::timeout, [=]() {
		MyMov->ChangeMov(AttMov);
		BulletSendTimer->start(2400);
		MyMov->moveBy(-20, -154);

		AttackTimer->stop();
		});

}
Tower9::~Tower9()
{
}
void Tower9::init(QPoint _Pos)
{
	MySide::init(_Pos);
	AttackTimer->start(1000);
	MyMov->moveBy(-20, -20);
}

void Tower9::BulletMove()
{
	for (auto Bul : TracingBulletList)
	{
		if (!GameControl::Instance()->MonList1.isEmpty()) {
			if (Bul->count == -1)
				Bul->count = rand() % GameControl::Instance()->MonList1.size();
			if (Bul->count < GameControl::Instance()->MonList1.size())
			{
				RoleAni* mon = GameControl::Instance()->MonList1[Bul->count]->MyMov;
				if (abs((Bul->pos().y() - mon->pos().y())) >= abs(Bul->pos().x() - mon->pos().x()))
				{
					if (Bul->pos().y() - mon->pos().y() > 10)
						Bul->Temp = -QPoint(((2 * Bul->pos().x() - 2 * mon->pos().x())) / (Bul->pos().y() - mon->pos().y()), 2);
					else if (Bul->pos().y() - mon->pos().y() < 10)
						Bul->Temp = +QPoint(((2 * Bul->pos().x() - 2 * mon->pos().x())) / (Bul->pos().y() - mon->pos().y()), 2);
				}
				else {
					if (Bul->pos().x() - mon->pos().x() > 10)
						Bul->Temp = -QPoint(2, (2 * Bul->pos().y() - 2 * mon->pos().y()) / (Bul->pos().x() - mon->pos().x()));
					else if (Bul->pos().x() - mon->pos().x() < 10)
						Bul->Temp = QPoint(2, ((2 * Bul->pos().y() - 2 * mon->pos().y())) / (Bul->pos().x() - mon->pos().x()));
				}
				Bul->setPos(Bul->pos() + Bul->Temp);

				if (Bul->collidesWithItem(mon))
				{
					Bul->count2++;
					Bul->count = rand() % GameControl::Instance()->MonList1.size();
					((Monster1*)mon->parent)->BloodVolume -= Bul->Harm ;
					((Monster1*)mon->parent)->BloodBar->setValue(((Monster1*)mon->parent)->BloodVolume * 100 / ((Monster1*)mon->parent)->MaxBlood);
				}
			}
			else
				Bul->count = -1;
		}
		else
		{
			if (Bul->Temp == QPoint(0, 0))
			{
				Bul->Temp = QPoint(1, 1);
			}
			Bul->setPos(Bul->pos() + Bul->Temp);
		}
		if (Bul->x() < 0 || Bul->y() < 0 || Bul->x() > 1400 || Bul->y() > 800 || Bul->count2 == 5)
		{
			GameControl::Instance()->GameScene.removeItem(Bul);
			Bul->Temp = QPoint(0, 0);
			Bul->Mov->stop();
			Bul->count = -1;
			Bul->count2 = 0;
			TracingBulletList.removeOne(Bul);
			BulletList.append(Bul);
		}
	}
}

void Tower9::MyAce(MyScene* TargetScene)
{
}

