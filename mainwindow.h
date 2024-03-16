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
#include <QMessageBox>

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



private slots:
    void handleButtonBookSaveClick();
    void handleButtonClickBookClear();
    void handleButtonMagazineSaveClick();
    void handleButtonClickMagazineClear();
    void handleButtonOthersSaveClick();
    void handleButtonClickOthersClear();
    void handleButtonClickSearchAllDatabase();
    void handleSelectedNewFilter();
    void handleRecordSelection(QModelIndex givenIndex);
    void handleVerticalHeaderSelection(int rowindex);
    void handleHorizontalHeaderSelection(int columnIndex);
    void handleButtonClickDeleteMedia();


private:
    inline QString GetComboBoxSelection(QComboBox* comboBox){return comboBox->currentText();};
    void connectWidgets();
    QString GetIdOfSelection(int rowIndex);


    Ui::MainWindow *m_ui;
    QString m_currentKeyword;
    //QString m_currentlySelectedRecordID; // Ermittelte ID aus der "Löschen"-Maske -> Angeklickter Eintrag
    //QSqlQueryModel* m_queryModel;
    std::unique_ptr<DbManager> m_dbmanager;
    std::unique_ptr<QSqlQueryModel> m_queryModel;

};
#endif // MAINWINDOW_H
