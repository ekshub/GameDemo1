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
//游戏定义类
class GameDefine
{
	
	GameDefine();
public:
	//定时器管理
	static const int MonsterCreatTimer1 = 100;
	static const int MonsterCreatTimer2 = 200;
	static const int MonsterMoveUpdateTimer1 = 2;

	//窗口元素
	static const int WindowWidth = 1400;
	static const int WindowHeight = 800;

	//图片路径
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

	//样式
	static const QString TransparentButtonSytle;

};

