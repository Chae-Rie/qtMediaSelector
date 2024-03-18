#include "credentialdialog.h"
#include "ui_credentialdialog.h"

CredentialDialog::CredentialDialog( DbManager& sqlLiteDatabase, QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::CredentialDialog)
    , m_rfSqlLiteDatabase(sqlLiteDatabase)
{
    m_ui->setupUi(this);
    m_allowedToLogin = false;


    connect(m_ui->pushButtonRegister, SIGNAL(clicked()), this, SLOT(handleButtonClickRegister()));
    connect(m_ui->pushButtonLogin, SIGNAL(clicked()), this, SLOT(handleButtonClickLogin()));
    connect(m_ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
}

CredentialDialog::~CredentialDialog()
{
    delete m_ui;
}

void CredentialDialog::handleButtonClickRegister()
{
    Datamanager::USER_CREDENTIALS usercredentialContainer;
    SetUserCredentialContainerAndHashPW(usercredentialContainer);

    bool success = m_rfSqlLiteDatabase.CreateNewRecord(usercredentialContainer);
    if (success){
        QMessageBox::information(nullptr, "Nutzer registriert", "Der Benutzer wurde erfolgreich angelegt. (Er kann noch 2x vorkommen)");

    } else {
        qDebug() << "Registierung für neuen Benutzer fehlgeschlagen.";
    }
}

void CredentialDialog::handleButtonClickLogin()
{

    Datamanager::USER_CREDENTIALS usercredentialContainer;
    SetUserCredentialContainerAndHashPW(usercredentialContainer);

    bool success = m_rfSqlLiteDatabase.CheckUserCredentials(usercredentialContainer);
    if (success){
        QMessageBox::information(nullptr, "Login", "Login erfolgreich, werde Benutzeroberfläche freigeben und diesen Dialog schließen!");

        m_allowedToLogin = true;
        // Triggered die Accept-Methode, die den Dialog schließt und den Main-Dialog öffnet
        QDialog::accept();
        return;
    } else {
        qDebug() << "Bad!";
    }
}

// Um DRY nicht zu verletzten, Setter für die Abfrage der Benutzerinformationen in den Steuerungselementen
void CredentialDialog::SetUserCredentialContainerAndHashPW(Datamanager::USER_CREDENTIALS &usercredentialContainer)
{
    usercredentialContainer.name = m_ui->lineEditName->text();
    usercredentialContainer.lastname = m_ui->lineEditLastName->text();
    usercredentialContainer.email = m_ui->lineEditEmail->text();
    usercredentialContainer.role = m_ui->comboBoxRoles->currentText();

    // ------------------- Password hashen da wir sowieso immer das Password hashen wollen
    QString passwordBuffer = m_ui->lineEditPassword->text();

    usercredentialContainer.password = HelperFunction::CalculateSHA256Hash(passwordBuffer);
    // ----------------------------------
}

