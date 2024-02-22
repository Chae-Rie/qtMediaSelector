#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Ich fände es auch toll, wenn es die Möglichkeit gäbe, eine Art Statusbar einzustellen
     * am Besten am Grund des Mainwindows -> Dann sollte ich aber in einem Fenster bleiben.
     * In der Statusbar, kann ich den Benutzer dann relativ gut über fehlgeschlagene
     * Operationen hinweisen
     * */

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCreatingMedia_triggered()
{
// Was soll passieren, wenn man in das Menü klickt?

 /*
  * Ich dachte an eine Art Formular was sich öffnet, in dem man dementsprechend sein Buch eintragen kann
  * Infos wie:
  * - ISBM
  * - Titel
  * - Genre
  * - Autor
  * - Publishdate
  *
  * sollten dort eingetragen werden können.
  * */
}



