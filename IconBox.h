#pragma once
#include"GameDefine.h"
#pragma warning(disable : 4828)
class IconBox:public QGraphicsPixmapItem
{
public:
	IconBox();
	void dropEvent(QGraphicsSceneDragDropEvent* event) override;
	void dragEnterEvent(QGraphicsSceneDragDropEvent* event)override;
};

