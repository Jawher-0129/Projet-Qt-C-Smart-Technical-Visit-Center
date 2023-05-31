#ifndef VEHICULE_H
#define VEHICULE_H
#include <QString>
#include <QSqlQuery>
#include<QtDebug>
#include <qmessagebox.h>
#include <QSqlQueryModel>
class vehicule
{
public:
    vehicule();
    vehicule(QString matricule,QString marque,QString type,float puissance,int age,int nbchevaux,QString carburant,QString cin,QByteArray imageV);
    QString getmatricule();
    QString getmarque();
    QString getype();
    QString getcarburant();
    int getage();
    int getnbchevaux();
    float getpuissance();
    QString getcin();

    void setmatricule(QString mat);
    void setmarque(QString marq);
    void settype(QString tp);
    void setpuissance(float puiss);
    void setnbchevaux(int nbchev);
    void setage(int ag);
    void setcarburant(QString carb);
    void setcin(QString c);


    bool chercher_client(QString cin);
    bool chercher_matricule(QString matricule);
    bool ajouter();
    bool supprimer(QString matricule);
    QSqlQueryModel * afficher();
    bool modifier(QString matricule);
    QSqlQueryModel * tri_croissant();
    QSqlQueryModel * tri_decroissant();
    QSqlQueryModel * rechercher(QString mat);
    QString encrypt(QString cin);
    QString decrypt(QString encrypted_cin);


private:
    QString matricule,marque,type,carburant,cin;
    int age,nbchevaux;
    float poids,puissance;
    QByteArray imageV;
};

#endif // VEHICULE_H
