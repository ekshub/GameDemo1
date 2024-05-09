#include "GameControl.h"
#include"cmath"
#include<thread>
GameControl* GameControl::instance = nullptr;

GameControl::GameControl()
{
    MonsterGenTimer1 = nullptr;
    MonsterGenTimer2 = nullptr;
    MonsterMoveTimer1 = nullptr;
    MainTimer = nullptr;
    back = nullptr;
    mMap = nullptr;
    BackBtn = nullptr;
    BossAni = new RoleAni("D:\\Monster\\Boss0.gif");
    Tower4Ani = new RoleAni("D:\\tower\\tower4.gif");
    Tower5Ani = new RoleAni("D:\\tower\\tower5.gif");
}
void GameControl::GameInit()
{
    MonsterGenTimer1 = new QTimer(this);
    MonsterGenTimer2 = new QTimer(this);
    MonsterMoveTimer1 = new QTimer(this);
    MainTimer = new QTimer(this);
    mGameView.setParent(GameDemo1::MainWindow);
    mGameView.setFixedSize(GameDefine::WindowWidth, GameDefine::WindowHeight);
    LoadStartScene();
    LoadPanelScene();
    LoadGameScene();
}

void GameControl::LoadStartScene()
{
    
    mbackground1.setPixmap(QPixmap(GameDefine::StartBackGroundUrl));
    StartScene.addItem(BossAni);
    BossAni->Mov->start();
    BossAni->setPos(800, 0);
    StartScene.addItem(Tower4Ani);
    Tower4Ani->Mov->start();
    Tower4Ani->setPos(-50, -50);
    StartScene.addItem(Tower5Ani);
    Tower5Ani->Mov->start();
    Tower5Ani->setPos(120, 100);
    StartScene.setSceneRect(QRect(0, 0, GameDefine::WindowWidth, GameDefine::WindowHeight));

    auto startBtn = new QToolButton();
    startBtn->setAutoRaise(true);
    
    QPixmap img = QPixmap("D:\\Qt_code\\Kenney_gameIcons\\PNG\\Black\\1x\\next.png");
   
    
    startBtn->setFixedSize(img.size());
    startBtn->setStyleSheet(GameDefine::TransparentButtonSytle);
    startBtn->setIcon(img);

    startBtn->setIconSize(img.size());
    
    startBtn->move(900, 550);
    
    StartScene.addWidget(startBtn);
    connect(startBtn, &QToolButton::clicked, [this]() {
        //this->LoadGameScene();
        mGameView.setScene(&PanelScene);
        mGameView.adjustSize();
        mGameView.show();
        });

    mGameView.setScene(&StartScene);
    
    mGameView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mGameView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mGameView.adjustSize();
    mGameView.show();

}

void GameControl::LoadGameScene()
{
    
    GameScene.setSceneRect(QRect(0, 0, GameDefine::WindowWidth, GameDefine::WindowHeight));
    mbackground2.setPixmap(QPixmap(GameDefine::GameGroundUrl));
    GameScene.addItem(&mbackground2);
    
    
   
        BackBtn = new QToolButton();
        BackBtn->setAutoRaise(true);
        QPixmap img = QPixmap("D:\\Qt_code\\Kenney_gameIcons\\PNG\\Black\\1x\\previous.png");
        BackBtn->setFixedSize(img.size());
        BackBtn->setStyleSheet(GameDefine::TransparentButtonSytle);
        BackBtn->setIcon(img);
        BackBtn->setIconSize(img.size());
        BackBtn->move(900, 550);
        
    connect(BackBtn, &QToolButton::clicked, [this]() {
        //this->LoadGameScene();
        mGameView.setScene(&PanelScene);
        mGameView.adjustSize();
        mGameView.show();
        
        GameOver();
         
        });

    connect(MonsterGenTimer1, &QTimer::timeout, [this]() {
        Monster1* mon = (Monster1*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Monster1);
        mon->init(QPoint(1000, rand()%5*100));
        MonList1.append(mon);
        GameScene.addItem(mon->MyMov);
        GameScene.addWidget(mon->BloodBar);
        });

    
    connect(MonsterMoveTimer1, &QTimer::timeout, [this]() {
        Collison();
        DeadRecover();
        for (auto i : MonList1)
        {
            
            for (auto tow : MySideList)
            {
                if (i->MyMov->collidesWithItem(tow->MyMov))
                {
                    i->Actived = false;
                    break;
                }
            }
            if (i->Actived)
                i->Move();
            else
                i->Actived = true;
        }
        
        });

    connect(MainTimer, &QTimer::timeout, [this]() {
        BulletMove();
        CheckOutBound();
        
        });
    LoadGameMap();
    LoadCards();
    getCards();
    GameScene.addWidget(BackBtn);
}

