#pragma once
#include "GameObject.h"
#include "GameDemo1.h"
#include<QPixmap>
#include <QProgressBar>
#include"RoleAni.h"
class EnemySide : public GameObject
{
public:
	explicit EnemySide(QObject* parent = nullptr);
	virtual ~EnemySide();
	void Move();
	bool IsBloodEmpty();
	QPoint _dir;
	long int MaxBlood;
	long int BloodVolume;
	RoleAni* MyMov;
	QProgressBar* BloodBar;
	void hurted(int Harm);
	bool Actived;
protected:
	double MoveSpeed;
	
	QPixmap img;
};

