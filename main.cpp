#include "GameDemo1.h"
#include "GameControl.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    GameDemo1:: MainWindow=new GameDemo1;
    GameControl::Instance()->GameInit();
    (*(GameDemo1::MainWindow)).show();
    return a.exec();
    
}
