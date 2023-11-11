#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "HuffmanTree.h"
#include<QListWidget>
#include<QLineEdit>
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
    void on_pushButton_encode_clicked();

    void on_pushButton_decode_clicked();

    void on_pushButton_buildTree_clicked();

    void on_pushButton_clear_clicked();

    void on_updateSceneTree();

protected:
    void resizeEvent(QResizeEvent *event) override;
    int range(Node* root);
    void printTree(Node* root, int posX, int posY);

public:


private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene = nullptr;
    HuffmanTree tree;
    int lenghtBetweenNode = 5;
};
#endif // MAINWINDOW_H
