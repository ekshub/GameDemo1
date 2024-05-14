#pragma once
#include<QGraphicsPixmapItem>
#include <QGraphicsSceneDragDropEvent>
#pragma warning(disable : 4828)
class Card :public QGraphicsPixmapItem
{
	
public:
	Card();
	QString _Text;
	QString _Pix;
	int num;
	Card(QString text, QString pixmap, QPoint Pos=QPoint(0,0));
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

