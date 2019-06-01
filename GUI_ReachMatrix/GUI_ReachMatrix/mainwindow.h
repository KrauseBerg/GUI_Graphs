#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QStandardItemModel"
#include "QStandardItem"
#include <QModelIndex>
#include <sstream>
#include <ctime>

using namespace std;

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
    QModelIndex index_1, index_2;
    QVariant myData_1, myData_2;
    int size;
    stringstream ss;
    QStandardItemModel *model;
    QStandardItemModel *model_2;
    QStandardItem *item;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
