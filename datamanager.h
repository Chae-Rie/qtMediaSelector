#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>

class Datamanager
{
public:
    Datamanager();
    virtual~Datamanager();

    struct bookContainer
    {
        bookContainer() {}
        QString isbn;
        QString publisher;
        QString title;
        QString author;
        QString genre;
        QString language;
        QString date;
        QString condition;
    } m_BookContainer;

    struct magazinesContainer
    {
        magazinesContainer() {}
        QString issn;
        QString publisher;
        QString title;
        QString genre;
        QString language;
        QString releaseData;
        QString condtion;
    }m_MagazineContainer;


    struct othersContainer
    {
        othersContainer() {}
        QString number;
        QString publisher;
        QString title;
        QString description;
        QString condition;

    };
};

#endif // DATAMANAGER_H
