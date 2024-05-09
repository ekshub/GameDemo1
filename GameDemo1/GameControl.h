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
	//����
	GameControl();
	static GameControl* instance;
public:
	//��ȡ����
	static GameControl* Instance()
	{
		if (instance == nullptr)
			return instance = new GameControl();
		return instance;
	}

	//��Ϸ��ʼ��
	void GameInit();

	//���ؿ�ʼ����
	void LoadStartScene();

	//������Ϸ�������ź�����
	void LoadGameScene();

	//���ص�ͼ
	void LoadGameMap();
	
	//��������
	void LoadCards();

	//�������
	void LoadPanelScene();

	//��Ϸ�߼���ʱ����������ʼ�������
	void  GameStart();
	//��ȡ��Ƭ
	void getCards();
	//����Ϸ���������Tower������
	void CreatTower(QPoint pos, int _object);

	//����Tower
	void TowerRecover(MySide* tow);

	//�����������
	void DeadRecover();
	//�ӵ�����
	void BulletRecover(Bullet*Bul, int _obj);
	//�ӵ��ƶ�
	void BulletMove();
	void CardRecover(Card* Car);
	//��Ϸ��ʱ���رգ���ն���
	void GameOver();

	//��ײ���
	void Collison();
	
	//������
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

