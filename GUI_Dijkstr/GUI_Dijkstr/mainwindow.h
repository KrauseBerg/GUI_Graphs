#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QStandardItem>
#include <iostream>
#include <QMainWindow>
#include <QModelIndex>

struct elems{
    int elem;
    bool color = false;
};

struct coords{
    int x;
    int y;
};

struct climb{
    int d = 0xFFFF;
    bool color = false;
    QString name;
    int name_int;
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_create_clicked();

    void on_generate_clicked();

    void on_next_clicked();

private:
    int a(QString a, QString b);
    QStandardItemModel *model;
    QStandardItemModel *model_2;
    QVector <coords> vec_mas;
    QVector <climb> apexes;
    QStandardItem *item_2;
    QStandardItem *item;
    QModelIndex index_1;
    QVector <elems> vec;
    Ui::MainWindow *ui;
    QString start;
    QString end;
    QString chars;
    int size;
};

#endif // MAINWINDOW_H
