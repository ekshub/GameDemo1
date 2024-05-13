#include "MapItem.h"
#include"GameControl.h"
MapItem:: MapItem() {
	setAcceptDrops(true);
	onfree = true;
}

void MapItem::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
	event->setAccepted(true);
	update();
}

void MapItem::dropEvent(QGraphicsSceneDragDropEvent* event)
{
	QString _objectType = event->mimeData()->text();
	QPointF pos = mapToScene(event->pos());
		
	int _ob = -1;
	if (_objectType == "Tower1")
		_ob = GameObject::OT_Tower1;
	else if (_objectType == "Tower2")
		_ob = GameObject::OT_Tower2;
	else if (_objectType == "Tower3")
		_ob = GameObject::OT_Tower3;
	else if (_objectType == "Tower4")
		_ob = GameObject::OT_Tower4;
	else if (_objectType == "Tower5")
		_ob = GameObject::OT_Tower5;
	else if (_objectType == "Tower6")
		_ob = GameObject::OT_Tower6;
	else if (_objectType == "Tower7")
		_ob = GameObject::OT_Tower7;
	else if (_objectType == "Tower8")
		_ob = GameObject::OT_Tower8;
	else if (_objectType == "Tower9")
		_ob = GameObject::OT_Tower9;
	if (_ob != -1 && onfree)
	{
		GameControl::Instance()->CreatTower(QPoint(this->pos().x()+50, this->pos().y()+100), _ob,this);
		onfree= false;
		GameControl::Instance()->AllCardList.removeOne(_ob);
		GameControl::Instance()->CardRecover(((Card*)((MyMime*)(event->mimeData()))->ptr));
	}

		else if (_objectType == "TowerAttack1")
		{
			//((Tower1*)((MyMime*)(event->mimeData()))->ptr)->AttackPix->setPos(QPoint(pos.x()-30, pos.y()-30));
		}
		update();
	
}
