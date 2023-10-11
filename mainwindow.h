#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasemanager.h"
#include <QSqlQueryModel>

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

private:
    Ui::MainWindow *ui;
    databaseManager *db;
    void load_table();

};
#endif // MAINWINDOW_H
