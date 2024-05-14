#include "Synodic_Month.h"
#include "GameControl.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    Synodic_Month:: MainWindow=new Synodic_Month;
    GameControl::Instance()->GameInit();
    (*(Synodic_Month::MainWindow)).show();
    return a.exec();
    
}
