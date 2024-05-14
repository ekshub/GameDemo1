#include "Tower4.h"
#include"GameControl.h"
QList<Card*> Tower4::cardList;
void Tower4::Recover()
{
	MySide::Recover();
	BulletSendTimer->stop();
	AttMov->stop();
}
Tower4::Tower4() :MySide(GameDefine::TowBul4, GameDefine::TowHarm4)
{
	MaxHP = GameDefine::TowHP4;
	MaxMP = GameDefine::TowMP4;
	mObjectType = GameObject::OT_Tower4;
	MyMov = new RoleAni(GameDefine::TowMov4, this);
	AttMov = new QMovie(GameDefine::TowAttMov4);
	AceMov = new QMovie(GameDefine::TowAceMov4);
	this->setPixmap(GameDefine::TowerUrl4_1);
	Harm = GameDefine::TowHarm4;


	QObject::connect(AttMov, &QMovie::finished, [=]() {
		if (AttState)
			return;
		AttMov->stop();
		MyMov->Play();
		AttackTimer->start(1000);
		});
	QObject::connect(AceMov, &QMovie::finished, [=]() {
		if (AttState)
			return;
		AceMov->stop();
		MyMov->Play();

		AttackTimer->start(2000);
		});
	QObject::connect(BulletSendTimer, &QTimer::timeout, [=]() {
		if (AttState)
			return;
		Bullet* Bul = getBullet();
		GameControl::Instance()->GameScene.addItem(Bul);
		Bul->Mov->start();
		Bul->setPos(pos().x() + MyMov->size().width() / 2-20, pos().y()-MyMov->size().height()/2-50);
		
		TracingBulletList.append(Bul);
		BulletSendTimer->stop();
		});
	QObject::connect(AceStartTimer, &QTimer::timeout, [=]() {
		if (AttState)
			return;
		for (int i = 0; i < 3; i++)
		{
			Bullet* Bul = getBullet();
			GameControl::Instance()->GameScene.addItem(Bul);
			Bul->Mov->start();
			Bul->setPos(pos().x() + MyMov->size().width() / 2-10, pos().y() - MyMov->size().height() / 2 - 50+(i-1)*100);
			TracingBulletList.append(Bul);
		}
		AceStartTimer->stop();
		});
	QObject::connect(AttackTimer, &QTimer::timeout, [=]() {
		if (AttState)
			return;
		bool temp = false;
		for (auto mon : GameControl::Instance()->MonList1)
		{
			if ((mon->MyMov->pos().x() - MyMov->Pos.x() > 0) && (abs(mon->MyMov->pos().y()+mon->MyMov->size().height()/2 - (MyMov->Pos.y()- MyMov->size().height()/2) )< 50))
			{
				temp = true;
				break;
			}
		}
		if (!temp)
			return;
		AttackTimer->stop();
		if (MP >= MaxMP)
		{
			MyAce();
			return;
		}
			MyMov->ChangeMov(AttMov);
			BulletSendTimer->start(1200);
			
		if (level == 3)
			MP += 2000;
		});

}
Tower4::~Tower4()
{
	delete BulletSendTimer;
}
void Tower4::init(QPoint _Pos, MapItem* _Map)
{
	MySide::init(_Pos,  _Map);
	
}

void Tower4::BulletMove()
{
	for (auto Bul : TracingBulletList)
	{
		Bul->moveBy(5, 0);
		qDebug() << Bul->size();
	}
}

void Tower4::MyAce(MyScene* TargetScene)
{
	MySide::MyAce();
	MyMov->ChangeMov(AceMov);
	AceStartTimer->start(2600);
}

