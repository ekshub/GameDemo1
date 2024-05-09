#include "GameObject.h"

GameObject::GameObject(QObject* parent) 
{
}

GameObject::~GameObject()
{
}

int GameObject::GetType()
{
	return mObjectType;
}

void GameObject::init(QPoint _Pos) 
{
	this->Pos = _Pos;
	this->setPos(Pos);
}
