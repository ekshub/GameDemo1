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
    virtual ~MySide();//����������
    virtual void init(QPoint _Pos, MapItem* _Map);//��ʼ��
    virtual void Recover();//���ն���
    virtual void BulletMove() = 0;//���麯�������ƶ����ӵ����ƶ���ÿ�����������ӵ��͹�����ʽ��ͬ��ǿ��������д
    virtual void Upgrade();//���ƶ�������
    virtual void MyAce(MyScene* TargetScene=nullptr)=0;//���麯�������ƶ����ͷż���
    virtual void death();//���ƶ�������
    virtual void BulletRecover();//�����ӵ�
    virtual void Reset();//����״̬����
    virtual void StartAtt();//����ʼ����
    Bullet* getBullet();//���ӵ������л�ȡ�ӵ�
    int Harm;//�˺�
    QTimer* BulletSendTimer;//�����ͷŵĶ�ʱ��
    QTimer* AceStartTimer;//�����ͷż��ܵĶ�ʱ��
    QTimer* AceEndTimer;//���Ƽ��ܽ����Ķ�ʱ��
    QTimer* AceAttTimer;//�����п����õ���������ʱ��
    QString BulletUrl;//�ӵ�ͼ���·��
    int level;//����ĵȼ�
    RoleAni* MyMov;//����Ķ���������
    QMovie* AceMov;//���ܶ���
    QMovie* DeathMov;//��������
    bool isalive;//�Ƿ���
    bool AttState;//�Ƿ��ڹ���״̬
    MapItem* ParentMap;//����������ͼ
    QList<Bullet*> BulletList;//�洢�ӵ����������๹��ʱԤ�����ӵ����洢������ʱ����ȡ�ã�������Ż�
    QList<Bullet*>TracingBulletList;//���ڹ������ӵ�����BulletMove()���������ӵ���Ϊ
    QList<Bullet*> AceBulletList;//���ڼ��ܵ��ӵ�����MyAce()���������ӵ���Ϊ

};

