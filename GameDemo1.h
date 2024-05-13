#pragma once

#include <QtWidgets/QMainWindow>
#include "GameDefine.h"

class GameDemo1 : public QMainWindow
{
    Q_OBJECT

public:
    GameDemo1(QWidget *parent = nullptr);
    ~GameDemo1();
    void keyPressEvent(QKeyEvent* event);
    static GameDemo1* MainWindow;
    
private:
    
};
