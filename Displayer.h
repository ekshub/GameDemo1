#pragma once
#include"GameDefine.h"
#pragma warning(disable : 4828)
class Displayer :
    public QGraphicsProxyWidget
{
	//单例
	Displayer();
	static Displayer* instance;
public:
	
	//获取单例
	static Displayer* Instance()
	{
		if (instance == nullptr)
			return instance = new Displayer;
		return instance;
	}
	QWidget* centralwidget;
	QLCDNumber* lcdNumber;
	QGroupBox* groupBox;
	QLabel* label;
	QLabel* label_2;
	QLabel* label_3;
	QLabel* label_4;
	QLabel* label_5;
	QGroupBox* groupBox_2;
	QGroupBox* groupBox_3;
	QGroupBox* groupBox_4;
	QGroupBox* groupBox_5;
	QGroupBox* groupBox_6;
	QProgressBar* progressBar;
	QProgressBar* progressBar_3;
	QString showstr;
	void Init(MyScene* TargetScene);
	void showTime(int t);
	void showHP(int t);
	void showRound(int t);
	void showCoin(int t);
	void showLevel(int xp, int le);
	void showBossHP();
	void showBossHP(int t);
};

