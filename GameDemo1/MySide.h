#pragma once
#include "GameObject.h"
#include"RoleAni.h"
#include"Card.h"
#include"Bullet.h"
class MySide :
    public GameObject
{
public:
    MySide(QString _BurUrl,int _Harm);
    virtual void init(QPoint _Pos);
    virtual ~MySide();
    virtual void Recover();
    virtual void BulletMove() = 0;
    Bullet* getBullet();
    int Harm;
    int InitHarm;
    QTimer* AttackTimer;
    QTimer* AceStartTimer;
    QTimer* AceEndTimer;
    QTimer* AceAttTimer;
    QTimer* BulletSendTimer;
    QString BulletUrl;
    QList<Bullet*> BulletList;
    QList<Bullet*> AceBulletList;
    QList<Bullet*>TracingBulletList;
    RoleAni* MyMov;
    QMovie* AttMov;
    QMovie* AceMov;
    bool isBound;
};

