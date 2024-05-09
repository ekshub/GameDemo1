#pragma once
#include"GameDefine.h"
class RoleAni:public QGraphicsProxyWidget
{
public:
	RoleAni(QString mov, GameObject* par=nullptr);
	QMovie* Mov;
	QLabel* Lab;
	QPoint Pos;
	GameObject* parent;
	~RoleAni();
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void ChangeMov(QMovie* _Mov);
	void Play();
	void stop();
};

