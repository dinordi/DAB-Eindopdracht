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
    qry.prepare("SELECT tblMerk.strMerk FROM tblMerk");
    qry.exec();
    model->setQuery(std::move(qry));
    ui->listViewMerken->setModel(model);

    QSqlQueryModel *countryModel = new QSqlQueryModel();

    // Connect a slot to handle brand selection in the first list view
    QObject::connect(ui->listViewMerken, &QListView::clicked, [countryModel, this](const QModelIndex &index) {
    QString selectedBrand = index.data().toString();

    // Create a new query to fetch the country based on the selected brand
    QSqlQuery countryQuery;
    countryQuery.prepare("SELECT tblLand.strLand FROM tblLand INNER JOIN tblMerk ON tblLand.ID = tblMerk.IDLand WHERE tblMerk.strMerk = ?");
    countryQuery.addBindValue(selectedBrand);
    countryQuery.exec();

    // Set the query result as the model for the second QListView
    countryModel->setQuery(std::move(countryQuery));
    ui->listViewTypes->setModel(countryModel);
    });

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
}


void MainWindow::on_listViewMerken_clicked(const QModelIndex &index)
{
    qDebug() << index;
}

