#ifndef HELPERFUNCTION_H
#define HELPERFUNCTION_H

#include <QString>
#include <QDateTime>
#include <QCryptographicHash>

/*
 * Diese Klasse soll nur eine Ansammlung von statischen Hilfsfunktionen darstellen
 *
*/
class HelperFunction
{
public:

    static QString GetCurrentTime();
    static QString CalculateSHA256Hash(const QString &input);

};

#endif // HELPERFUNCTION_H
