#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QString>
#include <QDebug>
#include <QMessageBox>





class databaseManager
{
private:
    QSqlDatabase db;
    QSqlQuery *qry;
    QDateTime dateTime;
    bool connectedDB;

public:
    databaseManager();
    databaseManager(QString host, QString user, QString pass, QString database);
    virtual ~databaseManager();
    void printDB();

};

#endif // DATABASEMANAGER_H
