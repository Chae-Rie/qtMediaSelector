#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datamanager.h"

#include <QMainWindow>
#include <QStatusBar>
#include <QDebug>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void connectWidgets();

private slots:
    void handleButtonBookSaveClick();
    void handleButtonMagazineSaveClick();
private:
    Ui::MainWindow *m_ui;
    Datamanager m_Datamanager;


};
#endif // MAINWINDOW_H
