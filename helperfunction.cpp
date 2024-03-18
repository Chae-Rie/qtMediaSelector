#include "helperfunction.h"


QString HelperFunction::GetCurrentTime()
{
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("yyyy-MM-dd");
    return formattedTime;
}

QString HelperFunction::CalculateSHA256Hash(const QString &input)
{
    QByteArray byteArray = input.toUtf8(); // Konvertiere den Eingabestring in QByteArray
    QByteArray hashArray = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha256); // Berechne den SHA-256-Hash
    return QString(hashArray.toHex()); // Konvertiere den Hash in einen Hexadezimal-String und gebe ihn zurück

}
