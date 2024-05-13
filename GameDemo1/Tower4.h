#pragma once
#include "MySide.h"
class Tower4 :
    public MySide
{
public:
    static QList<Card*> cardList;//��̬�������洢�ö����Ƶ��������ڳ鿨��ע����cpp�ļ��ж����ʼ��
    static Card* getcard(QPoint cPos)//��̬��������ȡ����
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
    //�Ի��ຯ��������д������
    void init(QPoint _Pos, MapItem* _Map) override;
    void BulletMove() override;
    void MyAce(MyScene* TargetScene=nullptr) override;
    void Recover() override;

    Tower4();
    ~Tower4();
};

