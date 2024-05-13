#pragma once
#include"GameDefine.h"
class GameObject;
class RoleAni:public QGraphicsProxyWidget
{
public:
	enum AlignWay
	{
		CenterAlign,
		ButtomAlign
	};
	RoleAni(QString mov, GameObject* par=nullptr);
	QMovie* Mov;
	QLabel* Lab;
	QPoint Pos;
	GameObject* parent;
	~RoleAni();
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void ChangeMov(QMovie* _Mov, int AlignWay= ButtomAlign);
	void Play();
	void stop();
	void initDrag();
};

