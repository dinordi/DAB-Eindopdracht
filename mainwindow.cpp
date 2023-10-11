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
    connect(ui->PK, &QRadioButton::clicked, this, &MainWindow::radioButtonToggled);
    connect(ui->KW, &QRadioButton::clicked, this, &MainWindow::radioButtonToggled);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::load_table()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT DISTINCT strMerk FROM NFS ORDER BY strMerk ASC");
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
    QString selectedBrand = ui->listViewMerken->currentIndex().data().toString();
    QString query = "SELECT strSerie,strNaam FROM NFS WHERE strMerk = :brand";
    QString query2 = "SELECT DISTINCT strStad,strLand FROM NFS WHERE strMerk = :brand";
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare(query);
    qry.bindValue(":brand", selectedBrand);
    qry.exec();
    model->setQuery(std::move(qry));
    ui->tableViewSerie->setModel(model);
    ui->tableViewSerie->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QSqlQueryModel *model2 = new QSqlQueryModel();
    QSqlQuery qry2;
    qry2.clear();
    qry2.prepare(query2);
    qry2.bindValue(":brand", selectedBrand);
    qry2.exec();
    model2->setQuery(std::move(qry2));
    ui->tableViewHQ->setModel(model2);
    ui->tableViewHQ->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}


void MainWindow::on_tableViewSerie_doubleClicked(const QModelIndex &index)
{
    QString selectedType = ui->tableViewSerie->currentIndex().sibling(ui->tableViewSerie->currentIndex().row(), 1).data().toString();
    QString selectedSerie = ui->tableViewSerie->currentIndex().sibling(ui->tableViewSerie->currentIndex().row(), 0).data().toString();
    qDebug() << selectedType;
    QString query = "SELECT intVermogenPK,intVermogenkW,strLogo,autoFoto FROM NFS WHERE strSerie = :Serie and strNaam = :type";
    QSqlQuery qry;
    qry.prepare(query);
    qry.bindValue(":type", selectedType);
    qry.bindValue(":Serie", selectedSerie);
    qry.exec();
    while(qry.next())
    {
        this->vermogenPK = qry.value(0).toString();
        this->vermogenkW = qry.value(1).toString();
        this->pathCarImage = qry.value(3).toString();
        this->pathLogoImage = qry.value(2).toString();
    }
    radioButtonToggled();





    QPixmap pixmap(this->pathCarImage);
    QPixmap pixmap2(this->pathLogoImage);
    if (!pixmap.isNull()) {
        QSize lblImage = ui->lblImage->size();
        QSize lblLogo = ui->lblLogo->size();
        QPixmap scaled = pixmap.scaled(lblImage, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPixmap scaled2 = pixmap2.scaled(lblLogo, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        // The image was successfully loaded
        ui->lblImage->setPixmap(scaled);
        ui->lblImage->setScaledContents(true); // Optional: Scale the image to fit the QLabel
        ui->lblLogo->setPixmap(scaled2);
        ui->lblLogo->setScaledContents(true); // Optional: Scale the image to fit the QLabel
    } else {
        // Failed to load the image, handle the error
        qDebug() << "Error: Failed to load the image.";
    }


}

void MainWindow::radioButtonToggled()
{
    if(ui->PK->isChecked())
    {
        ui->lblVermogen->setText(this->vermogenPK);
        ui->lblUnit->setText("PK");
    }
    else
    {
        ui->lblVermogen->setText(this->vermogenkW);
        ui->lblUnit->setText("kW");
    }
}

