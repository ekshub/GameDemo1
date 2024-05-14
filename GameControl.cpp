#include "GameControl.h"
#include"cmath"
GameControl* GameControl::instance = nullptr;

GameControl::GameControl()
{
    MonsterGenTimer1 = nullptr;
    MonsterGenTimer2 = nullptr;
    MonsterMoveTimer1 = nullptr;
    MainTimer = nullptr;
    mMap = nullptr;
    Boss = nullptr;
    
}
void GameControl::GameInit()
{
    Boss = new Boss1;
    MonsterGenTimer1 = new QTimer(this);
    MonsterGenTimer2 = new QTimer(this);
    MonsterMoveTimer1 = new QTimer(this);
    MainTimer = new QTimer(this);
    mGameView.setParent(Synodic_Month::MainWindow);
    mGameView.setFixedSize(GameDefine::WindowWidth, GameDefine::WindowHeight);
    LoadStartScene();

    LoadGameScene();
    state = true;
    
}

void GameControl::LoadStartScene()
{
    
    mbackground1.setPixmap(QPixmap(GameDefine::StartBackGroundUrl));
   
    StartScene.setSceneRect(QRect(0, 0, GameDefine::WindowWidth, GameDefine::WindowHeight));

    auto startBtn = new QToolButton();
    startBtn->setAutoRaise(true);
    
    QPixmap img = QPixmap("D:\\tower\\start.png");
   
    
    startBtn->setFixedSize(img.size());
    startBtn->setStyleSheet(GameDefine::TransparentButtonSytle);
    startBtn->setIcon(img);

    startBtn->setIconSize(img.size());
    
    startBtn->move(535, 650);
    StartScene.addItem(&mbackground1);
    StartScene.addWidget(startBtn);
    connect(startBtn, &QToolButton::clicked, [this]() {
        //this->LoadGameScene();
        GameStart();
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
    connect(MonsterGenTimer1, &QTimer::timeout, [this]() {
        EnemySide* mon = (EnemySide*)GameObjectPool::Instance()->GetGameObject(rand()%3+GameObject::OT_Monster1);
        
        mon->init(QPoint(1300, rand()%5*120+250));
        mon->isAlive = true;
        MonList1.append(mon);
        GameScene.addItem(mon->MyMov);
        GameScene.addWidget(mon->HPBar);
        });

    
    connect(MonsterMoveTimer1, &QTimer::timeout, [this]() {
        Collison();
        for (auto i : MonList1)
        {
            i->Move();
        }
        });

    connect(MainTimer, &QTimer::timeout, [this]() {
        BulletMove();
        CheckOutBound();
        DeadRecover();
        CheckUpgrade();
        UpdateTime();
        CheckState();
        Displayer::Instance()->showHP(HP);
        Displayer::Instance()->showCoin(Coin);
        Displayer::Instance()->showLevel(XP, level);

        });

    LoadGameMap();
    LoadCards();
    


}

void GameControl::LoadGameMap()
{
    mMap = new GameMap(this);
    if (!mMap->InitByFile(GameDefine::GameMap01)) { QMessageBox::warning(Synodic_Month::MainWindow, "warning", "failed to open the initmap file"); }
    mMap->DrawMap();
}

void GameControl::LoadCards()
{
    for(int j= GameObject::OT_Tower1;j< GameObject::OT_Tower1+9;j++)
    for (int i = 0; i < 10; i++)
    {
        AllCardList.append(j);
    }
    
}



void GameControl::GameStart()
{
    GameObjectPool::Instance()->Init();
    mGameView.setScene(&GameScene);
    mGameView.adjustSize();
    mGameView.show();
   
    MainTimer->start(10);
    BaseTime = QTime::currentTime();
    MonsterMoveTimer1->start(30);
    //Boss->Enter();
    Displayer::Instance()->Init(&GameScene);
    XP = GameDefine::XP ;
    level = GameDefine::level;
    Coin = GameDefine::Coin;
    Round = GameDefine::Round;
    HP = GameDefine::HP;
    mMap->showMap(&GameScene);
    getCards();
    RoundOver();
    
}

void GameControl::getCards()
{
    if (Coin - 2 < 0)
        return;
    for (auto i : CardList)
    {
        CardRecover(i);
    }
    Coin -= 2;
    for (int j = 0; j < (level+1)/2; j++)
    {
        int i = j;
        if ((level + 1)/2 == 1)
            i = 2;
        else if ((level + 1) / 2 == 2)
        {
            if (j == 0)
            i = j + 1;
            else
                i = j + 2;
        }
        else if ((level + 1) / 2 == 3)
            i =j+1;
        int ca = AllCardList[rand()%AllCardList.size()];
        Card* temp;
        switch (ca)
        {
        case GameObject::OT_Tower1: {
            temp=Tower1::getcard(QPoint(150*i + 350,600));
            break;
        }
        case GameObject::OT_Tower2: {
            temp = Tower2::getcard(QPoint(150 * i + 350, 600));
            break;
        }
        case GameObject::OT_Tower3: {
            temp = Tower3::getcard(QPoint(150 * i + 350, 600));
            break;
        }
        case GameObject::OT_Tower4: {
            temp = Tower4::getcard(QPoint(150 * i + 350, 600));
            break;
        }
        case GameObject::OT_Tower5: {
            temp = Tower5::getcard(QPoint(150 * i + 350, 600));;
            break;
        }
        case GameObject::OT_Tower6: {
            temp = Tower6::getcard(QPoint(150 * i + 350, 600));
            break;
        }
        case GameObject::OT_Tower7: {
            temp = Tower7::getcard(QPoint(150 * i + 350, 600));
            break;
        }
        case GameObject::OT_Tower8: {
            temp = Tower8::getcard(QPoint(150 * i+350, 600));;
            break;
        }
        case GameObject::OT_Tower9: {
            temp = Tower9::getcard(QPoint(150 * i + 350, 600));
            break;
        }
        }
        temp->num = ca;
        GameScene.addItem(temp);
        CardList.append(temp);
    }
}

void GameControl::CreatTower(QPoint pos, int _object,MapItem* _Map)
{
    MySide* Tow=nullptr;
    if (_object == GameObject::OT_Tower1)
    {
        Tow = (MySide*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower1);
        Tower1*  tow = (Tower1*)Tow;
        TowList1.append(tow);
        

    }
    else if (_object == GameObject::OT_Tower2)
    {
        Tow = (MySide*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower2);
        
   
        TowList2.append((Tower2*)Tow);
        Tow->AttackTimer->start(1000);
    }
    else if (_object == GameObject::OT_Tower3)
    {
        Tow = (MySide*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower3);
        TowList3.append((Tower3*)Tow);
    }

    else if (_object == GameObject::OT_Tower4)
    {
        Tow = (MySide*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower4);
        TowList4.append((Tower4*)Tow);
    }

    else if (_object == GameObject::OT_Tower5)
    {
        Tow = (MySide*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower5);
        TowList5.append((Tower5*)Tow);
    }
    else if (_object == GameObject::OT_Tower6)
    {
        Tow = (MySide*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower6);
        TowList6.append((Tower6*)Tow);
    }
    else if (_object == GameObject::OT_Tower7)
    {
        Tow = (MySide*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower7);
        TowList7.append((Tower7*)Tow);
        
    }
    else if (_object == GameObject::OT_Tower8)
    {
        Tow = (MySide*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower8);
        TowList8.append((Tower8*)Tow);
        
            }
    else if (_object == GameObject::OT_Tower9)
    {
        Tow = (MySide*)GameObjectPool::Instance()->GetGameObject(GameObject::OT_Tower9);
        TowList9.append((Tower9*)Tow);
        
            }
    if (Tow != nullptr)
    {
        Tow->init(pos, _Map);
        GameScene.addItem(Tow->MyMov);
        MySideList.append(Tow);
        Coin -= 5;
    }
}

void GameControl::UpdateTime()
{
    QTime current = QTime::currentTime();//获取系统当前时间
    int t = this->BaseTime.msecsTo(current);//两者相减的时间之差
    Displayer::Instance()->showTime(t);
    if (t >= GameDefine::roundE && t <= GameDefine::roundE +1000&&state==true)
    {
        BaseTime = QTime::currentTime();
        RoundOver();
    }
    else if (t >= GameDefine::roundS && t <= GameDefine::roundS+1000 && state == false)
    {
        BaseTime = QTime::currentTime();
        RoundStart();
    }
    else if (t >= GameDefine::roundE && t <= GameDefine::roundE+10000 && state == true)
    {
        MonsterGenTimer1->stop();
    }
}

void GameControl::RoundStart()
{
    if(Round==0)
    MonsterGenTimer1->start(4000);
else 
MonsterGenTimer1->start(2000);
    state = true;
    for (auto tow : MySideList)
        tow->StartAtt();
    Displayer::Instance()->showRound(++Round);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            mMap->mGameMap[i][j].setAcceptDrops(false);
        }
    }
}

