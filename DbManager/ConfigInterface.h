#ifndef CONFIGINTERFACE_H
#define CONFIGINTERFACE_H
#include "dbmanager_global.h"
#include <QSettings>

class DBMANAGERSHARED_EXPORT ConfigInterface
{
public:
    static ConfigInterface *getInstance(void);

    const QVariant readDatabase(QString sec,QString key,QVariant defaultVal) const;
    void writeDatabase(QString sec, QString key, QVariant val);

private:
    ConfigInterface();
    static ConfigInterface *mInstance;

    QSettings databaseSettings;
};

#endif // CONFIGINTERFACE_H
