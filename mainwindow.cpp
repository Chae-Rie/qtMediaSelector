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

    connect(m_ui->pushButtonLogout, SIGNAL(clicked()), this, SLOT(handleButtonClickLogout()));

    // --------------------------
    connect(m_ui->comboBoxFilterKeywords, SIGNAL(currentTextChanged(QString)), this, SLOT(handleSelectedNewFilter()));

    // Signal für das Auswählen einzelner Felder in dem QTableView für die Medien
    connect(m_ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(handleRecordSelection(QModelIndex)));

    // Signal für das Auswählen der Header der vertikal stehenden Header für die einzelnen ZEILEN
    connect( m_ui->tableView->verticalHeader(), SIGNAL(sectionPressed(int)), this, SLOT(handleVerticalHeaderSelection(int)));

    // Signal für das Auswählen der Header der horizontal stehenden Header für die einzelnen SPALTEN
    connect( m_ui->tableView->horizontalHeader(), SIGNAL(sectionPressed(int)), this, SLOT(handleHorizontalHeaderSelection(int)));

    // -------------------------- Für die Darstellung von Graphen

    connect(m_ui->tableViewUsers, SIGNAL(clicked(QModelIndex)), this, SLOT(handleRecordSelection(QModelIndex))); // Is das ok?

    connect(m_ui->tableViewUsers->verticalHeader(), SIGNAL(sectionPressed(int)), this, SLOT(handleVerticalHeaderSelection(int)));

    connect(m_ui->tableViewUsers->horizontalHeader(), SIGNAL(sectionPressed(int)), this, SLOT(handleHorizontalHeaderSelection(int)));

    connect(m_ui->pushButtonSearchUser, SIGNAL(clicked()), this, SLOT(handleButtonClickSearchUsers()));

    connect(m_ui->pushButtonDeleteUser, SIGNAL(clicked()), this, SLOT(handleButtonClickDeleteUsers()));
    /*
     * Ein Klick auf die Tabbar "Stats/History" soll ein kleines Fenster erzeugen welches aus einem Graphen besteht
    */

    connect(m_ui->tabWidgetStats, SIGNAL(tabBarClicked(int)), this, SLOT(handleClickOnTabbarStats(int)));
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

void MainWindow::handleClickOnTabbarStats(int)
{
    // // Das MainWindow-Objekt ist bereits erstellt worden, es muss demnach nur aktualisiert werden

    // // Hartcodierte Daten für den Graphen
    // QList<QPair<QString, int>> bookData;
    // bookData << qMakePair("Fiktion", 20)
    //          << qMakePair("Non-Fiktion", 15)
    //          << qMakePair("Fantasy", 10)
    //          << qMakePair("Thriller", 8);

    // // Erstellung eines Balkendiagramms
    // QBarSeries *series = new QBarSeries();
    // for (const auto &data : bookData) {
    //     QBarSet *set = new QBarSet(data.first);
    //     *set << data.second;
    //     series->append(set);
    // }

    // // Erstellung des Diagramms
    // QChart *chart = new QChart();
    // chart->addSeries(series);
    // chart->setTitle("Anzahl der ausgeliehenen Bücher nach Genre");
    // chart->setAnimationOptions(QChart::SeriesAnimations);

    // // Kategorienachse
    // QBarCategoryAxis *axisX = new QBarCategoryAxis();
    // QStringList categories;
    // for (const auto &data : bookData) {
    //     categories << data.first;
    // }
    // axisX->append(categories);
    // chart->addAxis(axisX, Qt::AlignBottom);
    // series->attachAxis(axisX);

    // // Wertachse
    // QValueAxis *axisY = new QValueAxis();
    // chart->addAxis(axisY, Qt::AlignLeft);
    // series->attachAxis(axisY);

    // QGraphicsScene *scene = new QGraphicsScene();
    // scene->addItem(chart);
    // m_ui->graphicsView->setScene(scene);

}

void MainWindow::handleButtonClickLogout()
{

    if (m_credentialDialog.get()->exec() == QDialog::Accepted) {
        // Anmeldeinformationen sind korrekt
        // Schließen des AnmeldeDialogs -> Öffnen des MainDialogs

        return;
    }
}

void MainWindow::handleButtonClickSearchUsers()
{
    m_dbmanager->QueryDbEntries(m_queryModel.get(), " users;");

    m_ui->tableViewUsers->setModel(m_queryModel.get());
    m_ui->tableViewUsers->show();
}

void MainWindow::handleButtonClickDeleteUsers()
{
    QString selectedRecordID = m_dbmanager->GetRecordId();
    m_dbmanager->DeleteRecord("users", selectedRecordID);
    // Aktualisiert das Tableview direkt
    handleButtonClickSearchUsers();
}

QString MainWindow::GetIdOfSelection(int rowIndex)
{
    QSqlRecord record;
    constexpr int positionOfId = 0; // Denn wir wissen, dass die ID immer an Erster Stelle steht

    record = m_queryModel->record(rowIndex);

    return record.value(positionOfId).toString();
}

void MainWindow::Login(DbManager& refDbmanager)
{
    m_credentialDialog = std::make_unique<CredentialDialog>(refDbmanager);
    //CredentialDialog credentialDialog(refDbmanager);

    if (m_credentialDialog.get()->exec() == QDialog::Accepted) {
        // Anmeldeinformationen sind korrekt
        // Schließen des AnmeldeDialogs -> Öffnen des MainDialogs

        // Prüfung nach Rolle und dann die Benutzerverwaltung darstellen

        return;
    }
}
