#pragma once
#include "MySide.h"
class Tower8 :
    public MySide
{
public:
    static QList<Card*> cardList;
    static Card* getcard(QPoint cPos)
    {
        if (cardList.isEmpty())
        {
            for (int i = 0; i < 9; i++) {
                Card* ca = new Card("Tower8", GameDefine::TowerUrl8_1);
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
    bool state;
    QMovie* AttMov2;
    int Harm2;
    void MyAce(MyScene* TargetScene);
    Tower8();
    ~Tower8();
};

