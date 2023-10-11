#include "databasemanager.h"

databaseManager::databaseManager()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    qry = new QSqlQuery;

    db.setHostName("s927.whserver.nl");
    db.setDatabaseName("p13799_databases");
    db.setUserName("p13799_databases");
    db.setPassword("databases");
    if(!db.open())
    {
        qDebug() << "Connection failed: " << db.lastError().text();
        QMessageBox msgBox;
        QString error = "Connection failed: ";
        error.append(db.lastError().text());
        msgBox.setText(error);
        msgBox.exec();
        this->connectedDB = false;
    }
    else{
        qDebug() << "Connected to database with hostname: " << db.hostName();
        this->connectedDB = true;
    }
}

databaseManager::databaseManager(QString host, QString user, QString pass, QString database)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    qry = new QSqlQuery;

    db.setHostName(host);
    db.setDatabaseName(database);
    db.setUserName(user);
    db.setPassword(pass);
    if(!db.open())
    {
        qDebug() << "Connection failed: " << db.lastError().text();
        QMessageBox msgBox;
        QString error = "Connection failed: ";
        error.append(db.lastError().text());
        msgBox.setText(error);
        msgBox.exec();
        this->connectedDB = false;
    }
    else{
        qDebug() << "Connected to database with hostname: " << db.hostName();
        this->connectedDB = true;
    }
}

databaseManager::~databaseManager()
{
    delete qry;
}

void databaseManager::printDB()
{
    qDebug() << "Printing...";
    qry->prepare("SELECT * FROM ___");
    QDebug debug = qDebug();
    debug.noquote();
    if(qry->exec())
    {
        while(qry->next())
        {
            debug << qry->value(1).toString();
        }
    }
}

