#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QStandardItemModel"
#include <QModelIndex>
#include "QStandardItem"
#include <QModelIndex>
#include <QVector>
#include <sstream>
#include <ctime>
#include <iostream>

using namespace std;

struct char_mas{
    int x, y;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_create_clicked();

    void on_generate_clicked();

    void on_next_clicked();

private:
    string chars = "abcdefghijk";
    int size;
    int current_i;
    QVector<int>vec;
    QVector<char_mas>vec_mas;
    QVector<char_mas>bad_vec_mas;
    QVector<char>buket_1;
    QVector<char>buket_2;
    QVector<char>buket_3;
    QStandardItem *item;
    QStandardItem *item_2;
    QStandardItem *item_3;
    QStandardItem *item_4;
    QStandardItem *item_5;
    QStandardItem *item_buk_1;
    QStandardItem *item_buk_2;
    QStandardItem *item_buk_3;
    QStandardItemModel *model;
    QStandardItemModel *model_2;
    QModelIndex index_1;
    QVariant myData_1;
    stringstream ss;
    stringstream ss_buk_1;
    stringstream ss_buk_2;
    stringstream ss_buk_3;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
