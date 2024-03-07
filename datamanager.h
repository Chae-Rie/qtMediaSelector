#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QSqlError>


class Datamanager
{
public:
    Datamanager();
    virtual~Datamanager();



    typedef struct BOOK_CONTENT{
        QString isbn;
        QString publisher;
        QString title;
        QString author;
        QString genre;
        QString language;
        QString date;
        QString condition;
    }BOOK_CONTENT;

    typedef struct MAGAZINE_CONTENT{
        QString issn;
        QString publisher;
        QString title;
        QString genre;
        QString language;
        QString publishingRate;
        QString releaseDate;
        QString condtion;
    }MAGAZINE_CONTENT;

    typedef struct OTHERS_CONTENT{
        QString number;
        QString publisher;
        QString title;
        QString description;
        QString condition;
    }OTHERS_CONTENT;

    // struct bookContainer
    // {
    //     bookContainer() {}
    //     QString isbn;
    //     QString publisher;
    //     QString title;
    //     QString author;
    //     QString genre;
    //     QString language;
    //     QString date;
    //     QString condition;
    // } m_BookContainer;

    // struct magazinesContainer
    // {
    //     magazinesContainer() {}
    //     QString issn;
    //     QString publisher;
    //     QString title;
    //     QString genre;
    //     QString language;
    //     QString releaseData;
    //     QString condtion;
    // }m_MagazineContainer;


    // struct othersContainer
    // {
    //     othersContainer() {}
    //     QString number;
    //     QString publisher;
    //     QString title;
    //     QString description;
    //     QString condition;
    // } m_OthersContainer;






};

#endif // DATAMANAGER_H
