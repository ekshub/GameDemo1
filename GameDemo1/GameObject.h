#pragma once
#include "GameDefine.h"
#include<QGraphicsPixmapItem>

class GameObject:public QGraphicsPixmapItem
{
public:
	enum ObjectType
	{
		OT_Monster1,
		OT_Monster2,
		OT_Tower1,
		OT_Tower2,
		OT_Tower3,
		OT_Tower4,
		OT_Tower5,
		OT_Tower6,
		OT_Tower7,
		OT_Tower8,
		OT_Tower9,
		OT_Tower1_Attack
	};
	explicit GameObject(QObject*parent=nullptr);
	virtual ~GameObject();
	int GetType();
	virtual void init(QPoint _Pos);
protected:
	int mObjectType;
	QPoint Pos;
};

