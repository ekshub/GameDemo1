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

	//��Ϸ�߼���ʱ����������ʼ�������
	void  GameStart();
	//��ȡ��Ƭ
	void getCards();
	//����Ϸ���������Tower������
	void CreatTower(QPoint pos, int _object,MapItem* _Map);
	//����ʱ��
	void UpdateTime();
	//�غϿ�ʼ
	void RoundStart();
	//�غϽ���
	void RoundOver();

	//����Tower
	void TowerRecover(MySide* tow);
	//����Tower
	void sellTower(MySide* tow);
	//����Tower
	void TowerRevive(MySide* tow);

	//�����������
	void DeadRecover();
	//�з�����
	void MonsterRecover(Monster1* i);
	//�ӵ�����
	void BulletRecover(Bullet*Bul, int _obj);
	//���ƻ���
	void CardRecover(Card* Car);
	//�ӵ��ƶ�
	void BulletMove();
	//��Ϸ��ʱ���رգ���ն���
	void GameOver();

	//��ײ���
	void Collison();
	
	//������
	void CheckOutBound();

	//�������
	void CheckUpgrade();
	//��Ϸ״̬���
	void CheckState();
	//��������¼�
	void keyPressEvent(QKeyEvent* event);

	GameMap* mMap;//��Ϸ��ͼ
	QList<Monster1*>MonList1;//�洢�з����������
	MyScene GameScene;//��Ϸ������
	QList<int> AllCardList;//���飬���ڼ�¼ÿ����ʣ�������
	QList<MySide*> MySideList;//�ҷ�����������
private:
	//��Ϸ������
	int HP;//Ѫ��
	int XP;//����
	int MaxXP[8] = {2,4,6,8,16,32,48,64};//�������辭��
	int Coin;//���
	int Round;//�غ�
	QTime BaseTime;//����ʱ�䣬���ڼ�ʱ
	bool state;//��Ϸ״̬
	int level;//�ȼ�

	QTimer* MainTimer;//����ʱ����������Ϸ�����߼�
	QTimer* MonsterGenTimer1;
	QTimer* MonsterGenTimer2;
	QTimer* MonsterMoveTimer1;
	
	QList<Card*> CardList;//�洢���Ƶ�����
	
	QList<MySide*> MySideDList;//�洢������λ������
	MyView mGameView;//��Ϸ��ͼ
	MyScene StartScene;//��ʼ����
	QGraphicsPixmapItem mbackground1;//��Ϸ����1
	QGraphicsPixmapItem mbackground2;//��Ϸ����2
	QGraphicsPixmapItem Endpix ;//��Ϸ����ͼƬ
	//��¼��������ӵ��������ҷ�����
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

