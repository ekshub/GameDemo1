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
#pragma warning(disable : 4828)
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
	static const QString TowMov1;
	static const QString TowMov2;
	static const QString TowMov3;
	static const QString TowMov4;
	static const QString TowMov5;
	static const QString TowMov6;
	static const QString TowMov7;
	static const QString TowMov8;
	static const QString TowMov9;
	static const QString TowAttMov1;
	static const QString TowAttMov2;
	static const QString TowAttMov3;
	static const QString TowAttMov4;
	static const QString TowAttMov5;
	static const QString TowAttMov6;
	static const QString TowAttMov7;
	static const QString TowAttMov8;
	static const QString TowAtt2Mov8;
	static const QString TowAttMov9;
	static const QString TowAceMov1;
	static const QString TowAceMov2;
	static const QString TowAceMov3;
	static const QString TowAceMov4;
	static const QString TowAceMov5;
	static const QString TowAceMov6;
	static const QString TowAceMov7;
	static const QString TowAceMov8;
	static const QString TowAceMov9;
	static const QString TowBul1;
	static const QString TowBul2;
	static const QString TowBul3;
	static const QString TowBul4;
	static const QString TowBul5;
	static const QString TowBul6;
	static const QString TowBul7;
	static const QString TowBul8;
	static const QString TowBul9;
	static const QString MonMov1;
	static const QString MonMov2;
	static const QString MonMov3;
	static const QString MonAtt1;
	static const QString MonAtt2;
	static const QString MonAtt3;
	static const QString Mon5Death;
	static const QString Mon5Death2;
	static const QString Mon5MoveSt ;
	static const QString Mon5MoveEn;
	static const QString Mon5MoveD;
	static const QString Mon5AttMov2;

	static const int TowHarm1 = 1000;
	static const int TowHarm2 = 1000;
	static const int TowHarm3 = 1000;
	static const int TowHarm4 = 1000;
	static const int TowHarm5 = 1000;
	static const int TowHarm6 = 1000;
	static const int TowHarm7 = 10;
	static const int TowHarm8 = 1000;
	static const int TowHarm9 = 1000;

	static const int TowHP1 = 10000;
	static const int TowHP2 = 10000;
	static const int TowHP3 = 10000;
	static const int TowHP4 = 10000;
	static const int TowHP5 = 10000;
	static const int TowHP6 = 10000;
	static const int TowHP7 = 10000;
	static const int TowHP8 = 10000;
	static const int TowHP9 = 10000;

	static const int TowMP1 = 1000;
	static const int TowMP2 = 1000;
	static const int TowMP3 = 1000;
	static const int TowMP4 = 1000;
	static const int TowMP5 = 1000;
	static const int TowMP6 = 1000;
	static const int TowMP7 = 1000;
	static const int TowMP8 = 1000;
	static const int TowMP9 = 1000;

	static const int MonHP1 =10000;
	static const int MonHP2 = 10000;
	static const int MonHP3 = 10000;
	//游戏控制项
	static const int XP = 0;
	static const int level = 1;
	static const int Coin = 779;
	static const int Round = 0;
	static const int  HP = 100;
	static const int roundS = 10000;
	static const int roundE = 40000;
	//样式
	static const QString TransparentButtonSytle;

};

