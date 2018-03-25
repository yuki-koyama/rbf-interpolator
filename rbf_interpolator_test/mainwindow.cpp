#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

using std::vector;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_add_clicked()
{
    vector<double> x;
    x.push_back(ui->lineEdit_x1->text().toDouble());
    x.push_back(ui->lineEdit_x2->text().toDouble());
    double y = ui->lineEdit_y->text().toDouble();

    ui->widget->interpolator.addCenterPoint(y, x);
    ui->widget->interpolator.computeWeights();

    ui->lineEdit_x1->clear();
    ui->lineEdit_x2->clear();
    ui->lineEdit_y->clear();

    ui->lineEdit_x1->setFocus();

    ui->widget->repaint();
    repaint();
}

void MainWindow::on_pushButton_reset_clicked()
{
    ui->widget->interpolator.reset();

    ui->lineEdit_x1->clear();
    ui->lineEdit_x2->clear();
    ui->lineEdit_y->clear();

    ui->lineEdit_x1->setFocus();

    ui->widget->repaint();
    repaint();
}

