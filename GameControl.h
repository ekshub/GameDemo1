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
#include"Boss1.h"
#include"Displayer.h"
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

	//游戏逻辑定时器开启，初始化对象池
	void  GameStart();
	//抽取卡片
	void getCards();
	//在游戏场景上添加Tower并管理
	void CreatTower(QPoint pos, int _object,MapItem* _Map);
	//更新时间
	void UpdateTime();
	//回合开始
	void RoundStart();
	//回合结束
	void RoundOver();

	//回收Tower
	void TowerRecover(MySide* tow);
	//出售Tower
	void sellTower(MySide* tow);
	//复活Tower
	void TowerRevive(MySide* tow);

	//死亡对象回收
	void DeadRecover();
	//敌方回收
	void MonsterRecover(Monster1* i);
	//子弹回收
	void BulletRecover(Bullet*Bul, int _obj);
	//卡牌回收
	void CardRecover(Card* Car);
	//子弹移动
	void BulletMove();
	//游戏定时器关闭，清空对象
	void GameOver();

	//碰撞检测
	void Collison();
	
	//出界检测
	void CheckOutBound();

	//升级检测
	void CheckUpgrade();
	//游戏状态检测
	void CheckState();
	//捕获键盘事件
	void keyPressEvent(QKeyEvent* event);

	GameMap* mMap;//游戏地图
	QList<Monster1*>MonList1;//存储敌方对象的链表
	MyScene GameScene;//游戏主场景
	QList<int> AllCardList;//牌组，用于记录每张牌剩余的数量
	QList<MySide*> MySideList;//我方存活对象链表
private:
	//游戏控制项
	int HP;//血量
	int XP;//经验
	int MaxXP[8] = {2,4,6,8,16,32,48,64};//升级所需经验
	int Coin;//金币
	int Round;//回合
	QTime BaseTime;//基础时间，用于计时
	bool state;//游戏状态
	int level;//等级

	QTimer* MainTimer;//主定时器，控制游戏主体逻辑
	QTimer* MonsterGenTimer1;
	QTimer* MonsterGenTimer2;
	QTimer* MonsterMoveTimer1;
	
	QList<Card*> CardList;//存储卡牌的链表
	
	QList<MySide*> MySideDList;//存储阵亡单位的链表
	MyView mGameView;//游戏视图
	MyScene StartScene;//开始场景
	QGraphicsPixmapItem mbackground1;//游戏背景1
	QGraphicsPixmapItem mbackground2;//游戏背景2
	QGraphicsPixmapItem Endpix ;//游戏结束图片
	//记录并管理添加到场景的我方对象
	QList<Tower1*>TowList1;
	QList<Tower2*>TowList2;
	QList<Tower3*>TowList3;
	QList<Tower4*>TowList4;
	QList<Tower5*>TowList5;
	QList<Tower6*>TowList6;
	QList<Tower7*>TowList7;
	QList<Tower8*>TowList8;
	QList<Tower9*>TowList9;
	QList<Tower1*>TowList1_2;
	QList<Tower2*>TowList2_2;
	QList<Tower3*>TowList3_2;
	QList<Tower4*>TowList4_2;
	QList<Tower5*>TowList5_2;
	QList<Tower6*>TowList6_2;
	QList<Tower7*>TowList7_2;
	QList<Tower8*>TowList8_2;
	QList<Tower9*>TowList9_2;
	Boss1* Boss;
	~GameControl();
};

