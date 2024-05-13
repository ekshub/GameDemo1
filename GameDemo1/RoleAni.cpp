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
		GameControl::Instance()->sellTower((MySide*)this->parent);


	}
	else if (event->button() == Qt::LeftButton)
	{

	}
}

void RoleAni::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QDrag* drag = new QDrag(event->widget());
	MyMime* mime = new MyMime;
	mime->ptr = (QObject*)this;

	drag->setMimeData(mime);
	
	drag->setHotSpot(QPoint(35, 35));
	drag->exec();
}

void RoleAni::ChangeMov(QMovie* _Mov, int Align)
{
	Lab->setMovie(_Mov);
	Mov->stop();
	_Mov->start();
	Lab->adjustSize();
	switch (Align)
	{
	case ButtomAlign: {
		setPos(Pos.x() - size().width() / 2, Pos.y() - size().height());
		break;
	}
	case CenterAlign: {
		setPos(Pos.x() - size().width() / 2, Pos.y() - size().height()/2);
		break;
	}
	}
}



void RoleAni::Play()
{
	
	Lab->setMovie(Mov);
	Mov->start();
	Lab->adjustSize();
	Lab->move(Pos.x() - size().width() / 2, Pos.y() - size().height());
	qDebug() << Pos << pos();
}

void RoleAni::stop()
{
	Mov->stop();
}

RoleAni::~RoleAni()
{
	delete Mov;
}
	