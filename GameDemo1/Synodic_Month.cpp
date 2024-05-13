#include "Synodic_Month.h"
#include"GameControl.h"

Synodic_Month* Synodic_Month::MainWindow = nullptr;

Synodic_Month::Synodic_Month(QWidget *parent)
    : QMainWindow(parent)
{
    MainWindow = this;
    setFixedSize(GameDefine::WindowWidth, GameDefine::WindowHeight);
    MainWindow->setWindowTitle("Synodic Month");
    MainWindow->setWindowIcon(QIcon("D:\\tower\\GameIcon.png"));
}

Synodic_Month::~Synodic_Month()
{}

void Synodic_Month::keyPressEvent(QKeyEvent * event)
{
    GameControl::Instance()->keyPressEvent(event);
}

