#include "helperfunction.h"


QString HelperFunction::GetCurrentTime()
{
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("yyyy-MM-dd");
    return formattedTime;
}
