#pragma once
#include "GameObject.h"
#include"Card.h"
#include"Bullet.h"
#include"MapItem.h"
#pragma warning(disable : 4828)
class MySide :
    public GameObject
{
public:
    MySide(QString _BurUrl,int _Harm);
    virtual ~MySide();//虚析构函数
    virtual void init(QPoint _Pos, MapItem* _Map);//初始化
    virtual void Recover();//回收对象
    virtual void BulletMove() = 0;//纯虚函数，控制对象子弹的移动，每个子类对象的子弹和攻击方式不同，强制子类重写
    virtual void Upgrade();//控制对象升级
    virtual void MyAce(MyScene* TargetScene=nullptr)=0;//纯虚函数，控制对象释放技能
    virtual void death();//控制对象死亡
    virtual void BulletRecover();//回收子弹
    virtual void Reset();//对象状态重置
    virtual void StartAtt();//对象开始攻击
    Bullet* getBullet();//从子弹链表中获取子弹
    int Harm;//伤害
    QTimer* BulletSendTimer;//攻击释放的定时器
    QTimer* AceStartTimer;//控制释放技能的定时器
    QTimer* AceEndTimer;//控制技能结束的定时器
    QTimer* AceAttTimer;//技能中可能用到的其他定时器
    QString BulletUrl;//子弹图像的路径
    int level;//对象的等级
    RoleAni* MyMov;//对象的动画播放器
    QMovie* AceMov;//技能动画
    QMovie* DeathMov;//死亡动画
    bool isalive;//是否存活
    bool AttState;//是否处于攻击状态
    MapItem* ParentMap;//对象所属地图
    QList<Bullet*> BulletList;//存储子弹的链表，在类构造时预生产子弹并存储，攻击时从中取用，结束后放回
    QList<Bullet*>TracingBulletList;//用于攻击的子弹，由BulletMove()函数控制子弹行为
    QList<Bullet*> AceBulletList;//用于技能的子弹，由MyAce()函数控制子弹行为

};

