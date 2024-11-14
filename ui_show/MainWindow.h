#ifndef QTTEST_MAINWINDOW_H
#define QTTEST_MAINWINDOW_H

#include <QMainWindow>
#include "ui_PreMainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PreMainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent=nullptr);
    ~MainWindow() override;

private:
    Ui::PreMainWindow* ui;

};


#endif //QTTEST_MAINWINDOW_H
