#pragma once
#include "GameObject.h"


class EnemySide : public GameObject
{
public:
	explicit EnemySide(QObject* parent = nullptr);
	virtual ~EnemySide();//����������
	void Move();//���ƶ����ƶ�
	void init(QPoint _Pos);//��ʼ��
	RoleAni* MyMov;//���󶯻�������
	QProgressBar* HPBar;//Ѫ�������ڿ��ӻ�Ѫ��
	void hurted(int Harm);//�ܵ�����������Ѫ��������Ѫ��
	bool Actived;//�Ƿ񱻿���
	bool isAlive;//�Ƿ���
	bool isAtting;
	double MoveSpeed;//����
	virtual void MyAdjust();//����λ��
	void  death();
};

