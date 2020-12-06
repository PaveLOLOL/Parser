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


class Element { // это один объект класса содержащий в себе информацию о координате центра объекта, широту и долготу и тип описанного объекта
public:
//        void setPoligonCenter (QString poligon_center){
//            this->poligon_center = poligon_center;
//        }
//        void setPoligonAbris (QString poligon_abris){
//            this->poligon_abris = poligon_abris;
//        }
//        void setType (QString type){
//            this->type = type;
//        }
    QString getType (){
        return type;
    }

    QString getPoligonAbris (){
        return poligon_abris;
    }

    QString getPoligonCenter (){
        return poligon_center;
    }
private:
    QString poligon_center; // широта и долгота (7124,7125)
    QString poligon_abris; // центр объекта (вид 7114, 7115) дальше 7 значное число B L - (xy) Топографическая
    QString type; // 7120
};

class Obj {
public:
    QVector<Element> array; // элементов 35 (объектов)
private:
};

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
                ui->textEdit->append(str);
            } else if (sl.at(0).contains('P')) {
                ui->textEdit_4->append(str);
            } else if (sl.at(0) == ".DAT") {
                ui->textEdit_7->append(str);
            } else if (sl.at(0) == ".OBJ") {
                if (sl.at(2).startsWith("DOT\r\n")) {
                    ui->textEdit_2->append(str);
                    //                    QString str2 = file.readLine();
                    //bool ok;
                    int counterOfPosithion = file.readLine().toInt();
                    for (int i = 0; i < counterOfPosithion; i++) {
                        QString posithon = file.readLine();
                        QStringList sl = posithon.split(" ");
                        ui->textEdit_2->append(posithon);
                    }
                    QString str = file.readLine();
                    QStringList sl = str.split(" ");
                    if (sl.at(0).startsWith(".SEM")) {
                        ui->textEdit_2->append(sl.at(0));
                        int counterOfPosithion = sl.at(1).toInt();
                        for (int i = 0; i < counterOfPosithion; i++) {
                            QString posithon = file.readLine();
                            QStringList sl = posithon.split(" ");
                            ui->textEdit_2->append(posithon);
                        }
                    }
                } else if (sl.at(2) == "SQR\r\n") {
                    ui->textEdit_3->append(str);
                    QString str3 = file.readLine();
                    //bool ok;
                    int counterOfPosithion = str3.toInt();
                    for (int i = 0; i < counterOfPosithion; i++) {
                        QString posithon = file.readLine();
                        QStringList sl = posithon.split(" ");

                        ui->textEdit_3->append(posithon);
                    }
                    QString str = file.readLine();
                    QStringList sl = str.split(" ");
                    if (sl.at(0).startsWith(".SEM")) {
                        ui->textEdit_3->append(sl.at(0));
                        int counterOfPosithion = sl.at(1).toInt();
                        for (int i = 0; i < counterOfPosithion; i++) {
                            QString posithon = file.readLine();
                            QStringList sl = posithon.split(" ");
                            ui->textEdit_3->append(posithon);
                        }
                    }
                }
            }
        }

        file.close(); // закрытие файла
    }
}
