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

class Viewer {
public:
    void Show() {
        //QString path = QFileDialog::getOpenFileName(this, "Выбери файл", "", "*.sxf"); //подключение диалогового окна
        //    qDebug() << path;
    };
};

class Dot {
public:
    Dot(double aX, double aY)
    {
        x = aX;
        y = aY;
    }
    double x;
    double y;
};

class Sem {
public:
    Sem(QString aCode, QString aValue)
    {
        code = aCode;
        value = aValue;
    }
    QString code;
    QString value;
};

class Element { // это один объект класса содержащий в себе информацию о координате центра объекта, широту и долготу и тип описанного объекта
public:
    Element()
    {
    }

    QString getType()
    {
        return type;
    }

    void setType(int aType)
    {
        type = aType;
    }

    void AddDotToList(double ax, double ay)
    {
        double x = ax;
        double y = ay;
    }

    void AddSemToList(QString aCode, QString aValue)
    {
    }

    //TODO - add setters, getters
private:
    QString type; // 7120
    QList<Dot> dotes;
    //QString sem; // центр объекта (вид 7114, 7115) дальше 7 значное число B L - (xy) Топографическая
    QList<Sem> sems;
};

class Reader {
private:
    QVector<Element> array;

public:
    void ReadFromFile(QString path)
    {
        QFile file(path);
        if (file.open(QIODevice::ReadOnly)) //
        {
            while (!file.atEnd()) {
                QString str = file.readLine();
                Element* tempElement = new Element;
                QStringList sl = str.split(" ");
                if (sl.at(0) == ".SIT") {
                    // ui->textEdit->append(str);
                } else if (sl.at(0).contains('P')) {
                    // ui->textEdit_4->append(str);
                } else if (sl.at(0) == ".DAT") {
                    //DAT - колличество элементов
                    // ui->textEdit_7->append(str);
                } else if (sl.at(0) == ".OBJ") {
                    if (sl.at(2).startsWith("DOT\r\n")) {
                        // ui->textEdit_2->append(str);
                        //                    QString str2 = file.readLine();
                        //bool ok;
                        int counterOfPosithion = file.readLine().toInt();
                        for (int i = 0; i < counterOfPosithion; i++) {
                            QString posithon = file.readLine();
                            QStringList sl = posithon.split(" ");

                            //sl.at()
                            int temp = file.readLine().toInt();
                            QList<int> listToConvert;
                            listToConvert.append(temp);

                            //    ui->textEdit_2->append(posithon);
                        }
                        QString str = file.readLine();
                        QStringList sl = str.split(" ");
                        if (sl.at(0).startsWith(".SEM")) {
                            //  ui->textEdit_2->append(sl.at(0));
                            int counterOfPosithion = sl.at(1).toInt();
                            for (int i = 0; i < counterOfPosithion; i++) {
                                QString posithon = file.readLine();
                                QStringList sl = posithon.split(" ");
                                // ui->textEdit_2->append(posithon);
                                // temp->setType()
                            }
                        }
                    } else if (sl.at(2) == "SQR\r\n") {
                        //   ui->textEdit_3->append(str);
                        QString str3 = file.readLine();
                        //bool ok;
                        int counterOfPosithion = str3.toInt();
                        for (int i = 0; i < counterOfPosithion; i++) {
                            QString posithon = file.readLine();
                            QStringList sl = posithon.split(" ");

                            //    ui->textEdit_3->append(posithon);
                        }
                        QString str = file.readLine();
                        QStringList sl = str.split(" ");
                        if (sl.at(0).startsWith(".SEM")) {
                            //   ui->textEdit_3->append(sl.at(0));
                            int counterOfPosithion = sl.at(1).toInt();
                            for (int i = 0; i < counterOfPosithion; i++) {
                                QString posithon = file.readLine();
                                QStringList sl = posithon.split(" ");
                                //  ui->textEdit_3->append(posithon);
                            }
                        }
                    }
                }
            }

            file.close(); // закрытие файла
        }
    }
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

//ридер вызвать и геттер
