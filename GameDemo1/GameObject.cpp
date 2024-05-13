#include "GameObject.h"

GameObject::GameObject(QObject* parent) 
{
	AttackTimer = new QTimer;
}

GameObject::~GameObject()
{
	delete AttackTimer;
	delete AttMov;
}

int GameObject::GetType()
{
	if(this!=nullptr)
	return mObjectType;
}

void GameObject::init(QPoint _Pos) 
{
	this->Pos = _Pos;
	this->setPos(Pos);
}
bool GameObject::IsDead()
{
	if (this->HP <= 0)
		return true;
	return false;
}