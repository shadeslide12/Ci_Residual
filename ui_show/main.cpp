#include <QApplication>
#include "MainWindow.h"

int main(int argc,char* argv[] ){
    QApplication window(argc,argv);
    MainWindow M;
    M.show();

    return  window.exec() ;
}