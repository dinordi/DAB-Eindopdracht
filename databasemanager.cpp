#include "databasemanager.h"

databaseManager::databaseManager()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    qry = new QSqlQuery;

    db.setHostName("localhost");
    db.setDatabaseName("DAB-1");
    db.setUserName("root");
    db.setPassword("12345678");
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

        QString query =
            "CREATE VIEW NFS AS "
            "SELECT strMerk, strSerie, strNaam, intVermogenPK, intVermogenkW, strStad, strLand "
            "FROM "
            "    tblland "
            "LEFT JOIN "
            "    tblstad ON tblland.IDLand = tblstad.IDLand "
            "LEFT JOIN "
            "    tblmerk ON tblstad.IDStad = tblmerk.IDstad "
            "LEFT JOIN "
            "    tblserie ON tblmerk.IDMerk = tblserie.IDMerk "
            "LEFT JOIN "
            "    tblserietype ON tblserie.IDSerie = tblserietype.IDSerie "
            "LEFT JOIN "
            "    tbltype ON tblserietype.IDType = tbltype.IDType "
            "ORDER BY strMerk ASC ";
        qry->prepare(query);
        qry->exec();
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
        QString query =
            "CREATE VIEW NFS AS "
            "SELECT strMerk, strSerie, strNaam, intVermogenPK, intVermogenkW, strStad, strLand, strLogo, autofoto "
            "FROM "
            "    tblland "
            "LEFT JOIN "
            "    tblstad ON tblland.IDLand = tblstad.IDLand "
            "LEFT JOIN "
            "    tblmerk ON tblstad.IDStad = tblmerk.IDstad "
            "LEFT JOIN "
            "    tblserie ON tblmerk.IDMerk = tblserie.IDMerk "
            "LEFT JOIN "
            "    tblserietype ON tblserie.IDSerie = tblserietype.IDSerie "
            "LEFT JOIN "
            "    tbltype ON tblserietype.IDType = tbltype.IDType "
            "ORDER BY strMerk ASC ";
        qry->prepare(query);
        qry->exec();
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

