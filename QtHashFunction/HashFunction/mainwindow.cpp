#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tableWidget(new QTableWidget(this))

{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Key" << "Value");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_createTable_clicked()
{
    QString size = ui->lineEdit_create->text();
    if(size != ""){
        int intSize =  size.toInt();
        table.resize(intSize);
        ui->tableWidget->setRowCount(intSize);
    }
    else{
        QMessageBox::about(this, "Информация", "Пустая строка");
    }
}


void MainWindow::on_pushButton_insert_clicked()
{
    QString key = ui->lineKey->text();
    QString value = ui->lineValue->text();

    if(key != "" and value != ""){
        int intKey = key.toInt();
        std::string strValue = value.toStdString();
        bool checkOnFull = table.insert(intKey, strValue);
        if(checkOnFull){
            int hash = table.hashCode(intKey);
            QTableWidgetItem *newItemKey = new QTableWidgetItem(QString::number(intKey));
            QTableWidgetItem *newItemValue = new QTableWidgetItem(QString::fromLocal8Bit(strValue.c_str()));
            ui->tableWidget->setItem(hash, 0, newItemKey);
            ui->tableWidget->setItem(hash, 1, newItemValue);
        }
        else{
            QMessageBox::about(this, "Информация", "Таблица заполнена");

        }
    }
    else{
        QMessageBox::about(this, "Информация", "Пустая строка");
    }
}


void MainWindow::on_pushButton_remove_clicked()
{
    QString key = ui->lineKey->text();

    if(key != ""){
        int intKey = key.toInt();
        bool existsKey = table.searchKey(intKey);
        if(existsKey){
            int hash = table.hashCode(intKey);
            table.remove(intKey);
            QTableWidgetItem *emptyItem1 = new QTableWidgetItem(QString(""));
            QTableWidgetItem *emptyItem2 = new QTableWidgetItem(QString(""));

            ui->tableWidget->setItem(hash, 0, emptyItem1);
            ui->tableWidget->setItem(hash, 1, emptyItem2);
        }
        else{
            QMessageBox::about(this, "Информация", "Ключ не существует");
        }
    }
    else{
        QMessageBox::about(this, "Информация", "Пустая строка");
    }
}

void MainWindow::on_pushButton_search_clicked()
{
    int key = ui->lineKey->text().toInt();
    int hash = table.hashCode(key);
    if(table.searchKey(key)){
        ui->tableWidget->item(hash, 0)->setBackground(Qt::yellow);
        ui->tableWidget->item(hash, 1)->setBackground(Qt::yellow);

    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    table.clearTable();
    int size = ui->lineEdit_create->text().toInt();
    for(int i = 0; i < size; i++){
        QTableWidgetItem *emptyItem1 = new QTableWidgetItem(QString(""));
        QTableWidgetItem *emptyItem2 = new QTableWidgetItem(QString(""));
        ui->tableWidget->setItem(i, 0, emptyItem1);
        ui->tableWidget->setItem(i, 1, emptyItem2);

    }
}

void MainWindow::on_pushButton_randFilling_clicked()
{
    int size = ui->lineEdit_create->text().toInt();
    for(int i = 0; i < size; i++){
        int newKey = rand()%size+1;
        std::string newValue = std::to_string(rand());
        table.insert(newKey, newValue);
        int hash = table.hashCode(newKey);
        QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(newKey));
        QTableWidgetItem *newItem2 = new QTableWidgetItem(QString::fromLocal8Bit(newValue.c_str()));
        ui->tableWidget->setItem(hash, 0, newItem1);
        ui->tableWidget->setItem(hash, 1, newItem2);
    }
}

