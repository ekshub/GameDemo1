#pragma once
#include "MySide.h"
#include "GameDefine.h"
#include"Monster1.h"
class Tower1 :
    public MySide
{
    
public:
    static QList<Card*> cardList;
    static Card* getcard(QPoint cPos)
    {
        if (cardList.isEmpty())
        {
            for (int i = 0; i < 9; i++) {
                Card* ca = new Card("Tower1", GameDefine::TowerUrl1_1);
                cardList.append(ca);
            }
        }
        Card* card = cardList.first();
        card->setPos(cPos);
        cardList.removeFirst();
        return card;
    }
    int ace;
    void init(QPoint _Pos, MapItem* _Map) override;
    void BulletMove() override;
    void Reset()override;
    Tower1();
    ~Tower1();
    void MyAce(MyScene* TargetScene=nullptr)override;
};

