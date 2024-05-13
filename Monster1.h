#pragma once
#include "EnemySide.h"
class Monster1:public EnemySide
{
public:
	Monster1(QObject* parent);
	void init(QPoint _Pos);
};
