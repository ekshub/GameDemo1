#include "Tower5.h"
#include"GameControl.h"
QList<Card*> Tower5::cardList;
Tower5::Tower5() :MySide("D:\\tower\\toa3.gif", 200)
{
	mObjectType = GameObject::OT_Tower5;
	MyMov = new RoleAni("D:\\tower\\to5.gif", this);
	AttMov = new QMovie("D:\\tower\\to5at.gif");
	AttMov->setSpeed(150);
	AceMov = new QMovie("D:\\tower\\to5ace.gif");
	DeathMov = new QMovie("D:\\tower\\to5de.gif");
	DeathMov2= new QMovie("D:\\tower\\to5de2.gif");
	MoveSt = new QMovie("D:\\tower\\to5mst.gif");
	MoveEn = new QMovie("D:\\tower\\to5men.gif");
	MoveD = new QMovie("D:\\tower\\to5md.gif");
	AttMov2 = new QMovie("D:\\tower\\to5at2.gif");
	this->setPixmap(GameDefine::TowerUrl5_1);
	BulletSendTimer = new QTimer;
	MoveTimer = new QTimer;
	Harm = 1000;
	InitHarm = 200;
	state = 0;
	QObject::connect(AttMov, &QMovie::finished, [=]() {if (AttState)
		return;
		if (!isalive)
			return;
		AttMov->stop();
		MyMov->Play();
		
		AttackTimer->start(200);
		});
	QObject::connect(AttMov2, &QMovie::finished, [=]() {if (AttState)
		return;
		if (!isalive)
			return;
		AttackTimer->start(0);
		});
	QObject::connect(DeathMov, &QMovie::finished, [=]() {
		DeathMov->stop();
		MyMov->ChangeMov(DeathMov2);
		MyMov->moveBy(0, 66);
		
		if (level == 3)
			AceStartTimer->start(10000);
		});
	QObject::connect(AceMov, &QMovie::finished, [=]() {if (AttState)
		return;
		AttMov->stop();
		MyMov->Play();
		isalive = true;
		HP = MaxHP;
		state = 0;
		GameControl::Instance()->TowerRevive(this);
		AttackTimer->start(100);
		});
	QObject::connect(MoveSt, &QMovie::finished, [=]() {if (AttState)
		return;
		MyMov->ChangeMov(MoveD);
		MyMov->moveBy(35, 0);
		MoveTimer->start(10);

		});

	QObject::connect(MoveTimer, &QTimer::timeout, [=]() {if (AttState)
		return;
		
		RoleAni* mon = GameControl::Instance()->MonList1.first()->MyMov;
		
		QPointF Towtemp = MyMov->Pos + QPointF(MyMov->size().width() / 2, -MyMov->size().height()/2);
		QPointF Montemp = mon->pos() + QPointF(-100, mon->size().height() / 2);
		if ((mon->pos().x() - Towtemp.x() > 0) && (Montemp.x() - Towtemp.x() < 100) && ((Montemp.y() - Towtemp.y()) < 10))
		{
			state = 3;
			MoveTimer->stop();
			return;
		}
		if (abs((Towtemp.y() - Montemp.y())) >= abs(Towtemp.x()- Montemp.x()))
		{
			if (Towtemp.y() - Montemp.y() >= 0)
			{
				MyMov->moveBy(-((2 * Towtemp.x() - 2 * Montemp.x())) / (Towtemp.y() - Montemp.y()), -2);
				MyMov->Pos += QPoint(-((2 * Towtemp.x() - 2 * Montemp.x())) / (Towtemp.y() - Montemp.y()), -2);
			}
			else if (Towtemp.y() - Montemp.y() < 0)
			{
				MyMov->moveBy(((2 * Towtemp.x() - 2 * Montemp.x())) / (Towtemp.y() - Montemp.y()), 2);
				MyMov->Pos += QPoint(((2 * Towtemp.x() - 2 * Montemp.x())) / (Towtemp.y() - Montemp.y()), 2);
			}
		}
		else {
			if (Towtemp.x() - Montemp.x() >= 0)
			{
				MyMov->moveBy(-2, -(2 * Towtemp.y() - 2 * Montemp.y()) / (Towtemp.x() - Montemp.x()));
				MyMov->Pos += QPoint(-2, -(2 * Towtemp.y() - 2 * Montemp.y()) / (Towtemp.x() - Montemp.x()));
			}
			else if (Towtemp.x() - Montemp.x() < 0)
			{
				MyMov->moveBy(2, ((2 * Towtemp.y() - 2 * Montemp.y())) / (Towtemp.x() - Montemp.x()));
				MyMov->Pos += QPoint(2, ((2 * Towtemp.y() - 2 * Montemp.y())) / (Towtemp.x() - Montemp.x()));
			}
		}
		qDebug() << MyMov->Pos;
		});

	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {if (AttState)
		return;
		bool temp = true;
		for (auto mon : GameControl::Instance()->MonList1)
		{
			if ((mon->MyMov->pos().x() - MyMov->pos().x() > -50) && (mon->MyMov->pos().x() - MyMov->Pos.x() < 300) && (abs(mon->MyMov->pos().y() - MyMov->pos().y()-MyMov->size().height()) < 200))
			{
				temp = false;
				mon->hurted(1000);
			}

		}
		if (state == 0)
			BulletSendTimer->stop();
		if (state == 3 && temp)
			state = 1;
		});

	QObject::connect(AttackTimer, &QTimer::timeout, [=]() {if (AttState)
		return;

			bool temp = false;
			for (auto mon : GameControl::Instance()->MonList1)
			{
				if ((mon->MyMov->pos().x() - MyMov->pos().x() > 0) && (mon->MyMov->pos().x() - MyMov->pos().x() < 300) && (abs(mon->MyMov->pos().y() - MyMov->pos().y()) < 100))
				{
					temp = true;
					break;
				}
			}
			if (temp&&state==0)
			{

				BulletSendTimer->start(600);
				MyMov->ChangeMov(AttMov);
				MyMov->moveBy(0, 42);
				AttackTimer->stop();
				if(state==0)
				HP -= 1000;
			}
			else if (state == 1)
			{
				MyMov->ChangeMov(MoveSt);
				MyMov->moveBy(0, 66);
				state = 2;
			}
			else if (state == 3)
			{
				BulletSendTimer->start(300);
				MyMov->ChangeMov(AttMov2);
				MyMov->moveBy(0, 40);

				AttackTimer->stop();
			}

		
		});
	QObject::connect(AceStartTimer, &QTimer::timeout, [=]() {if (AttState)
		return;
		MyAce();
		AceStartTimer->stop();
		});
}
Tower5::~Tower5()
{
}
void Tower5::init(QPoint _Pos, MapItem* _Map)
{
	MySide::init(_Pos, _Map);
	
}

void Tower5::BulletMove()
{
}

void Tower5::MyAce(MyScene* TargetScene)
{
	MySide::MyAce();
	MyMov->ChangeMov(AceMov, RoleAni::CenterAlign);
	MyMov->setPos(0, 0);
	MyMov->Lab->resize(1400, 800);
}

void Tower5::death()
{
	isalive = false;
	MyMov->stop();
	AttackTimer->stop();
	AceStartTimer->stop();
	AceEndTimer->stop();
	AceAttTimer->stop();
	MyMov->ChangeMov(DeathMov);
	MyMov->moveBy(0, 113);
	
}

void Tower5::Recover()
{
	AttackTimer->stop();
	AceStartTimer->stop();
	AceEndTimer->stop();
	AceAttTimer->stop();
}