void GameControl::RoundOver()
{
    state = false;
    MonsterGenTimer1->stop();
    for (auto tow : MySideDList)
    {
        MySideDList.removeOne(tow);
        MySideList.append(tow);
        
    }
    for (auto tow : MySideList)
    {
        tow->Reset();
    }
    for (auto mon : MonList1)
    {
        MonsterRecover(mon);
        HP -= 2;
    }
    Coin += Coin % 10;
    Displayer::Instance()->showRound(Round);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            mMap->mGameMap[i][j].setAcceptDrops(true);
        }
    }
}

void GameControl::TowerRecover(MySide* tow)
{
    GameScene.removeItem(tow->MyMov);
    MySideList.removeOne(tow);
    
    GameObjectPool::Instance()->RecoveryGameObject(tow);
    tow->ParentMap->onfree = true;

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

void GameControl::sellTower(MySide* tow)
{
    AllCardList.append(tow->GetType());
    TowerRecover(tow);

}

void GameControl::TowerRevive(MySide* tow)
{
    
    MySideDList.removeOne(tow);
    MySideList.append(tow);
}


void GameControl::DeadRecover()
{
    for (auto i : MonList1)
    {
        if (i->IsDead())
        {
            i->death();
            MonsterRecover(i);
            if (rand() % 5 == 0)
                Coin++;
        }
    }
    for (auto tow : MySideList)
    {
        if (tow->IsDead())
        {
            tow->death();
            MySideList.removeOne(tow);
            MySideDList.append(tow);
        }
    }
}

void GameControl::MonsterRecover(EnemySide* i)
{
    i->death();
    i->isAlive = false;
    GameScene.removeItem(i->MyMov);
    delete i->HPBar;
    i->HPBar = nullptr;
    MonList1.removeOne(i);
    GameObjectPool::Instance()->RecoveryGameObject(i);
    i->MyMov->Mov->stop();
}

void GameControl::BulletRecover(Bullet* Bul,int _obj)
{

   if (_obj == GameObject::OT_Tower4)
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
    MainTimer->stop();
    Displayer::Instance()->showRound(-1);
    for (auto i : CardList)
        CardRecover(i);
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
    mMap->hideMap(&GameScene);
    GameObjectPool::Instance()->Clear();
    Round = -1;
}

void GameControl::Collison()
{
    for (auto mon : MonList1)
    {
        for(auto tow:MySideList)
            for(auto Bul:tow->TracingBulletList)
        if (Bul->collidesWithItem(mon->MyMov)&&tow->GetType()!=GameObject::OT_Tower9)
        {

            mon->HP -= Bul->Harm;
            mon->HPBar->setValue(mon->HP * 100 / mon->MaxHP);
            if(tow->GetType()== GameObject::OT_Tower1)
            BulletRecover(Bul, tow->GetType());
            if(tow->GetType() == GameObject::OT_Tower7)
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
    for (auto i : MonList1)
    {
        if (i->MyMov->pos().x() < 10)
        {
            MonsterRecover(i);
            HP -= 2;
        }
    }
}

void GameControl::CheckUpgrade()
{
    if (level <= 8 && XP >= MaxXP[level-1])
    {
        level++;
        XP -= MaxXP[level -2];
    }
    if (TowList1.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList1.first();
            TowerRecover(tow);
        }
        Tower1* tow = TowList1.first();
        TowList1.pop_front();
        MySideList.removeOne(tow);
        TowList1_2.append(tow);
        tow->Upgrade();
    }
    if (TowList2.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList2.first();
            TowList2.pop_front();
            TowerRecover(tow);
        }
        Tower2* tow = TowList2.first();
        TowList2.pop_front();
        MySideList.removeOne(tow);
        TowList2_2.append(tow);
        tow->Upgrade();
    }
    if (TowList3.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList3.first();
            TowList3.pop_front();
            TowerRecover(tow);
        }
        Tower3* tow = TowList3.first();
        TowList3.pop_front();
        TowList3_2.append(tow);
        tow->Upgrade();
    }
    if (TowList4.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList4.first();
            TowList4.pop_front();
            TowerRecover(tow);
        }
        Tower4* tow = TowList4.first();
        TowList4.pop_front();
        TowList4_2.append(tow);
        tow->Upgrade();
    }
    if (TowList5.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList5.first();
            TowList5.pop_front();
            TowerRecover(tow);
        }
        Tower5* tow = TowList5.first();
        TowList5.pop_front();
        TowList5_2.append(tow);
        tow->Upgrade();
    }
    if (TowList6.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList6.first();
            TowList6.pop_front();
            TowerRecover(tow);
        }
        Tower6* tow = TowList6.first();
        TowList6.pop_front();
        TowList6_2.append(tow);
        tow->Upgrade();
    }
    if (TowList7.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList7.first();
            TowList7.pop_front();
            TowerRecover(tow);
        }
        Tower7* tow = TowList7.first();
        TowList7.pop_front();
        TowList7_2.append(tow);
        tow->Upgrade();
    }
    if (TowList8.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList8.first();
            TowList8.pop_front();
            TowerRecover(tow);
        }
        Tower8* tow = TowList8.first();
        TowList5.pop_front();
        TowList8_2.append(tow);
        tow->Upgrade();
    }
    if (TowList9.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList9.first();
            TowList9.pop_front();
            TowerRecover(tow);
        }
        Tower8* tow = TowList8.first();
        TowList5.pop_front();
        TowList8_2.append(tow);
        tow->Upgrade();
    }
    if (TowList1_2.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList1_2.first();
            TowerRecover(tow);
        }
        Tower1* tow = TowList1_2.first();
        TowList1_2.pop_front();
        MySideList.removeOne(tow);
        tow->Upgrade();
    }
    if (TowList2_2.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList2_2.first();
            TowList2_2.pop_front();
            TowerRecover(tow);
        }
        Tower2* tow = TowList2_2.first();
        TowList2_2.pop_front();
        tow->Upgrade();
    }
    if (TowList3_2.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList3_2.first();
            TowList3_2.pop_front();
            TowerRecover(tow);
        }
        Tower3* tow = TowList3_2.first();
        TowList3_2.pop_front();
        tow->Upgrade();
    }
    if (TowList4_2.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList4_2.first();
            TowList4_2.pop_front();
            TowerRecover(tow);
        }
        Tower4* tow = TowList4_2.first();
        TowList4_2.pop_front();

        tow->Upgrade();
    }
    if (TowList5_2.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList5_2.first();
            TowList5_2.pop_front();
            TowerRecover(tow);
        }
        Tower5* tow = TowList5_2.first();
        TowList5_2.pop_front();

        tow->Upgrade();
    }
    if (TowList6_2.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList6_2.first();
            TowList6_2.pop_front();
            TowerRecover(tow);
        }
        Tower6* tow = TowList6_2.first();
        TowList6_2.pop_front();
        tow->Upgrade();
    }
    if (TowList7_2.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList7_2.first();
            TowList7_2.pop_front();
            TowerRecover(tow);
        }
        Tower7* tow = TowList7_2.first();
        TowList7_2.pop_front();
        tow->Upgrade();
    }
    if (TowList8_2.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList8_2.first();
            TowList8_2.pop_front();
            TowerRecover(tow);
        }
        Tower8* tow = TowList8_2.first();
        TowList8_2.pop_front();
        tow->Upgrade();
    }
    if (TowList9_2.size() >= 3)
    {
        for (int i = 0; i < 2; i++)
        {
            MySide* tow = TowList9_2.first();
            TowList9_2.pop_front();
            TowerRecover(tow);
        }
        Tower9* tow = TowList9_2.first();
        TowList9_2.pop_front();

        tow->Upgrade();
    }
}

