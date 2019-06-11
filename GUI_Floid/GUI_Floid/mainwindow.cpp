#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>

using namespace std;

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
    ss = new QString * [size];
    for (int i = 0; i < size; i++) {
        ss[i] = new QString[size];
        for (int j = 0; j < size; j++) {
            ss[i][j] = "(" + QString::number(i+1) + ", " + QString::number(j+1) + ")";
            item = new QStandardItem("0");
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(i, j, item);
        }
    }
    ui->initial->setModel(model);
    ui->generate->setDisabled(false);
}

void MainWindow::on_generate_clicked(){
    ui->next->setDisabled(false);
    int elem;
    int check;
    srand(static_cast<unsigned int>(time(nullptr))); //Для рандомизации от времени
    srand(time(0));
    vspom_mat = new int * [size];
    for (int i = 0; i < size; i++) {
        vspom_mat[i] = new int[size];
        for (int j = 0; j < size; j++) {
            vspom_mat[i][j] = j;
            if(i == j)
                continue;
            check = rand()%2;
            if (check == 1){
                elem = rand()%100; //Случайно (от 0 до 99)
                item = new QStandardItem(QString::number(elem));
            }
            else {
                item = new QStandardItem(QString("∞"));
            }
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(i, j, item);
        }
    }
    ui->initial->setModel(model);
    ui->before->setModel(model);
    cout << endl;
}

