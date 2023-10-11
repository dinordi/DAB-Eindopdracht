#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new databaseManager();
    load_table();
    connect(ui->btnShowMain, &QPushButton::clicked, this, &MainWindow::showMainPage);
    connect(ui->btnShowDatabase, &QPushButton::clicked, this, &MainWindow::showDatabasePage);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::load_table()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT DISTINCT TRIM(strMerk) FROM NFS");
    qry.exec();
    model->setQuery(std::move(qry));
    ui->listViewMerken->setModel(model);



}

void MainWindow::showMainPage()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::showDatabasePage()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnReconnect_clicked()
{
    delete db;
    db = new databaseManager(ui->lineHost->text(), ui->lineUser->text(), ui->linePass->text(), ui->lineDatabase->text());
    load_table();
}


void MainWindow::on_listViewMerken_clicked(const QModelIndex &index)
{
    QString selectedBrand = ui->listViewMerken->currentIndex().data().toString().trimmed();
    QString query = "SELECT strSerie,strStad,strLand FROM NFS WHERE strMerk = :brand";

    qDebug() << query;
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare(query);
    qry.bindValue(":brand", selectedBrand);
    qry.exec();
    model->setQuery(std::move(qry));
    ui->listViewTypes->setModel(model);
    ui->tableView->setModel(model);
}

