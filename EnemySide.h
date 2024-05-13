#pragma once
#include "GameObject.h"


class EnemySide : public GameObject
{
public:
	explicit EnemySide(QObject* parent = nullptr);
	virtual ~EnemySide();//虚析构函数
	void Move();//控制对象移动
	RoleAni* MyMov;//对象动画播放器
	QProgressBar* HPBar;//血条，用于可视化血量
	void hurted(int Harm);//受到攻击，减少血量，更新血条
	bool Actived;//是否被控制
	bool isAlive;//是否存活
	double MoveSpeed;//移速
};

