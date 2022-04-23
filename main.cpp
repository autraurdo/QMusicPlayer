#include "mainwindow.h"
#include <Player.h>
#include <QApplication>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;

    Player w;

    //Test w;
    w.resize(500, 100);
    w.show();

    return a.exec();
}
