#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasemanager.h"
#include <QSqlQueryModel>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void showMainPage();
    void showDatabasePage();
    void on_btnReconnect_clicked();

    void on_listViewMerken_clicked(const QModelIndex &index);

    void on_tableViewSerie_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    databaseManager *db;
    void load_table();
    QString vermogenPK;
    QString vermogenkW;
    QString pathCarImage;
    QString pathLogoImage;
    void radioButtonToggled();

};
#endif // MAINWINDOW_H
