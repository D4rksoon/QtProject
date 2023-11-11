#include <QGraphicsScene>
#include <QMessageBox>
#include <string>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HuffmanTree.h"
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


void MainWindow::on_pushButton_encode_clicked()
{

    QString text = ui->textString->text();
    if(tree.root() == nullptr){
        tree.build(text.toStdString());
        printTree(tree.root(), 400, 50);
        //QMessageBox::about(this, "Информация", "Постройте дерево");
    }
    if(text != ""){
        std::string code;
        tree.encode(text.toStdString(), code);
        ui->textCode->setText(QString::fromStdString(code));
    }
    else{
        QMessageBox::about(this, "Информация", "Пустая строка");
    }
}


void MainWindow::on_pushButton_decode_clicked()
{
    QString code = ui->textCode->text();
    if(code != ""){
        std::string text;
        tree.decode(code.toStdString(), text);
        ui->textString->setText(QString::fromStdString(text));
    }
    else{
        QMessageBox::about(this, "Информация", "Пустая строка");
    }
}


void MainWindow::on_pushButton_buildTree_clicked()
{
    QString text = ui->textString->text();
    tree.build(text.toStdString());

    printTree(tree.root(), 400, 50);
}


void MainWindow::on_pushButton_clear_clicked()
{
    tree.clear();
    m_scene->clear();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    on_updateSceneTree();
}

void MainWindow::printTree(Node* root, int posX, int posY)
{
    int rangeBetween = range(root);
    GraphicsRectItem *Node = new GraphicsRectItem(QString::fromStdString(root->symbols()));
    Node->setPos(posX, posY);
    Node->setMargins(QMargins(6, 10, 5, 5));
    //Node->setBackgroundColor(QColor(rand() % 256, rand() % 256, rand() % 256));

    m_scene->addItem(Node);
    if(root->left())
    {
        m_scene->addLine(posX , posY + 20,  posX - rangeBetween, posY + 50 + 10)->setZValue(-1);
        printTree(root->left(), posX - rangeBetween, posY + 50 );

    }
    if(root->right())
    {
        m_scene->addLine(posX , posY + 20,  posX + rangeBetween, posY + 50 + 10)->setZValue(-1);
        printTree(root->right(), posX + rangeBetween, posY + 50);

    }
}

int MainWindow::range(Node* root)
{
    int minrange = 10;

    int rangeBetween = minrange + lenghtBetweenNode/2;
    int width = 2 * lenghtBetweenNode + 2 * minrange;

    for(int i = 0; i < tree.heightTree(root) - 2; i++ )
    {
        width = 2 * width;
        rangeBetween = width/2 - lenghtBetweenNode;
    }

    return rangeBetween;
}

void MainWindow::on_updateSceneTree()
{
    m_scene->setSceneRect(QRect(
        0, 0,
        ui->graphicsView->viewport()->width(),
        ui->graphicsView->viewport()->height()
        ));
    ui->statusbar->showMessage(tr("Scene size: [%1 x %2]").
                               arg(m_scene->width()).
                               arg(m_scene->height()));
}

