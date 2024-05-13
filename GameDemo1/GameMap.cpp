#include "GameMap.h"


GameMap::GameMap(QObject* parent)//���캯��
    : QObject{ parent }, mRow{ 0 }, mCol{ 0 }, mpArr{ nullptr }
{}


GameMap::~GameMap()//��������
{
    if (mpArr != nullptr)
    {
        for (int i = 0; i < mRow; i++)
        {
            delete[] mpArr[i];
        }
        delete[] mpArr;
    }
    if (mGameMap != nullptr)
    {
        for (int i = 0; i < mRow; i++)
        {
            delete[] mGameMap[i];
        }
        delete[] mGameMap;
    }
}


bool GameMap::InitByFile(QString filename)//�����ļ���ʼ����ͼ����
{
    QFile file(filename);//�����ļ�����
    if (!file.open(QIODevice::ReadOnly))//�ļ���ʧ��
    {
        return false;
    }

    //QByteArray arrAll = file.readAll();//�ָ��ļ����ݲ������ͼ����
   // arrAll.replace("\r\n", "\n");
   // QList<QByteArray> lineList = arrAll.split('\n');
    //mRow = lineList.size();
    mpArr = new int* [5];
    
    for (int i = 0; i < 5; i++)
    {
        ///QList<QByteArray>colList = lineList[i].split(',');
        //mCol = colList.size();
        mpArr[i] = new int[15];
        
        for (int j = 0; j < 15; j++)
        {
            if(i%2==0)
            mpArr[i][j] = 1;
            else
                mpArr[i][j] = 0;
            
        }
    }

    
    mGameMap = new MapItem * [5];

    return true;
}


void GameMap::DrawMap()
{

    for (int i = 0; i < 5; i++)
    {
        mGameMap[i] = new MapItem[15];

        for (int j = 0; j < 11; j++)
        {
            QString Imgurl;
            switch (mpArr[i][j])
            {
            case Road:Imgurl = "D:\\tower\\MapItem.png";break;
            case Wall:Imgurl = "D:\\tower\\MapItem2.png"; break;
            }

            QPixmap img2(Imgurl);
            mGameMap[i][j].setPixmap(img2);
            mGameMap[i][j].setPos(j * (img2.width()), 150+i * img2.height());
            
        }
    }
}

void GameMap::hideMap(QGraphicsScene* Mapscene)
{
    for (int i = 0; i < 5; i++)
    {
       

        for (int j = 0; j < 11; j++)
        {
            (*Mapscene).removeItem(&mGameMap[i][j]);
        }
    }
}

void GameMap::showMap(QGraphicsScene* Mapscene)
{
    for (int i = 0; i < 5; i++)
    {


        for (int j = 0; j < 11; j++)
        {
            (*Mapscene).addItem(&mGameMap[i][j]);
        }
    }
}


