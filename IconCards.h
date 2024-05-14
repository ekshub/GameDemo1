#pragma once
#include"GameDefine.h"
#include"Card.h"
#include"Synodic_Month.h"
#pragma warning(disable : 4828)
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
			return instance = new IconCards(Synodic_Month::MainWindow);
		return instance;
	}
	static QString* IconName;
	QList<Card*>  IconList;
	Card* CardFactory(int _iconType);
	void LoadIcon(GameObject* _object);
};

