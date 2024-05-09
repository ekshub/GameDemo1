#pragma once
#include "MySide.h"
class Tower6 :
    public MySide
{
public:
    static QList<Card*> cardList;
    static Card* getcard(QPoint cPos)
    {
        if (cardList.isEmpty())
        {
            for (int i = 0; i < 9; i++) {
                Card* ca = new Card("Tower6", GameDefine::TowerUrl6_1);
                cardList.append(ca);
            }
        }
        Card* card = cardList.first();
        card->setPos(cPos);
        cardList.removeFirst();
        return card;
    }
    void init(QPoint _Pos) override;
    void BulletMove() override;
    void Recover() override;
    
    void MyAce(MyScene* TargetScene);
    Tower6();
    ~Tower6();
};

