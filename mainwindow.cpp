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

    // Es ist einfacher ein zentrales Modell zu verwalten als mehrere zu erzeugen und zu löschen
    m_queryModel = new QSqlQueryModel;

    // Zum Start der Anwendung soll die Membervariable so Ihren Startwert bekommen.
    handleSelectedNewFilter();
}

MainWindow::~MainWindow()
{
    delete m_queryModel;
    delete m_ui;

}

void MainWindow::connectWidgets()
{
    connect(m_ui->pushButtonQuit, SIGNAL (clicked()), this, SLOT (close()));

    connect(m_ui->pushButtonBookSave, SIGNAL(clicked()), this, SLOT(handleButtonBookSaveClick()));

    connect(m_ui->pushButtonMagazineSave, SIGNAL(clicked()), this, SLOT(handleButtonMagazineSaveClick()));

    connect(m_ui->pushButtonOthersSave, SIGNAL(clicked()), this, SLOT(handleButtonOthersSaveClick()));

    connect(m_ui->pushButtonSearchAllMedia, SIGNAL(clicked()), this, SLOT(handleButtonClickSearchAllDatabase()));

    // --------------------------
    connect(m_ui->comboBoxFilterKeywords, SIGNAL(currentTextChanged(QString)), this, SLOT(handleSelectedNewFilter()));

    // Signal für das Auswählen einzelner Felder in dem QTableView
    connect(m_ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(handleRecordSelection(QModelIndex)));

    // Signal für das Auswählen der Header der vertikal stehenden Header für die einzelnen ZEILEN
    connect( m_ui->tableView->verticalHeader(), SIGNAL(sectionPressed(int)), this, SLOT(handleVerticalHeaderSelection(int)));
    // Signal für das Auswählen der Header der horizontal stehenden Header für die einzelnen SPALTEN
    connect( m_ui->tableView->horizontalHeader(), SIGNAL(sectionPressed(int)), this, SLOT(handleHorizontalHeaderSelection(int)));
}

/* Laut https://stackoverflow.com/questions/75384792/how-may-i-fix-my-error-prone-on-foo-bar-slots
* ist deutlich besser, die Widgets selber durch den code mit den Steuerungselementen
* zu verbinden, da die durch den Designer erzeugten Verbindungen nicht so stabil sind.
* Heißt es würde Sinn ergeben, am Anfang, bei Erstellung des Dialogs, einmal alle Steuerungselemente
* dementsprechend zu verbinden-
*/


// Slot für den Klick auf "Speichern" in der Maske zum Erstellen eines neuen Eintrags von BÜCHERN
// Aber was soll hier passieren?
//
void MainWindow::handleButtonBookSaveClick()
{
    qDebug() << "Trying to save everything out of the books-mask!";


    Datamanager::BOOK_CONTENT bookContent;
    // Ich sollte hier auch irgendwie einen Mechanismus einbauen, der sicherstellt, dass keine leeren Einträge übertragen
    // werden --> Idee: Vielleicht den "Speichern"-Button erst freigeben, wenn alle Daten vernünftig hinterlegt sind?



    // Die verschiedenen Steuerungselemente abfragen
    bookContent.title = m_ui->lineEditBookTitle->text();
    bookContent.author = m_ui->lineEditBookAuthor->text();
    bookContent.isbn = m_ui->lineEditISBN->text();
    bookContent.publisher = m_ui->lineEditBookPublisher->text();
    bookContent.genre = m_ui->lineEditBookGenre->text();
    bookContent.language = m_ui->lineEditBookLanguage->text();
    bookContent.condition = m_ui->comboBoxBooksCondition->currentText();
    bookContent.date = m_ui->dateEditBookReleaseDate->text();


    // Für die Kommunikation mit der Datenbank
    DbManager dbManager;

   bool success = dbManager.CreateNewRecord(bookContent);

    if (success){
       qDebug() << "Creating a new record for books was successfull and returned true.";
   } else
    {
       qDebug() << "Creating a new record for books was unsuccessfull and returned false.";
   }


    // TODO: Test einbauen -> fake data einführen
}

