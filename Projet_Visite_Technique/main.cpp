#include "mainwindow.h"
#include "connection.h"
#include <QtDebug>
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    bool test;
    QApplication a(argc, argv);
    connection c;
     test=c.createconnect();
    MainWindow w;
    if (test)
    {
    w.show();
    QMessageBox::information(nullptr,QObject::tr("database is open"),
    QObject::tr("connection successful.\n"
                "click cancel to exit.") ,QMessageBox::Cancel);  }


 else
 QMessageBox::critical(nullptr,QObject::tr("database is not open"),
                       QObject::tr("connection failed.\n"
                                   "click cancel to exit.") ,QMessageBox::Cancel);
    return a.exec();
}
