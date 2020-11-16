#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <fstream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_downloadFile_clicked()
{
    /*
     * enum
     * map
     * switch case
     */

    QString path = QFileDialog::getOpenFileName(this, "Выбери файл", "", "*.sxf"); //подключение диалогового окна
    //    qDebug() << path;

    QFile file(path); // черех QT бтблиотеку подключаем файл

    if (file.open(QIODevice::ReadOnly)) //
    {
        while (!file.atEnd()) {
            QString str = file.readLine();
            QStringList sl = str.split(" ");
            if (sl.at(0) == ".SIT") {

            } else if (sl.at(0) == ".DAT") {

            } else if (sl.at(0) == ".OBJ") {
                if (sl.at(2).startsWith("DOT")) {
                    qDebug() << sl.at(2);
                    if (sl.at(0) == ".SEM") {
                        ui->textEdit_2->append(str);
                    }
                } else if (sl.at(2) == "SQR") {
                    if (sl.at(0) == ".SEM") {
                        ui->textEdit_3->append(str);
                    }
                }
            }
            ui->textEdit->append(str);
        }
        file.close(); // закрытие файла
    }
}
