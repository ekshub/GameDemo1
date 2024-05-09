#pragma once
#include"GameDefine.h"

class Bullet:public QGraphicsProxyWidget
{
public:
	Bullet(QString mov, GameObject* par);
	QMovie* Mov;
	QLabel* Lab;
	QPoint Temp;
	GameObject* parent;
	int Harm;
	~Bullet();
	int count;
	int count2;
};

