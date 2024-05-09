#include "RoleAni.h"
#include"GameControl.h"
RoleAni::RoleAni(QString mov, GameObject* par):parent(par)
{
	Mov = new QMovie(mov);
	Lab = new QLabel;
	Lab->setMovie(Mov);
	Lab->setStyleSheet("background-color: transparent;");
	this->setWidget(Lab);
	
}

void RoleAni::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		GameControl::Instance()->TowerRecover((MySide*)this->parent);


	}
	else if (event->button() == Qt::LeftButton)
	{

	}
}
void RoleAni::ChangeMov(QMovie* _Mov)
{
	
	Pos = Lab->pos();
	Lab->setMovie(_Mov);
	Mov->stop();
	_Mov->start();
	Lab->adjustSize();

}



void RoleAni::Play()
{
	
	Lab->setMovie(Mov);
	Mov->start();
	Lab->adjustSize();
	Lab->move(Pos);
}

void RoleAni::stop()
{
	Mov->stop();
}

RoleAni::~RoleAni()
{
	delete Mov;
}
	