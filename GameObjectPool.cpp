#include "GameObjectPool.h"
#include"IconCards.h"

GameObjectPool* GameObjectPool::instance = nullptr;
GameObjectPool::GameObjectPool(QObject* parent) :QObject(parent)
{
}

void GameObjectPool::ObjectFactory(int _objectType)
{
	switch (_objectType)
	{
	case GameObject::OT_Monster1:
	{
		for (int i = 0; i < 10; i++)
		{
			Monster1* Mon = new Monster1(this);
			MonPool.append(Mon);
		}
		break;
	}
	case GameObject::OT_Tower1:
	{
		for (int i = 0; i < 2; i++)
		{
			Tower1* Tow = new Tower1;
			TowerPool1.append(Tow);
		}
		break;
	}
	case GameObject::OT_Tower2:
	{
		for (int i = 0; i < 2; i++)
		{
			Tower2* Tow = new Tower2;
			TowerPool2.append(Tow);
		}
		break;
	}
	case GameObject::OT_Tower3:
	{
		for (int i = 0; i < 2; i++)
		{
			Tower3* Tow = new Tower3;
			TowerPool3.append(Tow);
		}
		break;
	}
	case GameObject::OT_Tower4:
	{
		for (int i = 0; i < 2; i++)
		{
			Tower4* Tow = new Tower4;
			TowerPool4.append(Tow);
		}
		break;
	}
	case GameObject::OT_Tower5:
	{
		for (int i = 0; i < 2; i++)
		{
			Tower5* Tow = new Tower5;
			TowerPool5.append(Tow);
		}
		break;
	}
	case GameObject::OT_Tower6:
	{
		for (int i = 0; i < 2; i++)
		{
			Tower6* Tow = new Tower6;
			TowerPool6.append(Tow);
		}
		break;
	}
	case GameObject::OT_Tower7:
	{
		for (int i = 0; i < 2; i++)
		{
			Tower7* Tow = new Tower7;
			TowerPool7.append(Tow);
		}
		break;
	}
	case GameObject::OT_Tower8:
	{
		for (int i = 0; i < 2; i++)
		{
			Tower8* Tow = new Tower8;
			TowerPool8.append(Tow);
		}
		break;
	}
	case GameObject::OT_Tower9:
	{
		for (int i = 0; i < 2; i++)
		{
			Tower9* Tow = new Tower9;
			TowerPool9.append(Tow);
		}
		break;
	}
	
	}
}


void GameObjectPool::Init()
{
	//预先生产对象
	for(int i=0 ; i<12 ; i++)
		ObjectFactory(i);
}

GameObject* GameObjectPool::GetGameObject(int _objectType)
{
	switch (_objectType)
	{
	case GameObject::OT_Monster1:
	{
		if (MonPool.isEmpty())
			ObjectFactory(_objectType);
		Monster1* Mon = MonPool.first();
		MonPool.pop_front();
		return Mon;
	}
	case GameObject::OT_Tower1:
	{
		if (TowerPool1.isEmpty())
			ObjectFactory(_objectType);
		Tower1* Tow = TowerPool1.first();
		TowerPool1.pop_front();
		return Tow;
	}
	case GameObject::OT_Tower2:
	{
		if (TowerPool2.isEmpty())
			ObjectFactory(_objectType);
		Tower2* Tow = TowerPool2.first();
		TowerPool2.pop_front();
		return Tow;
	}
	case GameObject::OT_Tower3:
	{
		if (TowerPool3.isEmpty())
			ObjectFactory(_objectType);
		Tower3* Tow = TowerPool3.first();
		TowerPool3.pop_front();
		return Tow;
	}
	case GameObject::OT_Tower4:
	{
		if (TowerPool4.isEmpty())
			ObjectFactory(_objectType);
		Tower4* Tow = TowerPool4.first();
		TowerPool4.pop_front();
		return Tow;
	}
	case GameObject::OT_Tower5:
	{
		if (TowerPool5.isEmpty())
			ObjectFactory(_objectType);
		Tower5* Tow = TowerPool5.first();
		TowerPool5.pop_front();
		return Tow;
	}
	case GameObject::OT_Tower6:
	{
		if (TowerPool6.isEmpty())
			ObjectFactory(_objectType);
		Tower6* Tow = TowerPool6.first();
		TowerPool6.pop_front();
		return Tow;
	}
	case GameObject::OT_Tower7:
	{
		if (TowerPool7.isEmpty())
			ObjectFactory(_objectType);
		Tower7* Tow = TowerPool7.first();
		TowerPool7.pop_front();
		return Tow;
	}
	case GameObject::OT_Tower8:
	{
		if (TowerPool8.isEmpty())
			ObjectFactory(_objectType);
		Tower8* Tow = TowerPool8.first();
		TowerPool8.pop_front();
		return Tow;
	}
	case GameObject::OT_Tower9:
	{
		if (TowerPool3.isEmpty())
			ObjectFactory(_objectType);
		Tower9* Tow = TowerPool9.first();
		TowerPool9.pop_front();
		return Tow;
	}
	}
	return nullptr;
}

void GameObjectPool::RecoveryGameObject(GameObject* _object)
{
	switch (_object->GetType())
	{
	case GameObject::OT_Monster1:
	{
		MonPool.append((Monster1*)_object);
		break;
	}
	case GameObject::OT_Tower1:
	{
		TowerPool1.append((Tower1*)_object);
		break;
	}
	case GameObject::OT_Tower2:
	{
		TowerPool2.append((Tower2*)_object);
		break;
	}
	case GameObject::OT_Tower3:
	{
		TowerPool3.append((Tower3*)_object);
		break;
	}
	case GameObject::OT_Tower4:
	{
		TowerPool4.append((Tower4*)_object);
		break;
	}
	case GameObject::OT_Tower5:
	{
		TowerPool5.append((Tower5*)_object);
		break;
	}
	case GameObject::OT_Tower6:
	{
		TowerPool6.append((Tower6*)_object);
		break;
	}
	case GameObject::OT_Tower7:
	{
		TowerPool7.append((Tower7*)_object);
		break;
	}
	case GameObject::OT_Tower8:
	{
		TowerPool8.append((Tower8*)_object);
		break;
	}
	case GameObject::OT_Tower9:
	{
		TowerPool9.append((Tower9*)_object);
		break;
	}

	}
}

void GameObjectPool::Clear()
{
	for (auto i : MonPool)
	{
		delete i;
		MonPool.removeOne(i);
	}
	for (auto i : TowerPool1)
	{
		delete i;
		TowerPool1.removeOne(i);
	}
	for (auto i : TowerPool2)
	{
		delete i;
		TowerPool2.removeOne(i);
	}
	for (auto i : TowerPool3)
	{
		delete i;
		TowerPool3.removeOne(i);
	}
	for (auto i : TowerPool4)
	{
		delete i;
		TowerPool4.removeOne(i);
	}
	for (auto i : TowerPool5)
	{
		delete i;
		TowerPool5.removeOne(i);
	}
	for (auto i : TowerPool6)
	{
		delete i;
		TowerPool6.removeOne(i);
	}
	for (auto i : TowerPool7)
	{
		delete i;
		TowerPool7.removeOne(i);
	}
	for (auto i : TowerPool8)
	{
		delete i;
		TowerPool8.removeOne(i);
	}
	for (auto i : TowerPool9)
	{
		delete i;
		TowerPool9.removeOne(i);
	}
	
}

GameObjectPool::~GameObjectPool()
{
	Clear();
}
