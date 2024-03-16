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


    // Die wichtigsten Objekte werden sicher als unique_ptr erzeugt
    m_dbmanager = std::make_unique<DbManager>();
    m_queryModel = std::make_unique<QSqlQueryModel>();

    // Zum Start der Anwendung soll die Membervariable so Ihren Startwert bekommen.
    handleSelectedNewFilter();
}

MainWindow::~MainWindow()
{

    delete m_ui;

}

void MainWindow::connectWidgets()
{
    connect(m_ui->pushButtonQuit, SIGNAL (clicked()), this, SLOT (close()));

    connect(m_ui->pushButtonBookSave, SIGNAL(clicked()), this, SLOT(handleButtonBookSaveClick()));

    connect(m_ui->pushButtonBookClearAll, SIGNAL(clicked()), this, SLOT(handleButtonClickBookClear()));

    connect(m_ui->pushButtonMagazineSave, SIGNAL(clicked()), this, SLOT(handleButtonMagazineSaveClick()));

    connect(m_ui->pushButtonMagazineClearAll, SIGNAL(clicked()), this, SLOT(handleButtonClickMagazineClear()));

    connect(m_ui->pushButtonOthersSave, SIGNAL(clicked()), this, SLOT(handleButtonOthersSaveClick()));

    connect(m_ui->pushButtonOthersClearAll, SIGNAL(clicked()), this, SLOT(handleButtonClickOthersClear()));

    connect(m_ui->pushButtonSearchAllMedia, SIGNAL(clicked()), this, SLOT(handleButtonClickSearchAllDatabase()));

    connect(m_ui->pushButtonDeleteMedia, SIGNAL(clicked()), this, SLOT(handleButtonClickDeleteMedia()));

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


    bool success = m_dbmanager->CreateNewRecord(bookContent);

    if (success){
       qDebug() << "Creating a new record for books was successfull and returned true.";
   } else
    {
       qDebug() << "Creating a new record for books was unsuccessfull and returned false.";
   }


   // TODO: Test einbauen -> fake data einführen
}

void MainWindow::handleButtonClickBookClear()
{
    m_ui->lineEditBookTitle->clear();
    m_ui->lineEditBookAuthor->clear();
    m_ui->lineEditISBN->clear();
    m_ui->lineEditBookPublisher->clear();
    m_ui->lineEditBookGenre->clear();
    m_ui->lineEditBookLanguage->clear();
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

    bool success = m_dbmanager->CreateNewRecord(magazineContent);

    if (success){
        qDebug() << "Creating a new record for magazines was successfull and returned true.";
    } else {
        qDebug() << "Creating a new record for magazines was unsuccessfull and returned false.";
    }
}

void MainWindow::handleButtonClickMagazineClear()
{
    m_ui->lineEditISSN->clear();
    m_ui->lineEditMagazineTitle->clear();
    m_ui->lineEditMagazinePublisher->clear();
    m_ui->lineEditMagazineGenre->clear();
    m_ui->lineEditMagazineLanguage->clear();
}

void MainWindow::handleButtonOthersSaveClick(){
    qDebug() << "Trying to save everything out of the others-mask!";

    Datamanager::OTHERS_CONTENT othersContent;

    othersContent.number = m_ui->lineEditOthersNumber->text();
    othersContent.title = m_ui->lineEditOthersTitle->text();
    othersContent.publisher = m_ui->lineEditOthersPublisher->text();
    othersContent.description = m_ui->plainTextEditOthersDescription->toPlainText();
    othersContent.condition = m_ui->comboBoxOthersCondition->currentText();

    bool success = m_dbmanager->CreateNewRecord(othersContent);

    if (success){
        qDebug() << "Creating a new record for others was successfull and returned true.";
    } else {
        qDebug() << "Creating a new record for others was unsuccessfull and returned false.";
    }
}

void MainWindow::handleButtonClickOthersClear()
{
    m_ui->lineEditOthersNumber->clear();
    m_ui->lineEditOthersTitle->clear();
    m_ui->lineEditOthersPublisher->clear();
    m_ui->plainTextEditOthersDescription->clear();
}

