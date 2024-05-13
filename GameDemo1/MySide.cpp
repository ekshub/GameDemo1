#include "MySide.h"
#include"GameControl.h"


MySide::MySide(QString _BulUrl,int _Harm):BulletUrl(_BulUrl),Harm(_Harm)
{
	AceStartTimer = new QTimer;
	AceEndTimer = new QTimer;
	AceAttTimer = new QTimer;
	BulletSendTimer = new QTimer;
	AttState = true;
	for (int i = 0; i < 30; i++)
	{
		Bullet* Bul = new Bullet(BulletUrl, this);
		Bul->Harm = this->Harm;
		BulletList.append(Bul);

	}
	level = 1;
	isalive = true;
	ParentMap = nullptr;
}

void MySide::init(QPoint _Pos,MapItem* _Map)
{
	ParentMap = _Map;
	setPos(_Pos);
	MyMov->setPos(_Pos);
	MyMov->Pos =_Pos;
	isalive = true;
	MyMov->Play();
	MP = 0;
	HP = MaxHP;
}

void MySide::Upgrade()
{
	level++;
	if (level == 2)
	{
		MaxHP *= 3;
		HP = MaxHP;
		Harm *= 3;
	}
	else if (level == 3)
	{
		MaxHP *= 3;
		HP = MaxHP;
		Harm *= 3;
	}
}

void MySide::MyAce(MyScene* TargetScene)
{
	MP = 0;
}

void MySide::death()
{
	AttState = true;
	BulletSendTimer->stop();
	AttackTimer ->stop();
	AceStartTimer->stop();
	AceEndTimer->stop();
	AceAttTimer->stop();
	MyMov->stop();
	GameControl::Instance()->GameScene.removeItem(MyMov);
	BulletRecover();
}

void MySide::BulletRecover()
{
	for (auto Bul : TracingBulletList)
	{
		BulletList.append(Bul);
		GameControl::Instance()->GameScene.removeItem(Bul);
		TracingBulletList.removeOne(Bul);
		Bul->Recover();
	}
}

void MySide::Reset()
{
	BulletRecover();
	AttState = true;
	MyMov->stop();
	HP = MaxHP;
	MP = 0;
	GameControl::Instance()->GameScene.addItem(MyMov);
	MyMov->Play();
}

void MySide::StartAtt()
{
	AttState=false;
	AttackTimer->start(1000);
}

Bullet* MySide::getBullet()
{
	if (BulletList.isEmpty())
		for (int i = 0; i < 10; i++)
		{
			Bullet* Bul = new Bullet(BulletUrl, this);
			Bul->Harm = this->Harm;
			BulletList.append(Bul);
		}
	Bullet* bul = BulletList.first();
	BulletList.pop_front();
	return bul;
}
MySide::~MySide()
{
	Recover();
	delete AceStartTimer;
	delete AceEndTimer;
	delete AceAttTimer;
	for (auto i : BulletList)
	{
		BulletList.removeOne(i);
		delete i;

	}
	for (auto i :TracingBulletList)
	{
		AceBulletList.removeOne(i);
		delete i;
	}
	for (auto i : AceBulletList)
	{
		AceBulletList.removeOne(i);
		delete i;
	}
	delete MyMov;
	delete AceMov;
	delete DeathMov;
}

void MySide::Recover()
{
	AttackTimer->stop();
	AceStartTimer->stop();
	AceEndTimer->stop();
	AceAttTimer->stop();
	MyMov->stop();
	//AttMov->stop();
	MyMov->Pos = QPoint(0, 0);
}


