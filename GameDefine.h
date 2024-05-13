#pragma once
#include<QGraphicsPixmapItem>
#include<QGraphicsProxyWidget>
#include <QApplication>
#include<QTimer>
#include<QList>
#include<QToolButton>
#include<QMessageBox>
#include<QObject>
#include<QFile>
#include<QCursor>
#include<QMouseEvent>
#include<QGraphicsSceneMouseEvent>
#include<QDrag>
#include<QMovie>
#include<QLcdNumber>
#include<QGroupBox>
#include <QProgressBar>
#include"MyLabel.h"
#include <QMutex>
#include"MyMime.h"
#include"MyScene.h"
#include"MyView.h"
#include"math.h"
//��Ϸ������
class GameDefine
{
	
	GameDefine();
public:
	//��ʱ������
	static const int MonsterCreatTimer1 = 100;
	static const int MonsterCreatTimer2 = 200;
	static const int MonsterMoveUpdateTimer1 = 2;

	//����Ԫ��
	static const int WindowWidth = 1400;
	static const int WindowHeight = 800;

	//ͼƬ·��
	static const QString MonsterUrl1;
	static const QString StartBackGroundUrl;
	static const QString GameGroundUrl;
	static const QString GameMap01;
	static const QString IconBaseUrl;
	static const QString TowerUrl1_1;
	static const QString TowerUrl2_1;
	static const QString TowerUrl3_1;
	static const QString TowerUrl4_1;
	static const QString TowerUrl5_1;
	static const QString TowerUrl6_1;
	static const QString TowerUrl7_1;
	static const QString TowerUrl8_1;
	static const QString TowerUrl9_1;

	//��ʽ
	static const QString TransparentButtonSytle;

};

