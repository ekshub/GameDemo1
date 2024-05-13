#include "IconBox.h"
#include "Card.h"
#include"IconCards.h"

IconBox::IconBox()
{
	setAcceptDrops(true);
}

void IconBox::dropEvent(QGraphicsSceneDragDropEvent* event)
{
	
	QString img = event->mimeData()->text();
	((Card*)((MyMime*)(event->mimeData()))->ptr)->setPos(QPoint(pos().x() , pos().y()));
	IconCards::Instance()->IconList.append(((Card*)((MyMime*)(event->mimeData()))->ptr));
	update();
}

void IconBox::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
	event->setAccepted(true);
	update();
}
