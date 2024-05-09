#pragma once
#include "GameDefine.h"
#include "GameDemo1.h"
#include "GameObjectPool.h"
#include "GameMap.h"
#include "MyScene.h"
#include "MyView.h"
#include"Card.h"
#include"IconCards.h"
#include "IconBox.h"
class GameControl:public QObject
{
	//单例
	GameControl();
	static GameControl* instance;
public:
	//获取单例
	static GameControl* Instance()
	{
		if (instance == nullptr)
			return instance = new GameControl();
		return instance;
	}

	//游戏初始化
	void GameInit();

	//加载开始界面
	void LoadStartScene();

	//加载游戏场景和信号连接
	void LoadGameScene();

	//加载地图
	void LoadGameMap();
	
	//加载牌组
	void LoadCards();

	//加载面板
	void LoadPanelScene();

	//游戏逻辑定时器开启，初始化对象池
	void  GameStart();
	//抽取卡片
	void getCards();
	//在游戏场景上添加Tower并管理
	void CreatTower(QPoint pos, int _object);

	//回收Tower
	void TowerRecover(MySide* tow);

	//死亡对象回收
	void DeadRecover();
	//子弹回收
	void BulletRecover(Bullet*Bul, int _obj);
	//子弹移动
	void BulletMove();
	void CardRecover(Card* Car);
	//游戏定时器关闭，清空对象
	void GameOver();

	//碰撞检测
	void Collison();
	
	//出界检测
	void CheckOutBound();

	void keyPressEvent(QKeyEvent* event);
	GameMap* mMap;
	QList<Monster1*>MonList1;
	MyScene GameScene;
	QList<int> AllCardList;
private:
	
	QTimer* MonsterGenTimer1;
	QTimer* MonsterGenTimer2;
	QTimer* MonsterMoveTimer1;
	QTimer* MainTimer;
	
	
	QList<Card*> CardList;
	QList<MySide*> MySideList;
	MyView mGameView;
	
	MyScene PanelScene;
	MyScene StartScene;
	QGraphicsPixmapItem mbackground1;
	QGraphicsPixmapItem mbackground2;
	IconBox Panel1[10];
	QGraphicsPixmapItem* back;
	QToolButton* BackBtn;
	//QGraphicsPixmapItem particle;
	RoleAni* BossAni;
	RoleAni* Tower4Ani;
	RoleAni* Tower5Ani;
	
	QList<Tower1*>TowList1;
	QList<Tower2*>TowList2;
	QList<Tower3*>TowList3;
	QList<Tower4*>TowList4;
	QList<Tower5*>TowList5;
	QList<Tower6*>TowList6;
	QList<Tower7*>TowList7;
	QList<Tower8*>TowList8;
	QList<Tower9*>TowList9;
	~GameControl();
};

