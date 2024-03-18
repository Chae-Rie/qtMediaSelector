#include "dbmanager.h"

DbManager::DbManager() {

}

DbManager::~DbManager(){}


// Should connect client to local sqlite-database
bool DbManager::Connect()
{
    //QString currentDir = QCoreApplication::applicationDirPath();
    // QString dbPath = "/Users/yoocherry/dev/local_projects/mediaSelector/database/mediaselector.db";


    //QString dbPath = "../" + currentDir + "/testdb/mediaselector.db";
    // Spezifieren welche Datenbanktreiber verwendet werden sollen
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // Wie heißt die Datenbank-Datei und wo liegt sie?
    //db.setDatabaseName(dbPath);
    db.setDatabaseName("mediaselector.db");

    // Überprüfen, ob die Verbindung erfolgreich hergestellt wurde
    if (!db.open()) {
        qDebug() << "Database connection failed!";
    } else {
        qDebug() << "Connected with database under '" << db.databaseName() << "'";
    }
    // Was für Routinen könnte ich hier ausführen? Was ist hier sinnvoll?
    return false;
}

// Should disconnect client from local sqlite-database
bool DbManager::Disconnect()
{
    // Was für Routinen könnte ich hier ausführen? Was ist hier sinnvoll?
    return false;
}




// TODO: Ich möchte, dass es auch eine Tabelle mit entry_created_on gibt -> Vorher muss ich das aktuelle Datum, zur Laufzeit erstellen
// Dieses möchte direkt bei dem Funktionscall herausfinden und dann übergeben

bool DbManager::CreateMainTables()
{
    // Da es nur eine Datenbank gibt, findet er automatisch die richtige
    QSqlDatabase db = QSqlDatabase::database();
    bool isOpened = db.isOpen();

    if (isOpened){

        QString bookTable =
            "CREATE TABLE IF NOT EXISTS books ("
            "id INTEGER PRIMARY KEY,"
            "isbn TEXT,"
            "title TEXT,"
            "publisher TEXT,"
            "author TEXT,"
            "genre TEXT,"
            "language TEXT,"
            "release_date DATE,"
            "condition TEXT,"
            "created_on DATE"
            ");";
        QString magazineTable =
            "CREATE TABLE IF NOT EXISTS magazines ("
            "id INTEGER PRIMARY KEY,"
            "issn TEXT,"
            "title TEXT,"
            "publisher TEXT,"
            "genre TEXT,"
            "language TEXT,"
            "publishing_rate TEXT,"
            "release_date DATE,"
            "condition TEXT,"
            "created_on DATE"
            ");";
        QString othersTable =
            "CREATE TABLE IF NOT EXISTS others ("
            "id INTEGER PRIMARY KEY,"
            "number TEXT,"
            "title TEXT,"
            "publisher TEXT,"
            "detailed_description TEXT,"
            "condition TEXT,"
            "created_on DATE"
            ");";

        QString usersTable =
            "CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY,"
            "name TEXT,"
            "lastname TEXT,"
            "email TEXT,"
            "password TEXT,"
            "created_on DATE,"
            "role TEXT"
            ");";

        QString borrowedMediaTable =
            "CREATE TABLE IF NOT EXISTS borrowedMedia ("
            "id INTEGER PRIMARY KEY,"
            "user_id INTEGER,"
            "media_id INTEGER,"
            "borrowed_on DATE,"
            "borrowed_until DATE"
            ");";

        QSqlQuery query(db);
        bool success = (
            query.exec(bookTable) && query.exec(magazineTable) && query.exec(othersTable) && query.exec(usersTable) && query.exec(borrowedMediaTable)
                        );

        if (!success){
            qDebug() << "Query failed with" << query.lastError().text();
        } else {
            qDebug() << "Database creation was successfully";
            return true;
        }
    } else {
        // try to open it and try again
        return false;
    }
    return false;
}


// Drucke alles was sich in der books Tabelle befindet
bool DbManager::PrintAllBooks(){
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    if (db.isOpen()){
        int i = 0;
        query.exec("SELECT * from books");
        while(query.next()){
            QString isbn = query.value("isbn").toString();
            QString publisher = query.value("publisher").toString();
            QString title = query.value("title").toString();
            QString author = query.value("author").toString();
            QString genre = query.value("genre").toString();
            QString language = query.value("language").toString();
            QString date = query.value("release_date").toString();
            QString condition = query.value("condition").toString();
            QString creation_date = query.value("created_on").toString();


            qDebug() << "Processing query-count: " << i << "with following values:"
                     << "isbn:" << isbn
                     << "publisher:" << publisher
                     << "title:" << title
                     << "author:" << author
                     << "genre:" << genre
                     << "language:" << language
                     << "release_date:" << date
                     << "condition" << condition
                     << "created on:" << creation_date;
            i ++; // Um anzugeben, wieviele Queries hier abgefragt werden
        }

    } else {
        qDebug() << "PrintAllBooks() failed with" << query.lastError().text();
    }
}



