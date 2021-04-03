#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    testArrays();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testArrays()
{
    IncrementalArray i_array1 = IncrementalArray();
    Array &array1 = i_array1;
    array1.add(-1);
    array1[0] = 2;
    array1.add(5);
    array1.print();

    IncrementalArray i_array2 = IncrementalArray(0);
    Array &array2 = i_array2;
    array2.add(8);
    array2.print();

    array2.addAll(array1);
    array2.print();

    array1.addAll(array2);
    array2.addAll(array1);
    array2.print();

    BlockyArray b_array3 = BlockyArray(2);
    Array &array3 = b_array3;

    array3.print();
    array3.add(2);
    array3.add(5);
    array3.add(-1);
    array3.print();

    array3[0] = 0;
    array2.addAll(array2);
    array3.addAll(array2);
    array3.print();
}

