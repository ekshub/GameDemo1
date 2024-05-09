#include "Tower1.h"
#include"GameControl.h"

QList<Card*> Tower1::cardList ;
void Tower1::init(QPoint _Pos)
{
	MySide::init(_Pos);
	IconCards::Instance()->LoadIcon(this);
	count = 0;
}

void Tower1::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	/*QDrag* drag = new QDrag(event->widget());
	MyMime* mime = new MyMime;
	mime->setText("TowerAttack1");
	mime->ptr = (QObject*)this;
	drag->setMimeData(mime);
	drag->setPixmap(QPixmap("D:\\Qt_code\\qtmainproject\\img\\AttackPix1.png"));
	drag->setHotSpot(QPoint(35, 35));
	drag->exec();*/
}
void Tower1::Trace(Bullet* Bul)
{

	if (!GameControl::Instance()->MonList1.isEmpty())
	{
		RoleAni* mon = GameControl::Instance()->MonList1.first()->MyMov;
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
	}
	Bul->setPos(Bul->pos() + Bul->Temp);

}
void Tower1::BulletMove()
{
	for (auto Bul : TracingBulletList)
	Trace(Bul);
}

Tower1::Tower1():MySide("D:\\Qt_code\\spritesheets\\spritesheets\\unnamed-1.gif", 200)
{
	mObjectType = GameObject::OT_Tower1;
	MyMov = new RoleAni("D:\\Qt_code\\spritesheets\\spritesheets\\Tower-1.gif",this);
	
	
	this->setPixmap(GameDefine::TowerUrl1_1);
	InitHarm = 200;
}

Tower1::~Tower1()
{
	

	for (auto i : TracingBulletList)
	{
		delete i;
		TracingBulletList.removeOne(i);
	}
	
}

void Tower1::MyAce(MyScene* TargetScene,QTimer* MonGenTimer)
{
	
	
	if(MonGenTimer->isActive())
	MonGenTimer->stop();
	AttackTimer->stop();
	ace = 0;
	for (int i = 0; i < 360; i += 36)
	{
		Bullet* Bul = this->getBullet();
		this->AceBulletList.append(Bul);
		Bul->setPos(this->pos().x() + 100 * cos(double(i) * 3.14 / 180.0)+50, this->pos().y() + 100 * sin(double(i)* 3.14 / 180.0)+50);
		TargetScene->addItem(Bul);
		Bul->Mov->start();
		
	}
	AceStartTimer->start(10);
	AceEndTimer->start(500);
	if (isBound == false)
	{
		isBound = true;
		QObject::connect(AceStartTimer, &QTimer::timeout, [=] {
			ace = (ace + 1) % 360;
			int j = 0;
			for (auto i : AceBulletList)
			{
				i->setPos(this->pos().x() + 100 * cos(double(j + ace) * 3.14 / 180.0) + 50, this->pos().y() + 100 * sin(double(j + ace) * 3.14 / 180.0) + 50);
				j += 36;
			}
			ace = (ace + 1) % 360;
			j = 0;
			for (auto i : AceBulletList)
			{
				i->setPos(this->pos().x() + 100 * cos(double(j + ace) * 3.14 / 180.0) + 50, this->pos().y() + 100 * sin(double(j + ace) * 3.14 / 180.0) + 50);
				j += 36;
			}
			});
		QObject::connect(AceEndTimer, &QTimer::timeout, [this] {
			AceStartTimer->stop();
			ace = 0;
			AceEndTimer->stop();
			AceAttTimer->start(5);

			});
		QObject::connect(AceAttTimer, &QTimer::timeout, [this, MonGenTimer, TargetScene] {

			for (auto Bul : AceBulletList)
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
							Bul->count = rand() % GameControl::Instance()->MonList1.size();
							((Monster1*)mon->parent)->BloodVolume -= Bul->Harm / 2;
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
					if (Bul->x() < 10 || Bul->y() < 10 || Bul->x() > 1000 || Bul->y() > 550)
					{
						TargetScene->removeItem(Bul);
						Bul->Temp = QPoint(0, 0);
						Bul->Mov->stop();
						Bul->count = -1;
						AceBulletList.removeOne(Bul);
						BulletList.append(Bul);
					}
					if (AceBulletList.isEmpty())
					{
						MonGenTimer->start(1000);
						AttackTimer->start(1000);
						AceAttTimer->stop();
						count = 0;
					}
				}
			}
			});
	}
}