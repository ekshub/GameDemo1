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

    QByteArray arrAll = file.readAll();//�ָ��ļ����ݲ������ͼ����
    arrAll.replace("\r\n", "\n");
    QList<QByteArray> lineList = arrAll.split('\n');
    mRow = lineList.size();
    mpArr = new int* [mRow];
    mpArrB = new bool* [mRow];
    for (int i = 0; i < mRow; i++)
    {
        QList<QByteArray>colList = lineList[i].split(',');
        mCol = colList.size();
        mpArr[i] = new int[mCol];
        mpArrB[i] = new bool [mCol];
        for (int j = 0; j < mCol; j++)
        {
            mpArr[i][j] = colList[j].toInt();
            mpArrB[i][j] = true;
        }
    }
 
    mGameMap = new MapItem * [mRow];

    return true;
}


void GameMap::DrawMap(QGraphicsScene* Mapscene)
{

    for (int i = 0; i < mRow; i++)
    {
        mGameMap[i] = new MapItem[mCol];

        for (int j = 0; j < mCol; j++)
        {
            QString Imgurl;
            switch (mpArr[i][j])
            {
            case Road:Imgurl = "D:\\Qt_code\\qtmainproject\\img\\back100x100.png";break;
            case Wall:Imgurl = "D:\\Qt_code\\qtmainproject\\img\\Map2_100x100.png"; break;
            }

            QPixmap img2(Imgurl);
            mGameMap[i][j].setPixmap(img2);
            mGameMap[i][j].setPos(10+j * (img2.width()), 10+i * img2.height());

            (*Mapscene).addItem(&mGameMap[i][j]);
            
        }
    }
}


