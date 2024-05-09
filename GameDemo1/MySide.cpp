#include "MySide.h"



MySide::MySide(QString _BulUrl,int _Harm):BulletUrl(_BulUrl),Harm(_Harm), isBound(false)
{
	AttackTimer = new QTimer;
	AceStartTimer = new QTimer;
	AceEndTimer = new QTimer;
	AceAttTimer = new QTimer;
	for (int i = 0; i < 30; i++)
	{
		Bullet* Bul = new Bullet(BulletUrl, this);
		Bul->Harm = this->Harm;
		BulletList.append(Bul);

	}
}

void MySide::init(QPoint _Pos)
{
	setPos(_Pos);
	MyMov->setPos(_Pos);
	MyMov->Mov->start();
	
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
	delete AttackTimer;
	for (auto i : BulletList)
	{
		delete i;
		BulletList.removeOne(i);

	}
	for (auto i : AceBulletList)
	{
		delete i;
		AceBulletList.removeOne(i);
	}
}

void MySide::Recover()
{
	AttackTimer->stop();
	AceStartTimer->stop();
	AceEndTimer->stop();
	AceAttTimer->stop();
	MyMov->stop();
	//AttMov->stop();
}