void MainWindow::handleButtonMagazineSaveClick()
{
     qDebug() << "Trying to save everything out of the magazines-mask!";

    Datamanager::MAGAZINE_CONTENT magazineContent;

    magazineContent.issn = m_ui->lineEditISSN->text();
    magazineContent.title = m_ui->lineEditMagazineTitle->text();
    magazineContent.publisher = m_ui->lineEditMagazinePublisher->text();
    magazineContent.genre = m_ui->lineEditMagazineGenre->text();
    magazineContent.language = m_ui->lineEditMagazineLanguage->text();
    magazineContent.publishingRate = m_ui->comboBoxMagazinePublishingRate->currentText();
    magazineContent.condtion = m_ui->comboBoxMagazinesCondition->currentText();
    magazineContent.releaseDate = m_ui->dateEditMagazineReleaseDate->text();

    DbManager dbManager;

    bool success = dbManager.CreateNewRecord(magazineContent);

    if (success){
        qDebug() << "Creating a new record for magazines was successfull and returned true.";
    } else {
        qDebug() << "Creating a new record for magazines was unsuccessfull and returned false.";
    }
}

void MainWindow::handleButtonOthersSaveClick(){
    qDebug() << "Trying to save everything out of the others-mask!";

    Datamanager::OTHERS_CONTENT othersContent;

    othersContent.number = m_ui->lineEditOthersNumber->text();
    othersContent.title = m_ui->lineEditOthersTitle->text();
    othersContent.publisher = m_ui->lineEditOthersPublisher->text();
    othersContent.description = m_ui->plainTextEditOthersDescription->toPlainText();
    othersContent.condition = m_ui->comboBoxOthersCondition->currentText();

    DbManager dbManager;

    bool success = dbManager.CreateNewRecord(othersContent);

    if (success){
        qDebug() << "Creating a new record for others was successfull and returned true.";
    } else {
        qDebug() << "Creating a new record for others was unsuccessfull and returned false.";
    }
}



void MainWindow::handleButtonClickSearchAllDatabase(){

    DbManager dbmanager;

    if (m_currentKeyword == "Zeitschriften"){
        dbmanager.QueryDbEntries(m_queryModel, " magazines;");
    }
    else if (m_currentKeyword == "Bücher"){
        dbmanager.QueryDbEntries(m_queryModel, " books;");
    }
    else if (m_currentKeyword == "Andere Medien"){
        dbmanager.QueryDbEntries(m_queryModel, " others;");
    } else {
        // unspezifizierter Filter
        qDebug() << "Konnte Filter nicht genau ermitteln!";
        return;
    }

    m_ui->tableView->setModel(m_queryModel);
    m_ui->tableView->show();
}

void MainWindow::handleSelectedNewFilter()
{
    m_currentKeyword = GetComboBoxSelection(m_ui->comboBoxFilterKeywords);
}


// Triggers when we click on one of the records with the mouse
void MainWindow::handleRecordSelection(QModelIndex givenIndex)
{

    int selectedColumn = givenIndex.column();
    int selectedRow = givenIndex.row();

    QSqlRecord record;
    record =  m_queryModel->record(selectedRow);

    // Get the id for the record, so we can query it for deletion -> id is always 0
    QString recordId = record.value(0).toString();
    qDebug() << "We just selected the entry with the id: " << recordId;
}

/* Da ein anderes Signal gesendet wird, wenn man mit der Maus, die Row oder Columns anklickt, die die ganze Zeile oder
 * Spalte markieren, braucht es eine eigene Funktion für das Auswählen, einzelner Felder in dem QTableView und für das
 * Auswählen der horizontalen und vertikalen Header
 *
 *
 */
void MainWindow::handleVerticalHeaderSelection(int rowindex)
{
    qDebug() <<  "We just selected the vertical header: " << rowindex;
}

void MainWindow::handleHorizontalHeaderSelection(int columnIndex)
{
    qDebug() <<  "We just selected the horizontal header: " << columnIndex;
}



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
