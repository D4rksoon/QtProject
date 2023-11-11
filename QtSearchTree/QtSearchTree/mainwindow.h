#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "searchtree.h"
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
    void on_pushButton_incertNode_clicked();

    void on_pushButton_removeNode_clicked();

    void on_pushButton_searchNode_clicked();

    void on_updateSceneTree();

    void on_pushButton_clearTree_clicked();

protected:
    void printTree(SearchTree::Node* root, int posX, int posY);

    int range(SearchTree::Node* root);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene = nullptr;
    SearchTree tree;
    SearchTree::Node* root = tree.root();
    int lenghtBetweenNode = 5;
};
#endif // MAINWINDOW_H
