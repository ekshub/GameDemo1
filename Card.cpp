#include "Card.h"
#include"GameDefine.h"
Card::Card()
{
	
}

Card::Card(QString text, QString pixmap,QPoint Pos):_Text(text),_Pix(pixmap)
{
	setPixmap(QPixmap(_Pix));
	setPos(Pos);
	num = -1;
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	
}

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QDrag* drag = new QDrag(event->widget());
	MyMime* mime = new MyMime;
	mime->ptr = (QObject*)this;
	mime->setText(this->_Text);
	drag->setMimeData(mime);
	drag->setPixmap(QPixmap(this->_Pix));
	drag->setHotSpot(QPoint(35, 35));
	drag->exec();
}
