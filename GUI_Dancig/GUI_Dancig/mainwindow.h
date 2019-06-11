#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QStandardItem>
#include <QMainWindow>
#include <QModelIndex>

struct vspom_strucr{
    int x;
    int y;
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
    void on_generate_clicked();

    void on_create_clicked();

    void on_next_clicked();

private:
    QStandardItemModel *model;
    QStandardItemModel *model_2;
    QStandardItemModel *model_3;
    QStandardItemModel *model_4;
    QVector <vspom_strucr> vec_duga;
    QString **ss;
    QStandardItem *item_2;
    QStandardItem *item;
    QModelIndex index;
    int **elements;
    int **init_elements;
    int **before_elements;
    int **vspom_matrix;
    QString chars;
    int size;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
