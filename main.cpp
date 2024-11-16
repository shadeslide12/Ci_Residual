#include "mainwindow.h"

#include <QApplication>
#include <QDir>

int main(int argc,char* argv[]){
    QApplication app(argc,argv);
    QDir::setCurrent("/home/shadeslide/ZJUI_Test/Rotor67");
    MainWindow w;
    w.show();
    return app.exec();
}