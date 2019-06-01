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
    ss = new QString *[size];
    for (int i = 0; i < size; i++) {
        ss[i] = new QString [size];
        for (int j = 0; j < size; j++) {
            item = new QStandardItem(QString("0"));
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
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(i == j)
                continue;
            else{
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
    }
    ui->initial->setModel(model);
    ui->before->setModel(model);
}


void MainWindow::on_next_clicked(){
    int before_num = ui->before_num->text().toInt();
    int after_num = ui->after_num->text().toInt();
    ui->before_num ->setText(QString::number(before_num+=1));
    ui->after_num->setText(QString::number(after_num+=1));

    init_elements = new int * [size];
    if (before_num == 0)
        before_elements = new int * [size];
    else{
        before_elements = new int * [before_num];
    }
    int elem;
    for(int i = 0; i < size; i++){
        init_elements[i] = new int[size];
        for (int j = 0; j < size; j++){
            elem = ui->initial->model()->itemData(ui->initial->model()->index(i,j,QModelIndex())).value(0).toInt();
            if (i != j && elem == 0)
                elem = 0xFFFF;
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
        for (int i = 0 ; i < before_num; i ++ ) {
            before_elements[i] = new int [before_num];
        }
        before_elements = elements;
    }

    elements = new int * [before_num + 1];

    model_3 = new QStandardItemModel;

    duga duga;
    duga.k = -1;
    duga.k_1 = -1;
    duga.k_2 = -1;
    for (int i =  0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            vec_duga[i].push_back(duga);
        }
    }

    for (int i = 0; i < before_num + 1; i++) {
        elements[i] = new int[before_num + 1];
        for (int j = 0; j < before_num + 1; j++) {
            if( i == before_num && j < before_num ){
                int perem = 0xFFFF;
                for (int z = 0 ; z < before_num; z ++ ) {
                    elem = init_elements[i][z] + before_elements[z][j];
                    if (elem < perem){
                        perem = elem;
                        vec_duga[i][j].x1 = i + 1;
                        vec_duga[i][j].x2 = z + 1;
                        vec_duga[i][j].x3 = z + 1;
                        vec_duga[i][j].x4 = j + 1;
                        if(vec_duga[vec_duga[i][j].x1 - 1][vec_duga[i][j].x2 - 1].k == 4)
                            vec_duga[i][j].k_1 = 1;
                        if(vec_duga[vec_duga[i][j].x3 - 1][vec_duga[i][j].x4 - 1].k == 4)
                            vec_duga[i][j].k_2 = 1;
                        vec_duga[i][j].k = 4;
                        if(vec_duga[i][j].x1 == vec_duga[i][j].x2)
                            vec_duga[i][j].k = 2;
                        if(vec_duga[i][j].x3 == vec_duga[i][j].x4)
                            vec_duga[i][j].k = 1;
                    }
                }
                elements[i][j] = perem;
                if(perem == 0xFFFF){
                    ss[i][j] = "-";
                }
                else {
                    if(vec_duga[i][j].k == 1)
                        ss[i][j] = "(" + QString::number(vec_duga[i][j].x1) + ", " + QString::number(vec_duga[i][j].x2) + ")";
                    if(vec_duga[i][j].k == 2)
                        ss[i][j] = "(" + QString::number(vec_duga[i][j].x3) + ", " + QString::number(vec_duga[i][j].x4) + ")";
                    if(vec_duga[i][j].k == 4){
                        ss[i][j] = "(" + QString::number(vec_duga[i][j].x1) + ", " + QString::number(vec_duga[i][j].x2) + ")("
                                + QString::number(vec_duga[i][j].x3) + ", " + QString::number(vec_duga[i][j].x4) + ")";
                        if(vec_duga[i][j].k_1 == 1 && vec_duga[i][j].k_2 != 1)
                            ss[i][j] = ss[vec_duga[i][j].x1 - 1][vec_duga[i][j].x2 - 1]+"("+ QString::number(vec_duga[i][j].x3) + ", " + QString::number(vec_duga[i][j].x4) + ")";
                        if(vec_duga[i][j].k_2 == 1 && vec_duga[i][j].k_1 != 1)
                            ss[i][j] = "(" + QString::number(vec_duga[i][j].x1) + ", " + QString::number(vec_duga[i][j].x2) + ")"+ss[vec_duga[i][j].x3 - 1][vec_duga[i][j].x4 - 1];
                        if(vec_duga[i][j].k_2 == 1 && vec_duga[i][j].k_1 == 1)
                            ss[i][j] = ss[vec_duga[i][j].x1 - 1][vec_duga[i][j].x2 - 1] + ss[vec_duga[i][j].x3 - 1][vec_duga[i][j].x4 - 1];
                    }
                }
            }
            if( j == before_num && i < before_num){
                int perem = 0xFFFF;
                for (int z = 0 ; z < before_num; z ++ ) {
                    elem = init_elements[z][j] + before_elements[i][z];
                    if(elem < perem){
                        perem = elem;
                        vec_duga[i][j].x1 = i + 1;
                        vec_duga[i][j].x2 = z + 1;
                        vec_duga[i][j].x3 = z + 1;
                        vec_duga[i][j].x4 = j + 1;
                        if(vec_duga[vec_duga[i][j].x1 - 1][vec_duga[i][j].x2 - 1].k == 4)
                            vec_duga[i][j].k_1 = 1;
                        if(vec_duga[vec_duga[i][j].x3 - 1][vec_duga[i][j].x4 - 1].k == 4)
                            vec_duga[i][j].k_2 = 1;
                        vec_duga[i][j].k = 4;
                        if(vec_duga[i][j].x1 == vec_duga[i][j].x2)
                            vec_duga[i][j].k = 2;
                        if(vec_duga[i][j].x3 == vec_duga[i][j].x4)
                            vec_duga[i][j].k = 1;
                    }
                }
                elements[i][j] = perem;
                if(perem == 0xFFFF){
                    ss[i][j] = "-";
                }
                else{
                    if(vec_duga[i][j].k == 1)
                        ss[i][j] = "(" + QString::number(vec_duga[i][j].x1) + ", " + QString::number(vec_duga[i][j].x2) + ")";
                    if(vec_duga[i][j].k == 2)
                        ss[i][j] = "(" + QString::number(vec_duga[i][j].x3) + ", " + QString::number(vec_duga[i][j].x4) + ")";
                    if(vec_duga[i][j].k == 4){
                        ss[i][j] = "(" + QString::number(vec_duga[i][j].x1) + ", " + QString::number(vec_duga[i][j].x2) + ")("
                                + QString::number(vec_duga[i][j].x3) + ", " + QString::number(vec_duga[i][j].x4) + ")";
                        if(vec_duga[i][j].k_1 == 1 && vec_duga[i][j].k_2 != 1)
                            ss[i][j] = ss[vec_duga[i][j].x1 - 1][vec_duga[i][j].x2 - 1]+"("+ QString::number(vec_duga[i][j].x3) + ", " + QString::number(vec_duga[i][j].x4) + ")";
                        if(vec_duga[i][j].k_2 == 1 && vec_duga[i][j].k_1 != 1)
                            ss[i][j] = "(" + QString::number(vec_duga[i][j].x1) + ", " + QString::number(vec_duga[i][j].x2) + ")"+ss[vec_duga[i][j].x3 - 1][vec_duga[i][j].x4 - 1];
                        if(vec_duga[i][j].k_2 == 1 && vec_duga[i][j].k_1 == 1)
                            ss[i][j] = ss[vec_duga[i][j].x1 - 1][vec_duga[i][j].x2 - 1] + ss[vec_duga[i][j].x3 - 1][vec_duga[i][j].x4 - 1];
                    }
                }
            }
            if( i == j ){
                elements[i][j] = 0;
                ss[i][j] = "-";
                vec_duga[i][j].k = 0;
            }
            else if( i < before_num && j < before_num){
                int perem = 0xFFFF;
                for (int z = 0 ; z < before_num; z ++ ) {
                    elem = init_elements[z][before_num] + before_elements[i][z];
                    if(elem < perem){
                        perem = elem;
                        vec_duga[i][j].x1 = i + 1;
                        vec_duga[i][j].x2 = before_num + 1;
                        if(vec_duga[vec_duga[i][j].x1 - 1][vec_duga[i][j].x2 - 1].k == 4)
                            vec_duga[i][j].k_1 = 1;
                    }
                }
                int perem_2 = 0xFFFF;
                for (int z = 0 ; z < before_num; z ++ ) {
                    elem = init_elements[before_num][z] + before_elements[z][j];
                    if(elem < perem_2){
                        perem_2 = elem;
                        vec_duga[i][j].x3 = before_num + 1;
                        vec_duga[i][j].x4 = j + 1;
                        if(vec_duga[vec_duga[i][j].x3 - 1][vec_duga[i][j].x4 - 1].k == 4)
                            vec_duga[i][j].k_2 = 1;
                    }
                }
                if(perem + perem_2 < before_elements[i][j]){
                    elements[i][j] = perem + perem_2;
                    if(perem + perem_2 == 0xFFFF)
                        ss[i][j] = "-";
                    else{
                        vec_duga[i][j].k = 4;
                        ss[i][j] = "(" + QString::number(vec_duga[i][j].x1) + ", " + QString::number(vec_duga[i][j].x2) + ")("
                                + QString::number(vec_duga[i][j].x3) + ", " + QString::number(vec_duga[i][j].x4) + ")";
                        if(vec_duga[i][j].k_1 == 1 && vec_duga[i][j].k_2 != 1)
                            ss[i][j] = ss[vec_duga[i][j].x1 - 1][vec_duga[i][j].x2 - 1]+"("+ QString::number(vec_duga[i][j].x3) + ", " + QString::number(vec_duga[i][j].x4) + ")";
                        if(vec_duga[i][j].k_2 == 1 && vec_duga[i][j].k_1 != 1)
                            ss[i][j] = "(" + QString::number(vec_duga[i][j].x1) + ", " + QString::number(vec_duga[i][j].x2) + ")"+ss[vec_duga[i][j].x3 - 1][vec_duga[i][j].x4 - 1];
                        if(vec_duga[i][j].k_2 == 1 && vec_duga[i][j].k_1 == 1)
                            ss[i][j] = ss[vec_duga[i][j].x1 - 1][vec_duga[i][j].x2 - 1] + ss[vec_duga[i][j].x3 - 1][vec_duga[i][j].x4 - 1];
                        if(vec_duga[i][j].x3 == vec_duga[i][j].x4){
                            vec_duga[i][j].k = 1;
                            ss[i][j] = "(" + QString::number(vec_duga[i][j].x1) + ", " + QString::number(vec_duga[i][j].x2) + ")";
                        }
                        if(vec_duga[i][j].x1 == vec_duga[i][j].x2){
                            vec_duga[i][j].k = 2;
                            ss[i][j] = "(" + QString::number(vec_duga[i][j].x3) + ", " + QString::number(vec_duga[i][j].x4) + ")";
                        }
                    }

                }
                else{
                    elements[i][j] = before_elements[i][j];
                    if(before_elements[i][j] == 0xFFFF)
                        ss[i][j] = "-";
                    else if(vec_duga[i][j].k != 4 && vec_duga[i][j].k != 2 && vec_duga[i][j].k != 1){
                        ss[i][j] = "(" + QString::number(vec_duga[i][j].x1) + ", " + QString::number(vec_duga[i][j].x4) + ")";
                        vec_duga[i][j].k = 3;
                    }
                }
            }
        }
    }

    for (int i = 0; i < before_num + 1; i++) {
        for (int j = 0 ; j < before_num + 1; j ++ ) {
            item = new QStandardItem(QString::number(elements[i][j]));
            if (elements[i][j] == 0xFFFF)
                item = new QStandardItem(QString("∞"));
            item->setTextAlignment(Qt::AlignCenter);
            model_3->setItem(i, j, item);
        }
    }
    ui->after->setModel(model_3);

    model_2 = new QStandardItemModel;

    if(before_num == 0){
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
    }
    else{
        for (int i = 0 ; i < before_num ; i ++ ) {
            for (int j = 0 ; j < before_num; j ++ ) {
                item = new QStandardItem(QString::number(before_elements[i][j]));
                if (before_elements[i][j] == 0xFFFF)
                    item = new QStandardItem(QString("∞"));
                item->setTextAlignment(Qt::AlignCenter);
                model_2->setItem(i, j, item);
            }
        }
        ui->before->setModel(model_2);
    }

    model_4 = new QStandardItemModel;

    for (int i = 0 ; i < size; i ++ ) {
        for (int j = 0 ; j < size; j ++ ) {
            item = new QStandardItem(ss[i][j]);
            item->setTextAlignment(Qt::AlignCenter);
            model_4->setItem(i, j, item);
        }
    }
    ui->short_track->setModel(model_4);

    if(before_num + 1 == size)
        ui->next->setDisabled(true);
}
