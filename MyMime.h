#pragma once
#include <QMimeData>
#include"GameObject.h"

class MyMime :
    public QMimeData
{
public:
    QObject* ptr;
    
};

