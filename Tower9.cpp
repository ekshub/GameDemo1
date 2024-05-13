#include "Tower9.h"
#include"GameControl.h"
QList<Card*> Tower9::cardList;
Tower9::Tower9() :MySide("D:\\tower\\too9ac.gif", 1000)
{
	mObjectType = GameObject::OT_Tower9;
	MyMov = new RoleAni("D:\\tower\\to9.gif", this);
	AttMov = new QMovie("D:\\tower\\to9at.gif");
	AceMov = new QMovie("D:\\tower\\to9ac.gif");
	AceBulletTimer = new QTimer;
	BulletSendTimer = new QTimer;
	this->setPixmap(GameDefine::TowerUrl9_1);
	Harm = 1000;
	InitHarm = 200;
	QObject::connect(AttMov, &QMovie::finished, [=]() {if (AttState)
		return;
		AttMov->stop();
		MyMov->Play();
		AttackTimer->start(1000);
		});
	QObject::connect(AceMov, &QMovie::finished, [=]() {if (AttState)
		return;
		AttMov->stop();
		MyMov->Play();
		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {if (AttState)
		return;
		Bullet* Bul = getBullet();
		GameControl::Instance()->GameScene.addItem(Bul);
		Bul->Mov->start();
		Bul->setPos(pos().x() + 70, pos().y() - 100);
		TracingBulletList.append(Bul);
		BulletSendTimer->stop();
		});
	QObject::connect(AttackTimer, &QTimer::timeout, [=]() {if (AttState)
		return;
		if (MP >= MaxMP)
		{
			MyAce();
			return;
		}
		MyMov->ChangeMov(AttMov);
		MyMov->moveBy(22, 0);
		BulletSendTimer->start(2400);
		AttackTimer->stop();
		if (level == 3)
			MP += 500;
		});
	QObject::connect(AceStartTimer, &QTimer::timeout, [=]() {if (AttState)
		return;
		ace = 0;
		for (int i = 0; i < 360; i += 36)
		{
			Bullet* Bul = getBullet();
			AceBulletList.append(Bul);
			Bul->setPos(MyMov->Pos.x()-29+ 100 * cos(double(i) * 3.14 / 180.0), MyMov->Pos.y() + 100 * sin(double(i) * 3.14 / 180.0) - 62-29);
			GameControl::Instance()->GameScene.addItem(Bul);
			Bul->Mov->start();
			
		}
		AceBulletTimer->start(10);
		AceEndTimer->start(2000);
		AceStartTimer->stop();
		});
	QObject::connect(AceAttTimer, &QTimer::timeout, [=] {if (AttState)
		return;

		for (auto Bul : AceBulletList)
		{
			if (!GameControl::Instance()->MonList1.isEmpty()) {
				if (Bul->count == -1)
					Bul->count = rand() % GameControl::Instance()->MonList1.size();
				if (Bul->count < GameControl::Instance()->MonList1.size())
				{
					EnemySide* mon = GameControl::Instance()->MonList1[Bul->count];
					if (abs((Bul->pos().y() - mon->MyMov->pos().y())) >= abs(Bul->pos().x() - mon->MyMov->pos().x()))
					{
						if (Bul->pos().y() - mon->MyMov->pos().y() > 10)
							Bul->Temp = -QPoint(((2 * Bul->pos().x() - 2 * mon->MyMov->pos().x())) / (Bul->pos().y() - mon->MyMov->pos().y()), 2);
						else if (Bul->pos().y() - mon->MyMov->pos().y() < 10)
							Bul->Temp = +QPoint(((2 * Bul->pos().x() - 2 * mon->MyMov->pos().x())) / (Bul->pos().y() - mon->MyMov->pos().y()), 2);
					}
					else {
						if (Bul->pos().x() - mon->MyMov->pos().x() > 10)
							Bul->Temp = -QPoint(2, (2 * Bul->pos().y() - 2 * mon->MyMov->pos().y()) / (Bul->pos().x() - mon->MyMov->pos().x()));
						else if (Bul->pos().x() - mon->MyMov->pos().x() < 10)
							Bul->Temp = QPoint(2, ((2 * Bul->pos().y() - 2 * mon->MyMov->pos().y())) / (Bul->pos().x() - mon->MyMov->pos().x()));
					}
					Bul->moveBy(Bul->Temp.x(),Bul->Temp.y()) ;

					if (Bul->collidesWithItem(mon->MyMov))
					{
						Bul->count2++;
						Bul->count = rand() % GameControl::Instance()->MonList1.size();
						(mon)->HP -= Bul->Harm / 2;
						(mon)->HPBar->setValue((mon)->HP * 100 / ((Monster1*)mon)->MaxHP);
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
				if (Bul->x() < 10 || Bul->y() < 10 || Bul->x() > 1400 || Bul->y() > 800||Bul->count2>=10)
				{
					GameControl::Instance()->GameScene.removeItem(Bul);
					Bul->Temp = QPoint(0, 0);
					Bul->Mov->stop();
					Bul->count = -1;
					Bul->count2 = 0;
					AceBulletList.removeOne(Bul);
					BulletList.append(Bul);
				}
				if (AceBulletList.isEmpty())
				{
					AttackTimer->start(1000);
					AceAttTimer->stop();
				}
			}
		}
		});
	QObject::connect(AceBulletTimer, &QTimer::timeout, [=] (){if (AttState)
		return;
		ace = (ace + 1) % 360;
		int j = 0;
		for (auto i : AceBulletList)
		{
			i->setPos(MyMov->Pos.x() + 100 * cos(double(j + ace) * 3.14 / 180.0)-29, MyMov->Pos.y() + 100 * sin(double(j + ace) * 3.14 / 180.0) - -62 -29);
			j += 36;
		}
		ace = (ace + 1) % 360;
		j = 0;
		for (auto i : AceBulletList)
		{
			i->setPos(MyMov->Pos.x() + 100 * cos(double(j + ace) * 3.14 / 180.0)-29 , MyMov->Pos.y() + 100 * sin(double(j + ace) * 3.14 / 180.0) - 62 -29);
			j += 36;
		}
		});
	QObject::connect(AceEndTimer, &QTimer::timeout, [this] {if (AttState)
		return;
		AceBulletTimer->stop();
		ace = 0;
		AceEndTimer->stop();
		AceAttTimer->start(5);

		});
}
Tower9::~Tower9()
{
}
void Tower9::init(QPoint _Pos, MapItem* _Map)
{
	MySide::init(_Pos, _Map);
	MyMov->moveBy(-22, 0);
	MyMov->Pos -= QPoint(22, 0);
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
				EnemySide* mon = GameControl::Instance()->MonList1[Bul->count];
				if (abs((Bul->pos().y() - mon->MyMov->pos().y())) >= abs(Bul->pos().x() - mon->MyMov->pos().x()))
				{
					if (Bul->pos().y() - mon->MyMov->pos().y() > 10)
						Bul->Temp = -QPoint(((2 * Bul->pos().x() - 2 * mon->MyMov->pos().x())) / (Bul->pos().y() - mon->MyMov->pos().y()), 2);
					else if (Bul->pos().y() - mon->MyMov->pos().y() < 10)
						Bul->Temp = +QPoint(((2 * Bul->pos().x() - 2 * mon->MyMov->pos().x())) / (Bul->pos().y() - mon->MyMov->pos().y()), 2);
				}
				else {
					if (Bul->pos().x() - mon->MyMov->pos().x() > 10)
						Bul->Temp = -QPoint(2, (2 * Bul->pos().y() - 2 * mon->MyMov->pos().y()) / (Bul->pos().x() - mon->MyMov->pos().x()));
					else if (Bul->pos().x() - mon->MyMov->pos().x() < 10)
						Bul->Temp = QPoint(2, ((2 * Bul->pos().y() - 2 * mon->MyMov->pos().y())) / (Bul->pos().x() - mon->MyMov->pos().x()));
				}
				Bul->moveBy(Bul->Temp.x(), Bul->Temp.y());
				if (Bul->collidesWithItem(mon->MyMov))
				{
					Bul->count2++;
					Bul->count = rand() % GameControl::Instance()->MonList1.size();
					mon->HP -= Bul->Harm ;
					mon->HPBar->setValue(mon->HP * 100 / mon->MaxHP);
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
		if (Bul->x() < 0 || Bul->y() < 0 || Bul->x() > 1300 || Bul->y() > 800 || Bul->count2 == 3)
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
	MySide::MyAce();
	MyMov->ChangeMov(AceMov);
	MyMov->moveBy(46,0);
	AceStartTimer->start(1400);
	AttackTimer->stop();
}

void Tower9::Reset()
{
	MySide::Reset();
	if (MyMov->Pos.y() - MyMov->pos().y() == 270)
		MyMov->moveBy(36, 157);
}


