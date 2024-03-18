#ifndef TESTSTRINGOPERATIONS_H
#define TESTSTRINGOPERATIONS_H

#include <QObject>

class testStringOperations : public QObject
{
    // Ohne das Macro findet er die Testfunktion nicht
    Q_OBJECT
public:
    explicit testStringOperations(QObject *parent = nullptr);

signals:
};

#endif // TESTSTRINGOPERATIONS_H
