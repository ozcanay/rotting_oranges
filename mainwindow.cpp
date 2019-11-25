#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QDebug>
#include <QRandomGenerator>
#include <QTimer>

#include "colordelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ColorDelegate* delegate = new ColorDelegate;
    ui->tableView->setItemDelegate(delegate);

    QRandomGenerator random_generator;
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStandardItemModel* model = new QStandardItemModel(10, 10);
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            double val = random_generator.generateDouble();
            QString orange_status;

            if(val > 0.0 && val < 0.2) {
                orange_status = "2";
            } else if(val >= 0.2 && val < 0.9) {
                orange_status = "1";
            } else {
                orange_status = "0";
            }

            QStandardItem *item = new QStandardItem(orange_status);
            model->setItem(row, column, item);
        }
    }

    QTimer *timer = new QTimer(this);
    timer->start(1000);


    connect(timer, &QTimer::timeout, this, [model, timer]{
        bool found = false;
        std::vector<QStandardItem*> items;

        for (int row = 0; row < model->rowCount() && !found; ++row) {
            for (int column = 0; column < model->columnCount() && !found; ++column) {
                QStandardItem* item = model->item(row, column);
                if(item->text() == "2") {
                    items.push_back(item);
                }
            }
        }

        for(auto item : items) {
            QStandardItem *rotten_item = new QStandardItem("2");
            if(item->column() > 0)
                model->setItem(item->row(), item->column() - 1, rotten_item);
            if(item->row() > 0)
                model->setItem(item->row() - 1, item->column(), rotten_item);
            if(item->column() < model->columnCount() - 1)
                model->setItem(item->row(), item->column() + 1, rotten_item);
            if(item->row() < model->rowCount() - 1)
                model->setItem(item->row() + 1, item->column(), rotten_item);
        }
    });

    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
