#pragma once
#include"GameDefine.h"
#include"Card.h"
#include"GameDemo1.h"
class IconCards :public QObject
{
	//µ¥Àý
	IconCards(QObject* parent = nullptr)
	{}
	static IconCards* instance;
public:
	enum IconType
	{
		
	};
	static IconCards* Instance()
	{
		if (instance == nullptr)
			return instance = new IconCards(GameDemo1::MainWindow);
		return instance;
	}
	static QString* IconName;
	QList<Card*>  IconList;
	Card* CardFactory(int _iconType);
	void LoadIcon(GameObject* _object);
};