void MainWindow::handleButtonClickSearchAllDatabase(){

    if (m_currentKeyword == "Zeitschriften"){
        m_dbmanager->QueryDbEntries(m_queryModel.get(), " magazines;");
    }
    else if (m_currentKeyword == "Bücher"){
        m_dbmanager->QueryDbEntries(m_queryModel.get(), " books;");
    }
    else if (m_currentKeyword == "Andere Medien"){
        m_dbmanager->QueryDbEntries(m_queryModel.get(), " others;");
    } else {
        // unspezifizierter Filter
        qDebug() << "Konnte Filter nicht genau ermitteln!";
        return;
    }

    m_ui->tableView->setModel(m_queryModel.get());
    m_ui->tableView->show();
}

void MainWindow::handleSelectedNewFilter()
{
    m_currentKeyword = GetComboBoxSelection(m_ui->comboBoxFilterKeywords);
}


// Triggers when we click on one of the records with the mouse
void MainWindow::handleRecordSelection(QModelIndex givenIndex)
{

    int rowIndex = givenIndex.row();

    QString recordID = GetIdOfSelection(rowIndex);
    m_dbmanager->SetRecordId(recordID);
    qDebug() << "We just selected the entry with the id: " << recordID;

}

/* Da ein anderes Signal gesendet wird, wenn man mit der Maus, die Row oder Columns anklickt, die die ganze Zeile oder
 * Spalte markieren, braucht es eine eigene Funktion für das Auswählen, einzelner Felder in dem QTableView und für das
 * Auswählen der horizontalen und vertikalen Header
 * TODO: Ich möchte gern je nach dem welche Reihe bzw. welches Item ich auswähle
 * die ID des Eintrags haben
 *
 */
void MainWindow::handleVerticalHeaderSelection(int rowindex)
{
    qDebug() <<  "We just selected the vertical header: " << rowindex;
    QString recordID = GetIdOfSelection(rowindex);
    m_dbmanager->SetRecordId(recordID);
    qDebug() << "I clicked in row" << rowindex <<  " and the ID is: " << recordID;
}

void MainWindow::handleHorizontalHeaderSelection(int columnIndex)
{
    qDebug() <<  "We just selected the horizontal header: " << columnIndex;

    // wenn ich hier was auswählen und löschen würde, dann könnte ich die ganze Datenbank löschen. Das ist Schwachsinn

    // Spaßighalber mal die Statusbar beschreiebn

    m_ui->statusbar->showMessage("Test");
}

void MainWindow::handleButtonClickDeleteMedia()
{
    QString selectedRecordID = m_dbmanager->GetRecordId();
    if (selectedRecordID.isEmpty()){
        m_ui->statusbar->showMessage("Es wurde kein Eintrag ausgewählt!");
        return;
    }


    QString question = "Bist Du sicher, dass Du den Eintrag unter der ID ";
    question.append(selectedRecordID );
    question.append(" wirklich aus der Datenbank löschen möchtest?");

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Medium löschen", question,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked, will procceed with querying database for deletion of entry with ID" << selectedRecordID;

        QString currentTable = GetComboBoxSelection(m_ui->comboBoxFilterKeywords);
        if (currentTable == "Bücher"){
            m_dbmanager->DeleteRecord("books", selectedRecordID);
            handleButtonClickSearchAllDatabase();
        } else if ( currentTable == "Zeitschriften"){
            m_dbmanager->DeleteRecord("magazines", selectedRecordID);
            handleButtonClickSearchAllDatabase();
        }else if (currentTable == "Andere Medien"){
            m_dbmanager->DeleteRecord("others", selectedRecordID);
            handleButtonClickSearchAllDatabase();
        } else {
            qDebug() << "Failed deleting media because we couldn't determine a concrete table.";
            return;
        }
    } else {
        qDebug() << "Yes was *not* clicked";
    }
}

QString MainWindow::GetIdOfSelection(int rowIndex)
{
    QSqlRecord record;
    constexpr int positionOfId = 0; // Denn wir wissen, dass die ID immer an Erster Stelle steht

    record = m_queryModel->record(rowIndex);

    return record.value(positionOfId).toString();
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
