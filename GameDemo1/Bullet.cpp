#include "Bullet.h"

Bullet::Bullet(QString mov, GameObject* par) :Temp{ QPoint(0, 0) },parent(par)
{
	Mov = new QMovie(mov);
	Lab = new QLabel;
	Lab->setMovie(Mov);
	Lab->setStyleSheet("background-color: transparent;");
	this->setWidget(Lab);
	count = -1;
	count2 = 0;
}

Bullet::~Bullet()
{


		delete Mov;
		//Lab�����ڶ������ϣ�����Ҫ�ֶ��ͷ�

	
}