void GameControl::LoadGameMap()
{
    mMap = new GameMap(this);
    if (!mMap->InitByFile(GameDefine::GameMap01)) { QMessageBox::warning(GameDemo1::MainWindow, "warning", "failed to open the initmap file"); }
    mMap->DrawMap(&GameScene);
}

void GameControl::LoadCards()
{
    for(int j= GameObject::OT_Tower1;j< GameObject::OT_Tower1+9;j++)
    for (int i = 0; i < 10; i++)
    {
        AllCardList.append(j);
    }
    
}

void GameControl::LoadPanelScene()
{
    PanelScene.setSceneRect(QRect(0, 0, GameDefine::WindowWidth, GameDefine::WindowHeight));
    back = new QGraphicsPixmapItem;
    back->setPixmap(QPixmap("D:\\Qt_code\\qtmainproject\\img\\FelisChaus_ParchmentBackground.jpg"));
    PanelScene.addItem(back);
    for (int i = 0; i < 9; i++)
    {
        Panel1[i].setPixmap(QPixmap("D:\\Qt_code\\PNG\\Cell01.png"));
        Panel1[i].setPos(i % 3 * 60 + 70, i / 3 * 60+220);
        PanelScene.addItem(&Panel1[i]);
    }
    QGraphicsPixmapItem *temp=new QGraphicsPixmapItem;
    temp->setPixmap(QPixmap("D:\\Qt_code\\qtmainproject\\img\\tower1.m.png"));
    temp->setPos(100, 0);
    PanelScene.addItem(temp);
    auto startBtn2 = new QToolButton();
    startBtn2->setAutoRaise(true);

    QPixmap img = QPixmap("D:\\Qt_code\\Kenney_gameIcons\\PNG\\Black\\1x\\next.png");
    for (int i = 0; i < 3; i++)
    {
        //IconCards::Instance()->CardFactory(i)->setPos(i * 60, 100);
        PanelScene.addItem(IconCards::Instance()->CardFactory(i));
    }

    startBtn2->setFixedSize(img.size());
    startBtn2->setStyleSheet(GameDefine::TransparentButtonSytle);
    startBtn2->setIcon(img);
    startBtn2->setIconSize(img.size());
    startBtn2->move(900, 550);

    PanelScene.addWidget(startBtn2);
    connect(startBtn2, &QToolButton::clicked, [this]() {
        GameStart();
        });
   
}



void GameControl::GameStart()
{
    GameObjectPool::Instance()->Init();
    mGameView.setScene(&GameScene);
    mGameView.adjustSize();
    mGameView.show();
    MonsterGenTimer1->start(4000);
    MainTimer->start(10);
    MonsterMoveTimer1->start(10);
}

void GameControl::getCards()
{
    for (auto i : CardList)
    {
        CardRecover(i);
    }
    for (int i = 0; i < 5; i++)
    {
        int ca = AllCardList[rand()%AllCardList.size()];
        Card* temp;
        switch (ca)
        {
        case GameObject::OT_Tower1: {
            temp=Tower1::getcard(QPoint(100*i,500));
            break;
        }
        case GameObject::OT_Tower2: {
            temp = Tower2::getcard(QPoint(100 * i, 500));
            break;
        }
        case GameObject::OT_Tower3: {
            temp = Tower3::getcard(QPoint(100 * i, 500));
            break;
        }
        case GameObject::OT_Tower4: {
            temp = Tower4::getcard(QPoint(100 * i, 500));
            break;
        }
        case GameObject::OT_Tower5: {
            temp = Tower5::getcard(QPoint(100 * i, 500));;
            break;
        }
        case GameObject::OT_Tower6: {
            temp = Tower6::getcard(QPoint(100 * i, 500));
            break;
        }
        case GameObject::OT_Tower7: {
            temp = Tower7::getcard(QPoint(100 * i, 500));
            break;
        }
        case GameObject::OT_Tower8: {
            temp = Tower8::getcard(QPoint(100 * i, 500));;
            break;
        }
        case GameObject::OT_Tower9: {
            temp = Tower9::getcard(QPoint(100 * i, 500));
            break;
        }
        }
        temp->num = ca;
        GameScene.addItem(temp);
        CardList.append(temp);
    }
}

