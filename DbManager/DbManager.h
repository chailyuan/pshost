#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "dbmanager_global.h"
#include <QtSql>


class DBMANAGERSHARED_EXPORT DbManager
{

public:
    static DbManager *getInstance();
    QSqlDatabase getConfigDb(QString *type=NULL);


private:
    DbManager();
    static DbManager* mInstance;
    QSqlDatabase getDb(const QString& connectionName,
                       const QString& serverIp, int port,
                       const QString& userId, const QString & password,
                       const QString& dbName, const QString & driver);
    bool checkDb(QSqlDatabase& db);
};

#endif // DBMANAGER_H
