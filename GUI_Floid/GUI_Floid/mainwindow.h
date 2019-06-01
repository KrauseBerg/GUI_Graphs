#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QStandardItem>
#include <QMainWindow>
#include <QModelIndex>

using namespace std;

struct duga{
    bool changed = false;
    int k;
    int x1, x2, x3, x4;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QStandardItemModel *model;
    QStandardItemModel *model_2;
    QStandardItemModel *model_3;
    QStandardItemModel *model_4;
    QVector <duga> vec_duga [100];
    QStandardItem *item_2;
    QStandardItem *item;
    QModelIndex index;
    QString **ss;
    int **elements;
    int **init_elements;
    int **before_elements;
    QString chars;
    int size;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_create_clicked();

    void on_generate_clicked();

    void on_next_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
