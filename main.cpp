#include "mainwindow.h"

#include <QApplication>
#include <QDir>

int main(int argc,char* argv[]){
    QApplication app(argc,argv);
    QDir::setCurrent("/mnt/WinC/Linux_Files/ZJU/Result/Rotor67");
    MainWindow w;
    w.show();
    return app.exec();
}