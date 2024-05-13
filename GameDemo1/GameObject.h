#pragma once

#include"RoleAni.h"
#include<QGraphicsPixmapItem>
#include "GameDefine.h"
#pragma warning(disable : 4828)
class GameObject:public QGraphicsPixmapItem
{
public:
	enum ObjectType
	{
		OT_Monster1,
		OT_Monster2,
		OT_Monster3,
		OT_Tower1,
		OT_Tower2,
		OT_Tower3,
		OT_Tower4,
		OT_Tower5,
		OT_Tower6,
		OT_Tower7,
		OT_Tower8,
		OT_Tower9,
	};
public:
	explicit GameObject(QObject*parent=nullptr);
	virtual ~GameObject();//虚析构函数
	int GetType();//获取对象种类
	virtual void init(QPoint _Pos);//初始化
	bool IsDead();//是否死亡
	long int MaxHP;//对象总血量
	long int HP;//对象现有血量
	long int MP;//现有蓝量
	long int MaxMP;//总蓝量
	QMovie* AttMov;//攻击动画
	QTimer* AttackTimer;//控制播放攻击动画的定时器
protected:
	int mObjectType;//对象种类
	QPoint Pos;//对象位置
};

