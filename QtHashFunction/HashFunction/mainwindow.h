#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "HashTable.h"
#include<QTableWidget>
#include <QPushButton>
#include <QGraphicsScene>

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
    void on_pushButton_createTable_clicked();

    void on_pushButton_insert_clicked();

    void on_pushButton_remove_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_randFilling_clicked();

private:
    Ui::MainWindow *ui;
    HashTable table;
    QTableWidget *tableWidget = nullptr;
};
#endif // MAINWINDOW_H
