#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datamanager.h"
#include "dbmanager.h"

#include <QMainWindow>
#include <QStatusBar>
#include <QDebug>
#include <QPushButton>
#include <QComboBox>
#include <QModelIndex>
#include <QtSql/QSqlQueryModel>
#include <QSqlRecord>

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
    void handleButtonOthersSaveClick();
    void handleButtonClickSearchAllDatabase();
    void handleSelectedNewFilter();
    void handleRecordSelection(QModelIndex givenIndex);
    void handleVerticalHeaderSelection(int rowindex);
    void handleHorizontalHeaderSelection(int columnIndex);


private:
    inline QString GetComboBoxSelection(QComboBox* comboBox){return comboBox->currentText();};
    Ui::MainWindow *m_ui;
    QString m_currentKeyword;
    QSqlQueryModel* m_queryModel;


};
#endif // MAINWINDOW_H
