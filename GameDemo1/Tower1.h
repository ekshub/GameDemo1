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
    void Trace(Bullet* Bul);
    int count;
    int ace;
    void init(QPoint _Pos) override;
    void BulletMove() override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    Tower1();
    ~Tower1();
    void MyAce(MyScene* TargetScene,QTimer* MonGenTimer);
};

