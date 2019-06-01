#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->generate->setDisabled(true);
    ui->next->setDisabled(true);
    chars = "abcdefghijklmnopqrstuvwxyz";
}

MainWindow::~MainWindow(){
    delete ui;
}

//Функция для нахождения минимального из двух
int min(int a, int b){
    return a < b ? a : b;
}

//Функция для рассчитывания длины души между вершинами
int MainWindow::a(QString a, QString b){
    int int_a = 0, int_b = 0;
    for (int i = 0; i < chars.size(); i++) {
        if (chars[i] == a)
            int_a = i;
        if (chars[i] == b)
            int_b = i;
    }
    for (int i = 0; i < vec_mas.size(); i++) {
        if((vec_mas[i].x == int_a && vec_mas[i].y == int_b) ||
                (vec_mas[i].y == int_a && vec_mas[i].x == int_b))
            return vec[i].elem;
    }
    return 0xFFFF;
}


void MainWindow::on_create_clicked(){
    ui->next->setDisabled(true);
    model = new QStandardItemModel;
    model_2 = new QStandardItemModel;
    size = ui->size->text().toInt();
    for (int i = 0; i < size; i++) {
        item = new QStandardItem(QString(chars[i]));
        item_2 = new QStandardItem(QString(chars[i]));
        model->setHorizontalHeaderItem(i,item);
        model->setVerticalHeaderItem(i,item_2);
        for (int j = i; j < size; j++) {
            item = new QStandardItem(QString("0"));
            item_2 = new QStandardItem(QString("-"));
            item->setTextAlignment(Qt::AlignCenter);
            item_2->setTextAlignment(Qt::AlignCenter);
            model->setItem(i, j, item);
            model->setItem(j, i, item_2);
            if( i == j )
                model->setItem(i, j, item_2);
        }
    }
    ui->tableView->setModel(model);
    ui->generate->setDisabled(false);
}

void MainWindow::on_generate_clicked(){
    ui->next->setDisabled(false);
    int elem;
    int check;
    srand(static_cast<unsigned int>(time(nullptr))); //Для рандомизации от времени
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if(i == j)
                continue;
            else{
                check = rand()%2;
                if (check == 1){
                    elem = rand()%100; //Случайно (от 0 до 99)
                    item = new QStandardItem(QString::number(elem));
                    item_2 = new QStandardItem(QString::number(elem));
                }
                else {
                    item = new QStandardItem(QString("-"));
                    item_2 = new QStandardItem(QString("-"));
                }
                item->setTextAlignment(Qt::AlignCenter);
                model->setItem(i, j, item);
                model->setItem(j, i, item_2);
            }
        }
    }
    ui->tableView->setModel(model);
}

void MainWindow::on_next_clicked(){
    for (int i = 0; i < size; i++) {
        item = new QStandardItem(QString(chars[i]));
        item_2 = new QStandardItem(QString(chars[i]));
        model_2->setHorizontalHeaderItem(i,item);
        model_2->setVerticalHeaderItem(i,item_2);
    }
    climb apex_start;
    climb apex_end;
    climb apex;
    start = ui->start->text();
    end = ui->end->text();
    ///______________________Считывание_элементов_из_таблицы______________________________///
    elems elem;
    coords mas;
    for(int i = 0; i < size; i++){
        for (int j = i; j < size; j++){
            if(i == j)
                continue;
            else{
                elem.elem = ui->tableView->model()->itemData(ui->tableView->model()->index(i,j,QModelIndex())).value(0).toInt();
                item = new QStandardItem(QString::number(elem.elem));
                if (elem.elem == 0){
                    item = new QStandardItem(QString("-"));
                    elem.elem = 0xFFFF;
                }
                vec.push_back(elem);
                mas.x = i;
                mas.y = j;
                vec_mas.push_back(mas);
                item->setTextAlignment(Qt::AlignCenter);
                model->setItem(i,j, item);
            }
        }
    }
    ui->tableView->setModel(model);
    ///____________________________________________________________________________///
    for (int i = 0 ; i < chars.size(); i++) { //Добовляем каждой вершине её номер
        if(chars[i] == start)
            apex_start.name_int = i;
        if(chars[i] == end)
            apex_end.name_int = i;
    }
    apex_start.name = start;
    apex_start.color = true;
    apex_start.d = 0;
    apexes.push_back(apex_start); //Первый элемент этого вектора - вершина старта
    apex_end.name = end;
    apexes.push_back(apex_end); //Второй элемент этого вектора - вершина конца

    for (int i = 0; i < size; i++){ //Здесь заполнем вектор оставшимися вершинами
        if(chars[i] == start || chars[i] == end)
            continue;
        apex.name = chars[i];
        apex.name_int = i;
        apexes.push_back(apex);
    }

    QString current = start; //current - последняя из окрашенных вершин (y)
    int current_i = 0;       //Её индекс в векторе всех вершин
    climb apex_current;
    apex_current = apexes[current_i];

    while(apexes[1].color != true){
        int min_of_all_found = 0xFFFF + 1;
        for (int i = 1; i < size; i++) {
            if (apexes[i].color == true)
                continue;
            apexes[i].d = min(apexes[i].d, apex_current.d
                              + a(apex_current.name, apexes[i].name));
            min_of_all_found = min(apexes[i].d, min_of_all_found);   //Находим минимальный из всех найденных длин дуг
        }
        for (int i = 1; i < size; i++) {
            if(min_of_all_found == apexes[i].d){
                current_i = i;                               //Индекс текущей вершины
                apexes[i].color = true;                      //Окрасили вершину
                for (int j = 0; j < vec_mas.size(); j++) {
                    if (apexes[i].name_int == vec_mas[j].y){
                        for (int z = 0; z<size;z++) {
                            if(apexes[z].name_int == vec_mas[j].x && apexes[z].color == true && vec[j].elem!=0xFFFF && (apexes[i].d - apexes[z].d)==vec[j].elem){
                                vec[j].color = true;
                                item = new QStandardItem(QString::number(vec[j].elem));
                                item->setTextAlignment(Qt::AlignCenter);
                                model_2->setItem(vec_mas[j].x, vec_mas[j].y, item);
                                goto metka;
                            }
                        }
                    }
                    if (apexes[i].name_int == vec_mas[j].x){
                        for (int z = 0; z<size;z++) {
                            if(apexes[z].name_int == vec_mas[j].y && apexes[z].color == true && vec[j].elem!=0xFFFF && (apexes[i].d - apexes[z].d)==vec[j].elem){
                                vec[j].color = true;
                                item = new QStandardItem(QString::number(vec[j].elem));
                                item->setTextAlignment(Qt::AlignCenter);
                                model_2->setItem(vec_mas[j].x, vec_mas[j].y, item);
                                goto metka;
                            }
                        }
                    }
                }
            }
        }
        metka:
        ui->tableView_3->setModel(model_2);
        ui->min->setText(QString::number(min_of_all_found));
        apex_current = apexes[current_i];
        current = apex_current.name;
    }
}
