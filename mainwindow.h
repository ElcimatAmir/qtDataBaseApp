#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlQueryModel>
#include<QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_showingTable_clicked();

    void on_searchButton_clicked();

   // void on_pushButton_4_clicked();


    void on_loginButton_clicked();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_actionenglish_triggered();

    void on_action_4_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
