#pragma once
#include"MySide.h"

class Tower2 :
    public MySide
{
public:
    static QList<Card*> cardList;
    static Card* getcard(QPoint cPos)
    {
        if (cardList.isEmpty())
        {
            for (int i = 0; i < 9; i++) {
                Card* ca = new Card("Tower2", GameDefine::TowerUrl2_1);
                cardList.append(ca);
            }
        }
        Card* card = cardList.first();
        card->setPos(cPos);
        cardList.removeFirst();
        return card;
    }
    int count;
    void init(QPoint _Pos, MapItem* _Map) override;
    void BulletMove() override;
    void MyAce(MyScene* TargetScene=nullptr) override;
    void Upgrade() override;
    Tower2();
    ~Tower2();
    void Reset()override;
};

