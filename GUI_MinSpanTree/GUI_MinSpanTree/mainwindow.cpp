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
    size = ui->size->text().toInt();
    for (int i = 0; i < size; i++) {
        item = new QStandardItem(QString(chars[i]));
        item_2 = new QStandardItem(QString(chars[i]));
        model->setHorizontalHeaderItem(i,item);
        model->setVerticalHeaderItem(i,item_2);
        for (int j = 0; j < size; j++) {
            item = new QStandardItem(QString("0"));
            if(i == j)
                item = new QStandardItem(QString("x"));
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(i, j, item);
        }
    }
    ui->tableView->setModel(model);
    ui->generate->setDisabled(false);
}

void MainWindow::on_generate_clicked(){
    ui->next->setDisabled(false);
    int elem;
    srand(static_cast<unsigned int>(time(nullptr))); //Для рандомизации от времени
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if(i == j)
                continue;
            else{
                elem = rand()%100; //Случайно (от 0 до 99)
                item = new QStandardItem(QString::number(elem));
                item_2 = new QStandardItem(QString::number(elem));
                item->setTextAlignment(Qt::AlignCenter);
                model->setItem(i, j, item);
                model->setItem(j,i,item_2);
            }
        }
    }
    ui->tableView->setModel(model);
}

void MainWindow::on_next_clicked(){
    char_mas mas;
    for(int i = 0; i < size; i++){
        for (int j = i; j < size; j++){
            if(i == j)
                continue;
            else{
                index_1 = ui->tableView->model()->index(i,j,QModelIndex());
                myData_1 = ui->tableView->model()->data(index_1, Qt::DisplayRole);

                if (i == 0 && j == 1) {
                    vec.push_back(myData_1.toInt());
                    mas.x = i;
                    mas.y = j;
                    vec_mas.push_back(mas);
                }
                else{
                    int s_z = vec.size();
                    for (int z = 0; z < s_z; z ++ ){
                        if (vec[z] < myData_1.toInt()){
                            if(z == vec.size()-1){
                                vec.push_back(myData_1.toInt());
                                mas.x = i;
                                mas.y = j;
                                vec_mas.push_back(mas);
                            }
                        }
                        else{
                            vec.insert(z,myData_1.toInt());
                            mas.x = i;
                            mas.y = j;
                            vec_mas.insert(z,mas);
                            break;
                        }
                    }
                }

                item = new QStandardItem(QString::number(myData_1.toInt()));
                item->setTextAlignment(Qt::AlignCenter);
                model->setItem(i,j, item);
            }
        }
    }
    ui->tableView->setModel(model);



    char_mas bad_mas;
    model_2 = new QStandardItemModel;
    buket_1.clear();
    buket_2.clear();
    buket_3.clear();
    for (int i = 0; i < size*(size-1)/2; i++) {
        ss << "(" << chars[vec_mas[i].x] << "," << chars[vec_mas[i].y] << ")";
        if(buket_1.contains(chars[vec_mas[i].x]) && buket_1.contains(chars[vec_mas[i].y])){
            item_2 = new QStandardItem("красный");
            bad_mas.x = vec_mas[i].x;
            bad_mas.y = vec_mas[i].y;
            bad_vec_mas.push_back(bad_mas);
        }
        if(buket_1.contains(chars[vec_mas[i].x]) && buket_2.contains(chars[vec_mas[i].y])){
            for (int j = 0; j < buket_2.size(); j++) {
                buket_1.push_back(buket_2[j]);
            }
            buket_2.clear();
            item_2 = new QStandardItem("синий");
        }
        if(buket_1.contains(chars[vec_mas[i].x]) && !buket_2.contains(chars[vec_mas[i].y]) && !buket_1.contains(chars[vec_mas[i].y])){
            buket_1.push_back(chars[vec_mas[i].y]);
            item_2 = new QStandardItem("синий");
        }
        if(buket_2.contains(chars[vec_mas[i].x]) && buket_1.contains(chars[vec_mas[i].y])){
            for (int j = 0; j < buket_2.size(); j++) {
                buket_1.push_back(buket_2[j]);
            }
            buket_2.clear();
            item_2 = new QStandardItem("синий");
        }
        if(buket_2.contains(chars[vec_mas[i].x]) && buket_2.contains(chars[vec_mas[i].y])){
            bad_mas.x = vec_mas[i].x;
            bad_mas.y = vec_mas[i].y;
            bad_vec_mas.push_back(bad_mas);
            item_2 = new QStandardItem("красный");
        }
        if(buket_2.contains(chars[vec_mas[i].x]) && !buket_2.contains(chars[vec_mas[i].y])  && !buket_1.contains(chars[vec_mas[i].y])){
            buket_2.push_back(chars[vec_mas[i].y]);
            item_2 = new QStandardItem("синий");
        }
        if(buket_1.contains(chars[vec_mas[i].y]) && !buket_2.contains(chars[vec_mas[i].x]) && !buket_1.contains(chars[vec_mas[i].x])){
            buket_1.push_back(chars[vec_mas[i].x]);
            item_2 = new QStandardItem("синий");
        }
        if(buket_2.contains(chars[vec_mas[i].y]) && !buket_2.contains(chars[vec_mas[i].x]) && !buket_1.contains(chars[vec_mas[i].x])){
            buket_2.push_back(chars[vec_mas[i].x]);
            item_2 = new QStandardItem("синий");
        }
        if(!buket_2.contains(chars[vec_mas[i].y]) && !buket_1.contains(chars[vec_mas[i].y]) && !buket_2.contains(chars[vec_mas[i].x]) && !buket_1.contains(chars[vec_mas[i].x])){
            if(buket_1.size() == 0){
                buket_1.push_back(chars[vec_mas[i].y]);
                buket_1.push_back(chars[vec_mas[i].x]);
                item_2 = new QStandardItem("синий");
            }
            else if (buket_2.size()==0) {
                buket_2.push_back(chars[vec_mas[i].y]);
                buket_2.push_back(chars[vec_mas[i].x]);
                item_2 = new QStandardItem("синий");
            }
            else if (buket_3.size() == 0) {
                buket_3.push_back(chars[vec_mas[i].y]);
                buket_3.push_back(chars[vec_mas[i].x]);
                item_2 = new QStandardItem("синий");
            }
        }
        for(int j = 0; j < buket_1.size(); j++){
            ss_buk_1 << buket_1[j];
        }
        if (buket_2.size() == 0)
            item_buk_2 = new QStandardItem("Пусто");
        else{
            for (int j = 0; j < buket_2.size(); j++) {
                ss_buk_2 << buket_2[j];
            }
            item_buk_2 = new QStandardItem(QString::fromStdString(ss_buk_2.str()));
        }
        if (buket_3.size() == 0)
            item_buk_3 = new QStandardItem("Пусто");
        else{
            for (int j = 0; j < buket_3.size(); j++) {
                ss_buk_3 << buket_3[j];
            }
            item_buk_3 = new QStandardItem(QString::fromStdString(ss_buk_3.str()));
        }
        item = new QStandardItem(QString::fromStdString(ss.str()));
        item_buk_1 = new QStandardItem(QString::fromStdString(ss_buk_1.str()));
        model_2->setItem(i,0,item);
        model_2->setItem(i,1,item_2);
        model_2->setItem(i,2,item_buk_1);
        model_2->setItem(i,3,item_buk_2);
        model_2->setItem(i,4,item_buk_3);
        ss.str("");
        ss_buk_1.str("");
        ss_buk_2.str("");
        ss_buk_3.str("");
        if(buket_1.size() == size){
            current_i = i;
            break;
        }

    }
    ui->tableView_2->setModel(model_2);
    item_3 = new QStandardItem("рёбра");
    item_4 = new QStandardItem("цвет");

    model_2->setHorizontalHeaderItem(0,item_3);
    model_2->setHorizontalHeaderItem(1,item_4);
    for(int i=2;i<5;i++){
        item_5 = new QStandardItem("Букет №" + QString::number(i-1));
        model_2->setHorizontalHeaderItem(i,item_5);
    }
    model = new QStandardItemModel;
    for (int i = 0; i < size; i++) {
        item = new QStandardItem(QString(chars[i]));
        item_2 = new QStandardItem(QString(chars[i]));
        model->setHorizontalHeaderItem(i,item);
        model->setVerticalHeaderItem(i,item_2);
        for (int j = 0; j < size; j++) {
            item = new QStandardItem(QString("0"));
            if(i == j)
                item = new QStandardItem(QString("x"));
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(i, j, item);
        }
    }
    for (int i = 0; i < vec.size(); i ++) {
        item = new QStandardItem(QString::number(vec[i]));
        item_2 = new QStandardItem(QString::number(vec[i]));
        if(i > current_i){
            item = new QStandardItem(QString("x"));
            item_2 = new QStandardItem(QString("x"));
        }
        item->setTextAlignment(Qt::AlignCenter);
        model->setItem(vec_mas[i].x, vec_mas[i].y, item);
        model->setItem(vec_mas[i].y, vec_mas[i].x, item_2);
    }
    for (int i = 0; i < bad_vec_mas.size(); i ++) {
        item = new QStandardItem(QString("x"));
        item_2 = new QStandardItem(QString("x"));
        model->setItem(bad_vec_mas[i].x, bad_vec_mas[i].y, item);
        model->setItem(bad_vec_mas[i].y, bad_vec_mas[i].x, item_2);
    }
    ui->tableView_3->setModel(model);
}