void GameControl::CreatTower(QPoint pos, int _object)
{
    if (_object == GameObject::OT_Tower1)
    {
        Tower1* tow = (Tower1*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower1);
        tow->init(pos);
        GameScene.addItem(tow->MyMov);
        TowList1.append(tow);
        MySideList.append(tow);
        tow->AttackTimer->start(1000);

        connect(tow->AttackTimer, &QTimer::timeout, [=]() {
            if (!MonList1.isEmpty())
            {

                if (tow->count == 5)
                {

                    tow->MyAce(&GameScene, MonsterGenTimer1);
                }
                else {
                    tow->count++;
                    Bullet* Bul = tow->getBullet();
                    GameScene.addItem(Bul);
                    Bul->Mov->start();
                    Bul->setPos(tow->pos().x() + 105, tow->pos().y() + 53);
                    tow->TracingBulletList.append(Bul);
                }

            }
            });
    }
    else if (_object == GameObject::OT_Tower2)
    {
        Tower2* tow = (Tower2*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower2);
        tow->init(pos);
        GameScene.addItem(tow->MyMov);
        TowList2.append(tow);
        MySideList.append(tow);
        tow->AttackTimer->start(1000);
    }
    else if (_object == GameObject::OT_Tower3)
    {
        Tower3* tow = (Tower3*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower3);
        tow->init(pos);
        GameScene.addItem(tow->MyMov);
        TowList3.append(tow);
        MySideList.append(tow);
    }

    else if (_object == GameObject::OT_Tower4)
    {
        Tower4* tow = (Tower4*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower4);
        tow->init(pos);
        GameScene.addItem(tow->MyMov);
        TowList4.append(tow);
        MySideList.append(tow);
    }

    else if (_object == GameObject::OT_Tower5)
    {
        Tower5* tow = (Tower5*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower5);
        tow->init(pos);
        GameScene.addItem(tow->MyMov);
        TowList5.append(tow);
        MySideList.append(tow);
        
    }
    else if (_object == GameObject::OT_Tower6)
    {
        Tower6* tow = (Tower6*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower6);
        tow->init(pos);
        GameScene.addItem(tow->MyMov);
        TowList6.append(tow);
        MySideList.append(tow);
       
    }
    else if (_object == GameObject::OT_Tower7)
    {
        Tower7* tow = (Tower7*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower7);
        tow->init(pos);
        GameScene.addItem(tow->MyMov);
        TowList7.append(tow);
        MySideList.append(tow);
        
    }
    else if (_object == GameObject::OT_Tower8)
    {
        Tower8* tow = (Tower8*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower8);
        tow->init(pos);
        GameScene.addItem(tow->MyMov);
        TowList8.append(tow);
        MySideList.append(tow);
        
            }
    else if (_object == GameObject::OT_Tower9)
    {
        Tower9* tow = (Tower9*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower9);
        tow->init(pos);
        GameScene.addItem(tow->MyMov);
        TowList9.append(tow);
        MySideList.append(tow);
        
            }
}

void GameControl::TowerRecover(MySide* tow)
{
    GameScene.removeItem(tow->MyMov);
    MySideList.removeOne(tow);
    AllCardList.append(tow->GetType());
    GameObjectPool::Instance()->RecoveryGameObject(tow);
    mMap->mpArrB[(int(tow->pos().y()) - 10) / 100][int((tow->pos().x()) - 10) / 100] = true;
    for (auto i : tow->TracingBulletList)
    {
        i->Mov->stop();
        GameScene.removeItem(i);
        tow->TracingBulletList.removeOne(i);
        tow->BulletList.append(i);
    }
    tow->Recover();
    switch (tow->GetType())
    {
    case GameObject::OT_Tower1: {
        TowList1.removeOne(tow);
        break;
    }
    case GameObject::OT_Tower2: {
        TowList2.removeOne(tow);
        break;
    }
    case GameObject::OT_Tower3: {
        TowList3.removeOne(tow);
        break;
    }
    case GameObject::OT_Tower4: {
        TowList4.removeOne(tow);
        break;
    }
    case GameObject::OT_Tower5: {
        TowList5.removeOne(tow);
        break;
    }
    case GameObject::OT_Tower6: {
        TowList6.removeOne(tow);
        break;
    }
    case GameObject::OT_Tower7: {
        TowList7.removeOne(tow);
        break;
    }
    case GameObject::OT_Tower8: {
        TowList8.removeOne(tow);
        break;
    }
    case GameObject::OT_Tower9: {
        TowList9.removeOne(tow);
        break;
    }
    }
}




