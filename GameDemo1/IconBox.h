#pragma once
#include"GameDefine.h"
class IconBox:public QGraphicsPixmapItem
{
public:
	IconBox();
	void dropEvent(QGraphicsSceneDragDropEvent* event) override;
	void dragEnterEvent(QGraphicsSceneDragDropEvent* event)override;
};

