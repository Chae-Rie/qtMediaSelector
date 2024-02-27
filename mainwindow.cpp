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


// Was soll passieren, wenn man in das Menü klickt?

 /*
  * Ich dachte an eine Art Formular was sich öffnet, in dem man dementsprechend sein Buch eintragen kann
  * Infos wie:
  * - ISBM
  * - Titel
  * - Genre
  * - Autor
  * - Publishdate
  * - Verlag
  * - Sprache des Werks
  * - Verfügbarkeit des Artikels -> Ein Button der eine Query auslöst und dann mitteilt ob, der Artikel verliehen ist oder nicht
  * - Erfassungsdatum --> Das ist aber nur wichtig für die AUFNAHME in der Bibliothek und weniger wichtig für den Benutzer
  *
  * sollten dort eingetragen werden können.
  * */







/*
 * Idee:
 * Das wechseln zwischen den Tabs zeigt verschiedene Editcontrols an, die der Benutzer dann dementsprechend
 * mit passendem Inhalt füllen kann. Diese Editcontrols sollen, auch möglichst einfach den Input verarbeiten
 * und auch inhaltliche Richtigkeit überprüfen.
 * Wenn das geschehen ist, soll der Benutzer den Inhalt der Editcontrols mit einem Klick auf
 * "Speichern" in ein generisches Objekt laden können und mit einem Klick auf "Verwerfen" alle
 * bereits gemachten Eingaben aus dem Editcontrol löschen können.
 *
 * Das generische Objekt, soll dann für die Versendung an die Datenbank serialisiert werden.
 * Die Nutzung einer einfach SQLite Datenbank wird den Job schon erledigen.
 *
 * Frage: Wie könnte diese Struktur des generischen Objekts aussehen?
 * Ich könnte auch für den Anfang 3 eindeutig zu definierende Objekte verwenden, die jeweils eine
 * Klasse bekommen.
 * Oder ich verwende eine große Struktur mit Feldern, die im Falle eines Falles Standardwerte mit
 * NULL zugewiesen bekommen.
 * Was ist hier am smartesten?
 *
 */




// Manuelles Schließen der App durch den Benutzer, ohne das macos-typische X zu verwenden.
void MainWindow::on_pushButtonQuit_clicked()
{

}