void MainWindow::on_next_clicked(){
    int before_num = ui->before_num->text().toInt();
    int after_num = ui->after_num->text().toInt();
    ui->before_num ->setText(QString::number(before_num+=1));
    ui->after_num->setText(QString::number(after_num+=1));

    init_elements = new int * [size];
    before_elements = new int * [size];
    int elem;
    for(int i = 0; i < size; i++){
        init_elements[i] = new int[size];
        for (int j = 0; j < size; j++){
            elem = ui->initial->model()->itemData(ui->initial->model()->index(i,j,QModelIndex())).value(0).toInt();
            if (i != j && elem == 0){
                elem = 0xFFFF;
                ss[i][j] =" ";
            }
            if (i == j)
                ss[i][j] = " ";
            init_elements[i][j] = elem;
            item = new QStandardItem(QString::number(elem));
            if (elem == 0xFFFF)
                item = new QStandardItem(QString("∞"));
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(i, j, item);
        }
    }
    ui->initial->setModel(model);

    if (before_num == 0){
        for (int i = 0 ; i < size ; i ++ ) {
            before_elements[i] = new int [size];
        }
        before_elements = init_elements;
    }
    else {
        for (int i = 0 ; i < size; i ++ ) {
            before_elements[i] = new int [size];
        }
        before_elements = elements;
    }

    elements = new int * [size];

    model_3 = new QStandardItemModel;

    for (int i = 0; i < size; i++) {
        elements[i] = new int[size];
        for (int j = 0; j < size; j++) {
            if( i == j )
                elements[i][j] = 0;

            else{
                if( (before_elements[i][before_num] + before_elements[before_num][j]) < before_elements[i][j] ){
                    elements[i][j] = before_elements[i][before_num] + before_elements[before_num][j];
                    vspom_mat[i][j] = global_per;
                }
                else
                    elements[i][j] = before_elements[i][j];

            }
        }
    }
    global_per ++;

    for (int i = 0; i < size; i++) {
        for (int j = 0 ; j < size; j ++ ) {
            cout << vspom_mat[i][j] << " ";
            item = new QStandardItem(QString::number(elements[i][j]));
            if (elements[i][j] == 0xFFFF)
                item = new QStandardItem(QString("∞"));
            item->setTextAlignment(Qt::AlignCenter);
            model_3->setItem(i, j, item);
        }
        cout<<endl;
    }
    cout << endl;
    ui->after->setModel(model_3);

    model_2 = new QStandardItemModel;

    for (int i = 0 ; i < size; i ++ ) {
        for (int j = 0 ; j < size; j ++ ) {
            item = new QStandardItem(QString::number(before_elements[i][j]));
            if (before_elements[i][j] == 0xFFFF)
                item = new QStandardItem(QString("∞"));
            item->setTextAlignment(Qt::AlignCenter);
            model_2->setItem(i, j, item);
        }
    }
    ui->before->setModel(model_2);

    model_4 = new QStandardItemModel;


    for (int i = 0 ; i < size; i ++ ) {
        for (int j = 0 ; j < size; j ++ ) {
            int vspom_per_j = j;
            int vspom_Per_i = i;
            QString vspom_str = "(" + QString::number(vspom_Per_i + 1) + ", ";
            while(vspom_mat[vspom_Per_i][vspom_per_j] != vspom_per_j){
                ss[i][j] = vspom_str + QString::number(vspom_mat[vspom_Per_i][vspom_per_j] + 1) + ")";
                if(ss[vspom_Per_i][vspom_mat[vspom_Per_i][vspom_per_j]].size() > 6)
                    ss[i][j] = ss[vspom_Per_i][vspom_mat[vspom_Per_i][vspom_per_j]];
                if(vspom_mat[vspom_Per_i][vspom_per_j] > j){
                    vspom_strucr t;
                    t.x = vspom_Per_i;
                    t.y = j;
                    vec_duga.push_back(t);
                }
                vspom_str = ss[i][j] + "(" + QString::number(vspom_mat[vspom_Per_i][vspom_per_j] + 1) + ", ";
                vspom_Per_i = vspom_mat[vspom_Per_i][vspom_per_j];
                if (vspom_mat[vspom_Per_i][vspom_per_j] == vspom_per_j)
                    ss[i][j] = ss[i][j] + "(" + QString::number(vspom_Per_i + 1) + ", " +
                            QString::number(vspom_per_j + 1) + ")";
            }
            item = new QStandardItem(ss[i][j]);
            item->setTextAlignment(Qt::AlignCenter);
            model_4->setItem(i, j, item);
        }
    }

    for (int i = 0; i < vec_duga.size(); i++) {
        int vspom_per_j = vec_duga[i].y;
        int vspom_Per_i = vec_duga[i].x;
        QString vspom_str = "(" + QString::number(vspom_Per_i + 1) + ", ";
        while(vspom_mat[vspom_Per_i][vspom_per_j] != vspom_per_j){
            ss[vec_duga[i].x][vec_duga[i].y] = vspom_str + QString::number(vspom_mat[vspom_Per_i][vspom_per_j] + 1) + ")";
            if(ss[vspom_Per_i][vspom_mat[vspom_Per_i][vspom_per_j]].size() > 6)
                ss[vec_duga[i].x][vec_duga[i].y] = ss[vspom_Per_i][vspom_mat[vspom_Per_i][vspom_per_j]];
            vspom_str = ss[vec_duga[i].x][vec_duga[i].y] + "(" + QString::number(vspom_mat[vspom_Per_i][vspom_per_j] + 1) + ", ";
            vspom_Per_i = vspom_mat[vspom_Per_i][vspom_per_j];
            if (vspom_mat[vspom_Per_i][vspom_per_j] == vspom_per_j)
                ss[vec_duga[i].x][vec_duga[i].y] = ss[vec_duga[i].x][vec_duga[i].y] + "(" + QString::number(vspom_Per_i + 1) + ", " +
                        QString::number(vspom_per_j + 1) + ")";
        }
        item = new QStandardItem(ss[vec_duga[i].x][vec_duga[i].y]);
        item->setTextAlignment(Qt::AlignCenter);
        model_4->setItem(vec_duga[i].x, vec_duga[i].y, item);
    }

    ui->short_track->setModel(model_4);

    if(before_num + 1 == size)
        ui->next->setDisabled(true);
}