/*
 * Wichtige Info: Wenn ich mit bindValue etwas an die Query anhänge, kann ich einfach query.exec() ohne übergebenes Argument callen,
 * da der QueryString bereits mit dem QueryObjekt verbunden ist.
*/
bool DbManager::CreateNewRecord(Datamanager::BOOK_CONTENT newContent)
{

    QSqlDatabase db = QSqlDatabase::database();

    QSqlQuery query(db);

    if (db.isOpen()){
        QString currentDate = HelperFunction::GetCurrentTime();

        QString basicQuery = "INSERT INTO books (isbn, title, publisher, author, genre, language, release_date, condition, created_on) "
                                   "VALUES(:isbn, :title, :publisher, :author, :genre, :language, :release_date, :condition, :current_date);";

        query.prepare(basicQuery);

        // Übertrag in die Query
        query.bindValue(":isbn", newContent.isbn);
        query.bindValue(":title", newContent.title);
        query.bindValue(":publisher", newContent.publisher);
        query.bindValue(":author", newContent.author);
        query.bindValue(":genre", newContent.genre);
        query.bindValue(":language", newContent.language);
        query.bindValue(":release_date", newContent.date);
        query.bindValue(":condition", newContent.condition);
        query.bindValue(":current_date", currentDate);

        if(!(query.exec())){
            qDebug() << "Querying for new book record failed!"<< query.lastError().text();
            return false;
        } else {
            qDebug() << "Created a new book record!";
            return true;
        }
    } else {
        qDebug() << "CreateNewRecord() failed getting a valid connection!"<< query.lastError().text();
        return false;
    }
}

bool DbManager::CreateNewRecord(Datamanager::MAGAZINE_CONTENT newContent)
{

    QSqlDatabase db = QSqlDatabase::database();

    QSqlQuery query(db);

    if (db.isOpen()){
        QString currentDate = HelperFunction::GetCurrentTime();


        // QString magazineTable =
        //     "CREATE TABLE IF NOT EXISTS magazines ("
        //     "id INTEGER PRIMARY KEY,"
        //     "issn TEXT,"
        //     "title TEXT,"
        //     "publisher TEXT,"
        //     "genre TEXT,"
        //     "language TEXT,"
        //     "publishing_rate TEXT,"
        //     "release_date DATE,"
        //     "condition TEXT"
        //     "created_on DATE"
        //     ");";

        QString basicQuery = "INSERT INTO magazines (issn, title, publisher, genre, language, publishing_rate, release_date, condition, created_on) "
                                   "VALUES(:issn, :title, :publisher, :genre, :language, :publishing_rate, :release_date, :condition, :current_date);";

        if (!(query.prepare(basicQuery))){
            qDebug() << "prepare already failed (magazines)" << query.lastError().text();
            return false;
        }


        // Übertrag in die Query
        query.bindValue(":issn", newContent.issn);
        query.bindValue(":title", newContent.title);
        query.bindValue(":publisher", newContent.publisher);
        query.bindValue(":genre", newContent.genre);
        query.bindValue(":language", newContent.language);
        query.bindValue(":publishing_rate", newContent.publishingRate);
        query.bindValue(":release_date", newContent.releaseDate);
        query.bindValue(":condition", newContent.condtion);
        query.bindValue(":current_date", currentDate);

        if(!(query.exec())){
            qDebug() << "Querying for new magazine record failed!" << query.lastError().text();
            return false;
        } else {
            qDebug() << "Created a new magazine record!";
            return true;
        }
    } else {
        qDebug() << "CreateNewRecord() failed getting a valid connection!"<< query.lastError().text();
        return false;
    }
}
bool DbManager::CreateNewRecord(Datamanager::OTHERS_CONTENT newContent)
{

    QSqlDatabase db = QSqlDatabase::database();

    QSqlQuery query(db);



    // QString othersTable =
    //     "CREATE TABLE IF NOT EXISTS others ("
    //     "id INTEGER PRIMARY KEY,"
    //     "number TEXT,"
    //     "title TEXT,"
    //     "publisher TEXT,"
    //     "detailed_description TEXT,"
    //     "condition TEXT"
    //     "created_on DATE"
    //     ");";
    if (db.isOpen()){
        QString currentDate = HelperFunction::GetCurrentTime();

        QString basicQuery = "INSERT INTO others (number, title, publisher, detailed_description, condition, created_on) "
                                   "VALUES(:number, :title, :publisher, :detailed_description, :condition, :current_date);";

        if (!(query.prepare(basicQuery))){
            qDebug() << "prepare already failed (others)" << query.lastError().text();
            return false;
        }

        // Übertrag in die Query
        query.bindValue(":number", newContent.number);
        query.bindValue(":title", newContent.title);
        query.bindValue(":publisher", newContent.publisher);
        query.bindValue(":detailed_description", newContent.description);
        query.bindValue(":condition", newContent.condition);
        query.bindValue(":current_date", currentDate);


        if(!(query.exec())){
            qDebug() << "Querying for new otherMedia record failed!" << query.lastError().text();
            return false;
        } else {
            qDebug() << "Created a new otherMedia record!";
            return true;
        }
    } else {
        qDebug() << "CreateNewRecord() failed getting a valid connection!"<< query.lastError().text();
        return false;
    }
}

