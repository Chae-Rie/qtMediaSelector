#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);





    /* Der Übersichtlichkeithalber calle ich im Konstruktor eine Funktion, die die Steuerungselemente mit den
    * jeweiligen Signalen und Slots verbindet.
    *
    */
    connectWidgets();






}

MainWindow::~MainWindow()
{
    delete m_ui;
}

/* Laut https://stackoverflow.com/questions/75384792/how-may-i-fix-my-error-prone-on-foo-bar-slots
* ist deutlich besser, die Widgets selber durch den code mit den Steuerungselementen
* zu verbinden, da die durch den Designer erzeugten Verbindungen nicht so stabil sind.
* Heißt es würde Sinn ergeben, am Anfang, bei Erstellung des Dialogs, einmal alle Steuerungselemente
* dementsprechend zu verbinden-
*/
void MainWindow::connectWidgets()
{

    // close() ist ein bereits vordefinierter slot, also brauche ich diesen nur hinter SLOT zu referenzieren
    // -> Da er mit auf das clicked SIGNAL mit dem pushButtonQuit-Objekt verbunden ist, brauche ich nun nichts weiter machen
    connect(m_ui->pushButtonQuit, SIGNAL (clicked()), this, SLOT (close()));

    connect(m_ui->pushButtonBookSave, SIGNAL(clicked()), this, SLOT(handleButtonBookSaveClick()));

    connect(m_ui->pushButtonMagazineSave, SIGNAL(released()), this, SLOT(handleButtonMagazineSaveClick()));

}


// Slot für den Klick auf "Speichern" in der Maske zum Erstellen eines neuen Eintrags von BÜCHERN
void MainWindow::handleButtonBookSaveClick()
{
    qDebug() << "Trying to save everything out of the books-mask!";

    m_Datamanager.m_BookContainer.title = m_ui->lineEditBookTitle->text();
    m_Datamanager.m_BookContainer.author = m_ui->lineEditBookAuthor->text();
    m_Datamanager.m_BookContainer.isbn = m_ui->lineEditISBN->text();
    m_Datamanager.m_BookContainer.publisher = m_ui->lineEditBookPublisher->text();
    m_Datamanager.m_BookContainer.genre = m_ui->lineEditBookGenre->text();
    m_Datamanager.m_BookContainer.language = m_ui->lineEditBookLanguage->text();
    m_Datamanager.m_BookContainer.condition = m_ui->comboBoxBooksCondition->currentText();
    m_Datamanager.m_BookContainer.date = m_ui->dateEditBookReleaseDate->text();

    // TODO: Test einbauen -> fake data einführen
}

void MainWindow::handleButtonMagazineSaveClick()
{
     qDebug() << "Trying to save everything out of the magazines-mask!";
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



/*
 * Gibt es eine galante Möglichkeit, die bei den anderen Masken auch zu machen?
 *
*/

/* Ich fände es auch toll, wenn es die Möglichkeit gäbe, eine Art Statusbar einzustellen
     * am Besten am Grund des Mainwindows -> Dann sollte ich aber in einem Fenster bleiben.
     * In der Statusbar, kann ich den Benutzer dann relativ gut über fehlgeschlagene
     * Operationen hinweisen
     * */
