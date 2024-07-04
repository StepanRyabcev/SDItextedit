#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->action_txt, &QAction::triggered, this, MainWindow::save_txt);
    QObject::connect(ui->action_txt_2, &QAction::triggered, this, MainWindow::load_txt);
    QObject::connect(ui->action_bin, &QAction::triggered, this, MainWindow::save_bin);
    QObject::connect(ui->action_bin_2, &QAction::triggered, this, MainWindow::load_bin);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save_txt()
{
    QString fileName = QFileDialog::getSaveFileName(this, ("Open File"), "/home", ("txt File(*.txt)"));
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream write(&file);
        write << ui->plainTextEdit->toPlainText();
        file.close();
    }
}

void MainWindow::load_txt()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("txt File(*.txt)"));
    QFile file(fileName);
    QString data;
    if (file.open(QFile::ReadOnly))
    {
        data = file.readAll();
        file.close();
        ui->plainTextEdit->setPlainText(data);
    }
}

void MainWindow::save_bin()
{
    QString fileName = QFileDialog::getSaveFileName(this, ("Open File"), "/home", ("Binary File(*.bin)"));
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        QByteArray byteArray = ui->plainTextEdit->toPlainText().toUtf8();
        stream << byteArray;
        file.close();
    }
}

void MainWindow::load_bin()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("Binary File(*.bin)"));
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        QString data;
        QByteArray byteArray;
        while(!stream.atEnd())
        {
            stream >> byteArray;
            data = QString::fromUtf8(byteArray);
            ui->plainTextEdit->setPlainText(data);
        }
        file.close();
    }
}
