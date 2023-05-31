#ifndef RECLAMATION_H
#define RECLAMATION_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QLineEdit>
#include <QValidator>
#include <QRegExp>
#include <QRegExpValidator>


class reclamation
{
public:
    reclamation();
    reclamation(QString nom_client,QString prenom_client,QString email_client,QString type,QString cin_client,int etat,QString message);
    void setnom_client(QString n);
    void setprenom_client(QString pr);
    void setemail_client(QString em);
    void settype(QString typee);
    void setcin_client(QString c);

    QString getcin_client();
    QString getnom_client();
    QString getprenom_client();
    QString getemail_client();
    QString gettype();


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int num);
    bool modifier(int num);


    bool chercher_reclamation(int num);
    bool verif_email(QString email);
    QSqlQueryModel * rechercher_reclamation_numero(QString valeur);
    QString encrypt(QString cin);
     QString decrypt(QString encrypted_cin);
     bool chercher_client(QString cin);
int return_etat(int data);

     QSqlQueryModel *triC();
     QSqlQueryModel *triDec();
private:
    QString nom_client,prenom_client,email_client,type,cin_client,message;
    int etat;
};

#endif // RECLAMATION_H


