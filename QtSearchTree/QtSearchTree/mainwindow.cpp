#include <QMessageBox>
#include <QGraphicsScene>
#include <vector>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "searchtree.h"
#include "GraphicsRectItem.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(m_scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_incertNode_clicked()
{
    QString key = ui->lineEdit->text();
    if(key != ""){
        tree.addNode(key.toInt());
        on_updateSceneTree();
    }
    else{
        QMessageBox::about(this, "Ошибка", "Пустая строка");
    }
}


void MainWindow::on_pushButton_removeNode_clicked()
{
    if (tree.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Дерево пустое");
    }

    QString key = ui->lineEdit->text();
    if(key != ""){
        int keyInt = key.toInt();
        if (keyInt == (tree.searchNode(keyInt))->m_key){
            tree.deleteNode(keyInt);
        }
        else{
            QMessageBox::about(this, "Ошибка", "Узла нет в дереве");
        }

    }
    else{
        QMessageBox::about(this, "Информация", "Пустая строка");

    }

    on_updateSceneTree();
}


void MainWindow::on_pushButton_searchNode_clicked()
{

    QString key = ui->lineEdit->text();


    if(key != "")
    {
        if(tree.searchNode(key.toInt())){
            QMessageBox::about(this, "Поиск", "Узел есть в дереве");
        }
        else{
            QMessageBox::about(this, "Поиск", "Узла нет в дереве");
        }

    }
    else
    {
        QMessageBox::about(this, "Информация", "Строка пуста");
    }
}

void MainWindow::on_pushButton_clearTree_clicked()
{
    tree.clearTree();
    m_scene->clear();
}

void MainWindow::on_updateSceneTree()
{
    root = tree.root();
    m_scene->clear();
    if(tree.root()){
        printTree(tree.root(), 0, 0);
    }
}

void MainWindow::printTree(SearchTree::Node* root, int posX, int posY)
{
    int rangeBetween = range(root);
    GraphicsRectItem *Node = new GraphicsRectItem(QString::number(root->m_key));
    Node->setPos(posX, posY);
    Node->setMargins(QMargins(8, 10, 5, 5));
    //Node->setBackgroundColor(QColor(rand() % 256, rand() % 256, rand() % 256));

    m_scene->addItem(Node);
    if(root->m_left)
    {
        m_scene->addLine(posX, posY + 20,  posX - rangeBetween, posY + 50)->setZValue(-1);
        printTree(root->m_left, posX - rangeBetween, posY + 50 );

    }
    if(root->m_right)
    {
        m_scene->addLine(posX, posY + 20,  posX + rangeBetween, posY + 50)->setZValue(-1);
        printTree(root->m_right, posX + rangeBetween, posY + 50);

    }
}

int MainWindow::range(SearchTree::Node* root)
{
    int minrange = 20;

    int rangeBetween = minrange + lenghtBetweenNode/2;
    int width = 2 * lenghtBetweenNode + 2 * minrange;

    for(int i = 0; i < tree.heightTree(root) - 2; i++ )
    {
        width = 2 * width;
        rangeBetween = width/2 - lenghtBetweenNode;
    }

    return rangeBetween;
}