void GameControl::CheckState()
{
    if (Round == 11)
    {
        GameOver();
        
        Endpix.setPixmap( QPixmap("D:\\tower\\vectory2.png"));
        Endpix.moveBy(170, -20);
        GameScene.addItem(&Endpix);
    }
    else if (HP <= 0)
    {
        GameOver();

        Endpix.setPixmap(QPixmap("D:\\tower\\lose.png"));
        Endpix.moveBy(370, 120);
        GameScene.addItem(&Endpix);
    }
    
}



void GameControl::keyPressEvent(QKeyEvent* event)
{
    if (Round == -1)
    {
        mGameView.setScene(&StartScene);
        mGameView.adjustSize();
        mGameView.show();
    }
    if (event->key() == Qt::Key_D)
        getCards();
    else if (event->key() == Qt::Key_F&&Coin - 2 > 0 && level < 9)
    {
        Coin -= 2;
        XP += 2;
    }
    else if (event->key() == Qt::Key_Escape)
    {
        mGameView.setScene(&StartScene);
        mGameView.adjustSize();
        mGameView.show();
        GameOver();
    }
    
    
}

GameControl::~GameControl()
{
    for (auto i : MonList1)
        delete i;
    for (auto i : MySideList)
        delete i;
    for (auto i : MySideDList)
        delete i;
    delete MainTimer;//主定时器，控制游戏主体逻辑
    delete MonsterGenTimer1;
    delete MonsterGenTimer2;
    delete MonsterMoveTimer1;
}

