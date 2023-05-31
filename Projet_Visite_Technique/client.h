#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <qmessagebox.h>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <algorithm>
#include <QVariant>
#include <QtSql>
#include <QPdfWriter>
#include <QPainter>
#include <QTableWidget>
#include <QHeaderView>
#include <QLineEdit>
#include <QValidator>
#include <QRegExp>
#include <QRegExpValidator>
#include <QStandardItemModel>
#include <QLabel>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtPrintSupport/QPrinter>
#include <QLineSeries>

//mail
#include <QByteArray>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslSocket>

#include <QtCore/QTextStream>

#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
//for crypting


class client
{
public:
    client();

    client(QString cin,QString nom,QString prenom,QString adress,QString date,QString email,QString tel,QString sexe);

    QString getnom();
    QString getprenom();
    QString getadress();
    QString getcin();
    QString getemail();
    QString getsexe();
    QString gettel();
    QString getdate();

    void setnom(QString nom);
    void setprenom(QString prenom);
    void setadress(QString adress);
    void setcin(QString cin);
    void setemail(QString email);
    void setsexe(QString sexe);
    void settel(QString tel);
    void setdate(QString date);

    bool chercher_client(QString cin);
    bool ajouter_clilent();
    bool supprimer_client(QString cin);
    bool modifier_client(QString cin);

    bool isValidEmail(QString email);


   // QSqlQueryModel * afficher_client();
    QList<client> afficher_client();
    QStandardItemModel *afficher_tous_client();
    QStandardItemModel * afficher_client_tri_dec();
    QStandardItemModel * afficher_client_tri_cor();
    QStandardItemModel* rechercher_client(QString cin);
    void    afficher_dycrpt();


   void   client_affiche_stats();

   //void   sendEmail(QString email,QString subject,QString text);
    QString encrypt(QString cin);
    QString decrypt(QString encrypted_cin);

private:
       QString cin,nom,prenom,adress,date,email,tel,sexe;
};

#endif // CLIENT_H
