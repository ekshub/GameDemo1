#pragma once
#include "EnemySide.h"

class Monster2 :public EnemySide
{
public:
	Monster2(QObject* parent);
	void MyAdjust();
};

