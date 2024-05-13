#pragma once
#include "GameDefine.h"
#include "MapItem.h"
#pragma warning(disable : 4828)
enum MapElent
{
    Road,
    Wall,
    Box,
    Point,
    Inpoint
};
class GameMap :public QObject
{
	Q_OBJECT
    public:
        explicit GameMap(QObject* parent = nullptr);
        ~GameMap();
        bool InitByFile(QString filename);
        void DrawMap();
        void hideMap(QGraphicsScene* Mapscene);
        void showMap(QGraphicsScene* Mapscene);
        MapItem** mGameMap;
        int mRow;
        int mCol;
        int** mpArr;//开辟二维数组

};

