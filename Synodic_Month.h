#pragma once

#include <QtWidgets/QMainWindow>
#include "GameDefine.h"
#pragma warning(disable : 4828)
class Synodic_Month : public QMainWindow
{
    Q_OBJECT

public:
    Synodic_Month(QWidget *parent = nullptr);
    ~Synodic_Month();
    void keyPressEvent(QKeyEvent* event);
    static Synodic_Month* MainWindow;
    
private:
    
};
