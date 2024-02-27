#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QtSql/QSqlQueryModel> // Für die Abfrage von Inhalten aus der DB

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
    ~MainWindow();

private slots:


    void on_pushButtonQuit_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
