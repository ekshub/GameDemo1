#pragma once
#include "MySide.h"
class Tower4 :
    public MySide
{
public:
    static QList<Card*> cardList;//静态变量，存储该对象卡牌的链表，用于抽卡，注意在cpp文件中对其初始化
    static Card* getcard(QPoint cPos)//静态函数，获取卡牌
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
    //对基类函数进行重写并覆盖
    void init(QPoint _Pos, MapItem* _Map) override;
    void BulletMove() override;
    void MyAce(MyScene* TargetScene=nullptr) override;
    void Recover() override;

    Tower4();
    ~Tower4();
};

