#include "IconCards.h"
#include "Tower1.h"
IconCards* IconCards::instance = nullptr;
QString* IconCards::IconName = new QString[3]{"1","2","3"};

Card* IconCards::CardFactory(int _iconType)
{
	
	Card * _card = new Card("Harm+1000", QString(GameDefine::IconBaseUrl).arg(_iconType + 1),QPoint(50,50));
	_card->setPos((_iconType + 1) * 50, 200);
	return _card;
	return nullptr;
}

void IconCards::LoadIcon(GameObject* _object)
{
	for (auto i : IconList)
	{
		QString Data = i->_Text;
		if (Data == "Harm+1000")
			((Tower1*)_object)->Harm = ((Tower1*)_object)->InitHarm+ 100;
	}
}
