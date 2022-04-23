#include "test.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QPicture>
#include <QPainter>

Test::Test(QWidget* parent) {
    //"D:/made_IN/Qt_Dev/playia/no_cover.png"
    QPicture picture;
    picture.load("D:/made_IN/Qt_Dev/playia/no_cover.png");
    QLabel coverTest;
    coverTest.setPicture(picture);
    QHBoxLayout* testBox = new QHBoxLayout();
    testBox->addWidget(&coverTest);
    //setLayout(testBox);
}
