#ifndef VISITE_H
#define VISITE_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <qmessagebox.h>
#include <QtDebug>
#include <QDate>
#include <QSqlError>



class visite
{
public:
       void setnumero(int num);
       void setdate_visite(QString datev );
       void setresultat(QString res);
       void setmontant(float mont);
       void setnb_visite(int nbvisite);
       void setheure_entree(int he);
       void setheure_sortie(int hs);
       void setid_employe(int idemp);
       void setmatricule_vehicule(QString matv );

       int  getnumero();
       QString getdate_visite();
       QString getresultat();
       float getmontant();
       int getnb_visite();
       int getheureentree();
       int getheuresortie();
       int getid_employe();
       QString getmatricule_vehicule();


       visite();
       visite(QString date,QString resultat,float montant,int nb_visite,int heure_entree,int heure_sortie,int id,QString matricule_vehicule);
       bool chercher_visite_1(int numero);
       bool supprimer(QString matricule);
       bool ajouter();
       bool modifier(int numero);
       bool chercher_visite_cin(int cin);
       QSqlQueryModel *afficher();
       QSqlQueryModel *afficher_f();
       QSqlQueryModel *triC();
       QSqlQueryModel *triDec();
       QSqlQueryModel * chercher_visite(int numero);
       QSqlQueryModel * chercher_visite_2(int cin);
       float calculerremise(float montant, int nb_visites ,int numero);
         bool update_remise(int numero ,float montant);
        //bool visite::chercher_id_c(QString id);
   private:
       QString date,resultat,matricule_vehicule,num;
       int nb_visite,heure_entree,heure_sortie,id;
       float montant;
   };

#endif // VISITE_H
