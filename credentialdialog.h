#ifndef CREDENTIALDIALOG_H
#define CREDENTIALDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "datamanager.h"
#include "dbmanager.h"

namespace Ui {
class CredentialDialog;
}

class CredentialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CredentialDialog( DbManager& sqlLiteDatabase, QWidget *parent = nullptr);
    virtual ~CredentialDialog();

    inline bool GetUserStatus(){return m_allowedToLogin;};
private slots:
    void handleButtonClickRegister();
    void handleButtonClickLogin();

private:
    void SetUserCredentialContainerAndHashPW(Datamanager::USER_CREDENTIALS &usercredentialContainer);


private:
    Ui::CredentialDialog *m_ui;

    bool m_allowedToLogin;
    DbManager&  m_rfSqlLiteDatabase;

};

#endif // CREDENTIALDIALOG_H
