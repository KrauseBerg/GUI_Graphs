#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->generate->setDisabled(true);
    ui->next->setDisabled(true);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_create_clicked(){
    ui->next->setDisabled(true);
    model = new QStandardItemModel;
    model_2 = new QStandardItemModel;
    size = ui->size->text().toInt();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            item = new QStandardItem(QString("0"));
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(i, j, item);
        }
    }
    ui->tableView->setModel(model);
    ui->num->setText("0");
    ui->generate->setDisabled(false);
}

void MainWindow::on_generate_clicked(){
    ui->next->setDisabled(false);
    int elem;
    srand(static_cast<unsigned int>(time(nullptr))); //Для рандомизации от времени
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            elem = rand()%2; //Случайно (либо 1 либо 0)
            if(i == j)
                elem = 0;
            ss << elem;
            item = new QStandardItem(QString::fromStdString(ss.str()));
            ss.str("");
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(i, j, item);
        }
    }
    ui->tableView->setModel(model);
}

void MainWindow::on_next_clicked(){
    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            index_1 = ui->tableView->model()->index(i,j,QModelIndex());
            myData_1 = ui->tableView->model()->data(index_1, Qt::DisplayRole);
            item = new QStandardItem(QString::number(myData_1.toInt()));
            item->setTextAlignment(Qt::AlignCenter);
            model_2->setItem(i,j, item);
        }
    }
    ui->tableView_2->setModel(model_2);
    int current = ui->num->text().toInt();
    for (int i = current; i < current + 1; i++){
        for (int j = 0; j < size; j++) {
            index_1 = ui->tableView->model()->index(j,i,QModelIndex());
            myData_1 = ui->tableView->model()->data(index_1, Qt::DisplayRole);
            if(myData_1.toInt() == 1){
                for(int cur = 0; cur < size; cur++){
                    index_1 = ui->tableView->model()->index(j,cur,QModelIndex());
                    myData_1 = ui->tableView->model()->data(index_1, Qt::DisplayRole);
                    index_2 = ui->tableView->model()->index(i,cur,QModelIndex());
                    myData_2 = ui->tableView->model()->data(index_2, Qt::DisplayRole);
                    myData_1 = myData_1.toInt() || myData_2.toInt();
                    item = new QStandardItem(QString::number(myData_1.toInt()));
                    item->setTextAlignment(Qt::AlignCenter);
                    model->setItem(j, cur, item);
                }
            }
            else{
                for(int cur = 0; cur < size; cur++){
                    index_1 = ui->tableView->model()->index(j,cur,QModelIndex());
                    myData_1 = ui->tableView->model()->data(index_1, Qt::DisplayRole);
                    item = new QStandardItem(myData_1.toString());
                    item->setTextAlignment(Qt::AlignCenter);
                    model->setItem(j, cur, item);
                }
            }
        }
    }
    ui->num->setText(QString::number(current + 1));
    if(current + 1 == size)
        ui->next->setDisabled(true);
    ui->tableView->setModel(model);
}
