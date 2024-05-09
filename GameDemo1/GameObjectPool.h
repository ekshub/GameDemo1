#pragma once

#include "GameDefine.h"
#include "Monster1.h"
#include "Monster2.h"
#include "Tower1.h"
#include "Tower2.h"
#include "Tower3.h"
#include "Tower4.h"
#include "Tower5.h"
#include "Tower6.h"
#include "Tower7.h"
#include "Tower8.h"
#include "Tower9.h"
class GameObjectPool:public QObject
{
	//单例
	GameObjectPool(QObject* parent = nullptr);
	static GameObjectPool* instance;
public:
	static GameObjectPool* Instance()
	{
		if (instance == nullptr)
			return instance = new GameObjectPool(GameDemo1::MainWindow);
		return instance;
	}
	//对象工厂
	void ObjectFactory(int _objectType);


	//对象池初始化
	void Init();


	//获取对象
	GameObject* GetGameObject(int _objectType);

	//回收对象
	void RecoveryGameObject(GameObject* _object);

	//内存清除
	void Clear();
	~GameObjectPool();
protected:
	QList<Monster1*>MonPool;
	QList<Monster2*>MonPool2;
	QList<Tower1*>TowerPool1;
	QList<Tower2*>TowerPool2;
	QList<Tower3*>TowerPool3;
	QList<Tower4*>TowerPool4;
	QList<Tower5*>TowerPool5;
	QList<Tower6*>TowerPool6;
	QList<Tower7*>TowerPool7;
	QList<Tower8*>TowerPool8;
	QList<Tower9*>TowerPool9;
};

