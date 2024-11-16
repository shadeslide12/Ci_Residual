#include "mainwindow.h"

#include <QApplication>
#include <QDir>

int main(int argc,char* argv[]){
    QApplication app(argc,argv);
    QDir::setCurrent("$HOME/ZJUI_TEST/Rotor67");
    MainWindow w;
    w.show();
    return app.exec();
}