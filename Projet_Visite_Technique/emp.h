#ifndef EMP_H
#define EMP_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextStream>
#include <QtCharts>
#include <QSqlError>

class Emp
{
public:
    void setid(int ident);
    void setnom(QString n);
    void setprenom(QString pr);
    void setemail(QString mail);
    void setmdp(QString motpasse);
    void setgrade(QString grad);
    void setsalaire(float sal);
    void setnbhs(int nbhs);

    int getid();
    QString getnom();
    QString getprenom();
    QString getemail();
    QString getgrade();
    float getsalaire();
    int getnbhs();
     bool ajouter();
     bool supprimer (int cin);
    bool verifier_grade(QString grade);
    bool verif_email(QString email);
     QSqlQueryModel* Rechercher(QString value );
    Emp();
    Emp(int id,QString nom,QString prenom,QString email,QString mdp,QString grade,float salaire,int nb_heure_supp);
    QSqlQueryModel * afficher();
    bool modifier(int id );
      QSqlQueryModel* Trier_croissant_emp ();
       QSqlQueryModel* Trier_decroissant_emp ();

       bool chercher_employe(QString id);
private:
    QString nom,prenom,email,mdp,grade;
    int id,nb_heure_supp;
    float salaire;
};

#endif // EMP_H