bool DbManager::CreateNewRecord(Datamanager::USER_CREDENTIALS newContent)
{
    QSqlDatabase db = QSqlDatabase::database();

    QSqlQuery query(db);

    if (db.isOpen()){
        QString currentDate = HelperFunction::GetCurrentTime();

        QString basicQuery = "INSERT INTO users (name, lastname, email, password, created_on, role) "
                             "VALUES(:name, :lastname, :email, :password, :current_date, :role);";

        if (!(query.prepare(basicQuery))){
            qDebug() << "prepare already failed (others)" << query.lastError().text();
            return false;
        }


        query.bindValue(":name", newContent.name);
        query.bindValue(":lastname", newContent.lastname);
        query.bindValue(":email", newContent.email);
        query.bindValue(":password", newContent.password);
        query.bindValue(":current_date", currentDate);
        query.bindValue(":role", newContent.role);

        if(!(query.exec())){
            qDebug() << "Querying for new usercredentials record failed!" << query.lastError().text();
            return false;
        } else {
            qDebug() << "Created a new usercredentials record!";
            return true;
        }
    } else {
        qDebug() << "CreateNewRecord() failed getting a valid connection!"<< query.lastError().text();
        return false;
    }
}

// Scheinbar gibts kein Äquivalent zu bindValue bei QSqlQueryModel also verwaende ich die einfache QSqlQuery-API
// wenn ich QSqlQueryModel auf Krampf bräuchte, könnte ich das dann auch mit dem QSqlQuery-Objekt verbinden.
bool DbManager::DeleteRecord( QString table, QString recordID)
{
    QString basicQuery = "DELETE FROM " + table + " WHERE id = " + recordID + ";";
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    if (db.open()){
        if (!(query.exec(basicQuery))){
            qDebug() << "Querying the database for deletion failed with: " << query.lastError().text();
            return false;
        } else{
            return true;
        }

    } else {
        qDebug() << "DeleteRecord() failed getting a valid connection!"<< query.lastError().text();
        return false;
    }
}

bool DbManager::CheckUserCredentials(Datamanager::USER_CREDENTIALS givenCredentials)
{

    // Formulierung der SQL-Abfrage
    QString basicQuery = "SELECT COUNT(*) FROM users WHERE name = :name AND lastname = :lastname AND email = :email AND password = :password AND role = :role";
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    if (db.open()){

        if (!(query.prepare(basicQuery))){
            qDebug() << "prepare already failed (others)" << query.lastError().text();
            return false;
        }

        // Binden der Parameter an die Abfrage
        query.bindValue(":name", givenCredentials.name);
        query.bindValue(":lastname", givenCredentials.lastname);
        query.bindValue(":email", givenCredentials.email);
        query.bindValue(":password", givenCredentials.password);
        query.bindValue(":role", givenCredentials.role);

        // Ausführen der Abfrage
        if (query.exec()) {
            query.first(); // Gehe zum ersten Datensatz
            int count = query.value(0).toInt(); // Wert des ersten Feldes abrufen (Anzahl der übereinstimmenden Datensätze)

            if (count > 0) {
                // Benutzerdaten stimmen überein, der Benutzer kann sich anmelden
                qDebug() << "Found exact user, login allowed!";
                return true;
            } else {
                // Benutzerdaten stimmen nicht überein, der Benutzer kann sich nicht anmelden
                qDebug() << "Couldn't find user, login not allowed!";
                return false;
            }
    } else {
        qDebug() << "CheckUserCredentials() failed getting a valid connection!" << query.lastError().text();
        return false;
        }
    }
}

bool DbManager::QueryDbEntries(QSqlQueryModel* sqlModel, QString tableWithDelimiter)
{
    // Formuliere die Query
    QString basicQuery = "SELECT * from";

    basicQuery.append(tableWithDelimiter);

    QSqlDatabase db = QSqlDatabase::database();


    if (db.open()){

        sqlModel->setQuery(basicQuery);


        //int rowCount = sqlModel.rowCount();
        // Wie komme ich an die columns, der Query
        // QString columnname = sqlModel->headerData(3, Qt::Horizontal).toString();
        return true;
    } else {
        qDebug() << "QueryDbEntries() failed getting a valid connection!"<< sqlModel->lastError().text();
    }
}