void GameControl::DeadRecover()
{
    for (auto i : MonList1)
    {
        if (i->IsBloodEmpty()||i->MyMov->pos().x()<10)
        {
            GameScene.removeItem(i->MyMov);
            delete i->BloodBar;
            i->BloodBar = nullptr;
            MonList1.removeOne(i);
            GameObjectPool::Instance()->RecoveryGameObject(i);
            i->MyMov->Mov->stop();
        }
    }
}

void GameControl::BulletRecover(Bullet* Bul,int _obj)
{
    if (_obj == GameObject::OT_Tower1)
    {
        ((Tower1*)Bul->parent)->BulletList.append(Bul);
        Bul->Mov->stop();
        GameScene.removeItem(Bul);
        ((Tower1*)Bul->parent)->TracingBulletList.removeOne(Bul);
        Bul->Temp = QPoint(0, 0);
    }
    else  if (_obj == GameObject::OT_Tower4)
    {
        ((Tower4*)Bul->parent)->BulletList.append(Bul);
        Bul->Mov->stop();
        GameScene.removeItem(Bul);
        ((Tower4*)Bul->parent)->TracingBulletList.removeOne(Bul);
        Bul->Temp = QPoint(0, 0);
    }
    
}

void GameControl::BulletMove()
{
    for (auto i : MySideList)
            i->BulletMove();
}

void GameControl::CardRecover(Card* Car)
{
    GameScene.removeItem(Car);
    Car->num = -1;
    CardList.removeOne(Car);
    if (Car->_Text == "Tower1")
        Tower1::cardList.append(Car);
    else if (Car->_Text == "Tower2")
        Tower2::cardList.append(Car);
    else if (Car->_Text == "Tower3")
        Tower3::cardList.append(Car);
    else if (Car->_Text == "Tower4")
        Tower4::cardList.append(Car);
    else if (Car->_Text == "Tower5")
        Tower5::cardList.append(Car);
    else if (Car->_Text == "Tower6")
        Tower6::cardList.append(Car);
    else if (Car->_Text == "Tower7")
        Tower7::cardList.append(Car);
    else if (Car->_Text == "Tower8")
        Tower8::cardList.append(Car);
    else if (Car->_Text == "Tower9")
        Tower9::cardList.append(Car);
}

void GameControl::GameOver()
{
    MonsterGenTimer1->stop();
    MonsterGenTimer2->stop();
    MonsterMoveTimer1->stop();
   
    for (auto i : MonList1)
    {
        GameScene.removeItem(i->MyMov);
        delete i;
        MonList1.removeOne(i);
    }

    for (auto i : MySideList)
    {
        TowerRecover(i);
    }
    GameObjectPool::Instance()->Clear();
}

void GameControl::Collison()
{
    for (auto mon : MonList1)
    {
        for(auto tow:TowList1)
            for(auto Bul:tow->TracingBulletList)
        if (Bul->collidesWithItem(mon->MyMov))
        {

            mon->BloodVolume -= Bul->Harm;
            mon->BloodBar->setValue(mon->BloodVolume * 100 / mon->MaxBlood);
            if(tow->GetType()== GameObject::OT_Tower1|| tow->GetType() == GameObject::OT_Tower9)
            BulletRecover(Bul, tow->GetType());
        }
        for (auto tow : TowList7)
            for (auto Bul : tow->TracingBulletList)
                if (Bul->collidesWithItem(mon->MyMov))
                {
                    mon->Actived = false;
                }
    }
}

void GameControl::CheckOutBound()
{
    for (auto i : MySideList)
        for (auto Bul : i->TracingBulletList)
            if (Bul->x() < 0 || Bul->y() < -10 || Bul->x() > 1400 || Bul->y() > 800)
                BulletRecover(Bul, GameObject::OT_Tower4);
}



void GameControl::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_D)
        getCards();
}

GameControl::~GameControl()
{
    for (auto i : MonList1)
        delete i;
    for (auto i : TowList1)
        delete i;
}

