#include "Displayer.h"
Displayer*  Displayer::instance = nullptr;
Displayer::Displayer()
{
    centralwidget = nullptr;
    lcdNumber = nullptr;
    groupBox = nullptr;
    label = nullptr;
    label_2 = nullptr;
    label_3 = nullptr;
    label_4 = nullptr;
    label_5 = nullptr;
    groupBox_2 = nullptr;
    groupBox_3 = nullptr;
    groupBox_4 = nullptr;
    groupBox_5 = nullptr;
    groupBox_6 = nullptr;
    progressBar = nullptr;
    progressBar_3 = nullptr;
}
void Displayer::Init(MyScene* TargetScene)
{
    centralwidget = new QWidget;
    centralwidget->setObjectName("centralwidget");
    groupBox = new QGroupBox(centralwidget);
    groupBox->setObjectName("groupBox");
    groupBox->setGeometry(QRect(190, 10, 151, 71));
    label = new QLabel(groupBox);
    label->setObjectName("label");
    label->setGeometry(QRect(10, 23, 41, 41));
    label->setPixmap(QPixmap(QString::fromUtf8("../../tower/coin.png")));
    label_2 = new QLabel(groupBox);
    label_2->setObjectName("label_2");
    label_2->setGeometry(QRect(60, 20, 91, 51));
    label_2->setAlignment(Qt::AlignCenter);
    groupBox_2 = new QGroupBox(centralwidget);
    groupBox_2->setObjectName("groupBox_2");
    groupBox_2->setGeometry(QRect(350, 10, 101, 71));
    label_3 = new QLabel(groupBox_2);
    label_3->setObjectName("label_3");
    label_3->setGeometry(QRect(10, 20, 81, 51));
    label_3->setAlignment(Qt::AlignCenter);
    groupBox_3 = new QGroupBox(centralwidget);
    groupBox_3->setObjectName("groupBox_3");
    groupBox_3->setGeometry(QRect(30, 10, 151, 71));
    lcdNumber = new QLCDNumber(groupBox_3);
    lcdNumber->setObjectName("lcdNumber");
    lcdNumber->setGeometry(QRect(0, 20, 151, 51));
    groupBox_4 = new QGroupBox(centralwidget);
    groupBox_4->setObjectName("groupBox_4");
    groupBox_4->setGeometry(QRect(700, 10, 261, 71));
    progressBar = new QProgressBar(groupBox_4);
    progressBar->setObjectName("progressBar");
    progressBar->setGeometry(QRect(10, 30, 241, 31));
    progressBar->setValue(24);

    groupBox_5 = new QGroupBox(centralwidget);
    groupBox_5->setObjectName("groupBox_5");
    groupBox_5->setGeometry(QRect(460, 10, 111, 71));
    label_4 = new QLabel(groupBox_5);
    label_4->setObjectName("label_4");
    label_4->setGeometry(QRect(10, 20, 91, 51));
    label_4->setAlignment(Qt::AlignCenter);
    groupBox_6 = new QGroupBox(centralwidget);
    groupBox_6->setObjectName("groupBox_6");
    groupBox_6->setGeometry(QRect(580, 10, 111, 71));
    label_5 = new QLabel(groupBox_6);
    label_5->setObjectName("label_5");
    label_5->setGeometry(QRect(10, 23, 91, 41));
    label_5->setAlignment(Qt::AlignCenter);
    
    
    this->setWidget(centralwidget);
    TargetScene->addItem(this);
    label_2->setStyleSheet("color: white;");
    label_3->setStyleSheet("color: white;");
    label_4->setStyleSheet("color: white;");
    label_5->setStyleSheet("color: white;");
    groupBox->setStyleSheet("color: white;");
    groupBox_2->setStyleSheet("color: white;");
    groupBox_3->setStyleSheet("color: white;");
    groupBox_4->setStyleSheet("color: white;");
    groupBox_5->setStyleSheet("color: white;");
    groupBox_6->setStyleSheet("color: white;");
    QFont font;
    font.setPointSize(35);
    label_2->setFont(font);
    label_3->setFont(font);
    label_4->setFont(font);
    label_5->setFont(font);
    centralwidget->setStyleSheet("background-color: transparent;");
    groupBox->setTitle(QCoreApplication::translate("MainWindow", "Coin", nullptr));
    label->setText(QString());
    label_2->setText(QCoreApplication::translate("MainWindow", "1", "1"));
    groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Round", nullptr));
    label_3->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
    
    groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Time", nullptr));
    groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "HP", nullptr));
    groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Level", nullptr));
    label_4->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
    groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "XP", nullptr));
    label_5->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
    this->moveBy(180, 0);
}

void Displayer::showTime(int t)
{
    QTime showtime(0, 0, 0);//初始时间
    showtime = showtime.addMSecs(t);//增加tms
    showstr = showtime.toString("hh:mm:ss");//转换为string类型
    lcdNumber->display(showstr); //显示
}

void Displayer::showHP(int t)
{
    progressBar->setValue(t);
}

void Displayer::showRound(int t)
{
    QString str = QString::number(t);
    if (t == -1)
    {
        str = "END";
        QFont f2;
        f2.setPointSize(25);
        label_3->setFont(f2);
    }
    label_3->setText(str);
}

void Displayer::showCoin(int t)
{
    QString str = QString::number(t);
    label_2->setText(str);
}

void Displayer::showLevel(int xp, int le)
{
    QString str = QString::number(le);
    QString str2 = QString::number(xp);
    if (le == 9)
    {
        str2 = "MAX";
        QFont f2;
        f2.setPointSize(25);
        label_5->setFont(f2);
    }
    label_4->setText(str);
    label_5->setText(str2);
}

void Displayer::showBossHP()
{
    progressBar_3 = new QProgressBar(centralwidget);
    progressBar_3->setObjectName("progressBar_3");
    progressBar_3->setGeometry(QRect(30, 90, 921, 23));
    progressBar_3->setValue(24);
}

void Displayer::showBossHP(int t)
{
    progressBar->setValue(t);
}

