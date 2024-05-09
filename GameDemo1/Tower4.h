#pragma once
#include "MySide.h"
class Tower4 :
    public MySide
{
public:
    static QList<Card*> cardList;
    static Card* getcard(QPoint cPos)
    {
        if (cardList.isEmpty())
        {
            for (int i = 0; i < 9; i++) {
                Card* ca = new Card("Tower4", GameDefine::TowerUrl4_1);
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
    void MyAce(MyScene* TargetScene);
    void Recover() override;
    Tower4();
    ~Tower4();
};

