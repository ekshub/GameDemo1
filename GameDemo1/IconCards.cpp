#include "IconCards.h"
#include "Tower1.h"
IconCards* IconCards::instance = nullptr;
QString* IconCards::IconName = new QString[3]{"1","2","3"};

Card* IconCards::CardFactory(int _iconType)
{
	return 0;
}

void IconCards::LoadIcon(GameObject* _object)
{
}
