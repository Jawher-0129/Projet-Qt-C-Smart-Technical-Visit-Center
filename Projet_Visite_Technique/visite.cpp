#include "visite.h"
#include <QPdfWriter>
#include <QPainter>


visite::visite()
{
   date="";
   resultat="";
   montant=0;
   nb_visite=0;
   heure_entree=0;
   heure_sortie=0;
   id=0;
   matricule_vehicule="";
   num="";
}
visite::visite(QString date,QString resultat,float montant,int nb_visite,int heure_entree,int heure_sortie,int id,QString matricule_vehicule)
{
    this->date=date;
    this->resultat=resultat;
    this->montant=montant;
    this->nb_visite=nb_visite;
    this->heure_entree=heure_entree;
    this->heure_sortie=heure_sortie;
    this->id=id;
    this->matricule_vehicule=matricule_vehicule;
}
QString visite::getdate_visite()
{
    return date;
}
QString visite::getresultat()
{
    return resultat;
}
int visite::getid_employe()
{
    return id;
}
QString visite::getmatricule_vehicule()
{
    return matricule_vehicule;
}

int visite::getnb_visite()
{
    return nb_visite;
}
int visite::getheureentree()
{
    return heure_entree;
}
int visite::getheuresortie()
{
    return heure_sortie;
}

float visite::getmontant()
{
    return montant;
}

void visite::setmontant(float mont)
{
    montant=mont;
}
void visite::setresultat(QString res)
{
    resultat=res;
}
void visite::setnb_visite(int nbvisite)
{
    nb_visite=nbvisite;
}
void visite::setid_employe(int idemp)
{
    id=idemp;
}
void visite::setdate_visite(QString datev)
{
    date=datev;
}
void visite::setheure_entree(int he)
{
    heure_entree=he;
}
void visite::setheure_sortie(int hs){

   heure_sortie=hs;
}
void visite::setmatricule_vehicule(QString matv){
    matricule_vehicule=matv;
}


bool visite::ajouter()
{

    QString id_str=QString::number(id);
    QString montant_str=QString::number(montant);

    QSqlQuery query;

    query.prepare("INSERT INTO VISITES(DATE_VISITE,RESULTAT,MONTANT,NB_VISITE,HEURE_ENTREE,HEURE_SORTIE,ID_EMPLOYE,MATRICULE_VEHICULE)" "VALUES(:date,:res,:montant,:nbvisite,:he,:hs,:id,:mat)");
    query.bindValue(":num",num);
    query.bindValue(":date",date);
    query.bindValue(":res",resultat);
    query.bindValue(":montant",montant_str);
    query.bindValue(":nbvisite",nb_visite);
    query.bindValue(":he",heure_entree);
    query.bindValue(":hs",heure_sortie);
    query.bindValue(":id",id_str);
    query.bindValue(":mat",matricule_vehicule);

    return query.exec();

}

QSqlQueryModel * visite::afficher()
{

        QSqlQueryModel *model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM VISITES");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMERO"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_VISITE"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("RESULTAT"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("MONTANT"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("NB_VISITE"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("HEURE_ENTRE"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("HEURE_SORTIE"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("ID_EMPLOYE"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("MATRICULE_VEHICULE"));
        return model;

}

QSqlQueryModel * visite::afficher_f()
{

        QSqlQueryModel *model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM VISITES");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMERO"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_VISITE"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("RESULTAT"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("MONTANT"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("NB_VISITE"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("HEURE_ENTRE"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("HEURE_SORTIE"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID_EMPLOYE"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("MATRICULE_VEHICULE"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("NOM"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("PRENOM"));
        return model;

}




    bool visite::supprimer(QString matricule){

        QSqlQuery query;


             query.prepare("DELETE FROM VISITES WHERE NUMERO=:matricule");
             query.bindValue(":matricule",matricule);
             return query.exec();
    }



bool visite::modifier(int numero){

        QSqlQuery query;
        QString montant_str=QString::number(montant);
        QString id_str=QString::number(id);
        QString  nb_visite_str=QString::number(nb_visite);
        QString  heure_entree_str=QString::number(heure_entree);
        QString  heure_sortie_str=QString::number(heure_sortie);

        if(nb_visite_str!="")
            {
                query.prepare("UPDATE VISITES SET NB_VISITE=:nb_visite WHERE NUMERO=:numero");
                   query.bindValue(":numero",numero);
                   query.bindValue(":nb_visite",nb_visite_str);
                   query.exec();

            }
            if(montant_str!="")
            {
                query.prepare("UPDATE VISITES SET   MONTANT=:montant WHERE NUMERO=:numero");
                query.bindValue(":numero",numero);
                query.bindValue(":montant",montant_str);
                query.exec();

            }

            if(resultat!="")
            {
                query.prepare("UPDATE VISITES SET RESULTAT=:resultat WHERE NUMERO=:numero");
                query.bindValue(":numero",numero);
                query.bindValue(":resultat",resultat);
                query.exec();

            }

            if(heure_entree_str!="")
            {
                query.prepare("UPDATE VISITES SET HEURE_ENTREE=:heure_entree WHERE NUMERO=:numero");
                query.bindValue(":numero",numero);
                query.bindValue(":heure_entree",heure_entree_str);
                query.exec();

            }

            if(heure_sortie_str!="")
            {
                query.prepare("UPDATE VISITES SET HEURE_SORTIE=:heure_sortie WHERE NUMERO=:numero");
                query.bindValue(":numero",numero);
                query.bindValue(":heure_sortie",heure_sortie_str);
                query.exec();

            }

            if(date!="")
            {
                query.prepare("UPDATE VISITES SET DATE_VISITE=:date WHERE NUMERO=:numero");
                query.bindValue(":numero",numero);
                query.bindValue(":date",date);
                query.exec();
            }

            return query.exec();

    }

    bool visite::chercher_visite_1(int numero)
    {
        QSqlQuery query;

        query.prepare("SELECT * FROM VISITES WHERE NUMERO=:numero");
        query.bindValue(":numero",numero);

        if(query.exec() && query.next())
            return true;
        else
            return false;

    }
    bool visite::chercher_visite_cin(int cin)
    {
        QSqlQuery query;

        query.prepare("SELECT * FROM VISITES WHERE CIN_CLIENTS=:cin");
        query.bindValue(":cin",cin);

        if(query.exec() && query.next())
            return true;
        else
            return false;

    }


    QSqlQueryModel * visite::triC()
     {
        QSqlQueryModel *model=new QSqlQueryModel();
       QSqlQuery *q = new QSqlQuery();

        q->prepare("SELECT * FROM VISITES ORDER BY DATE_VISITE ASC");
        q->exec();
        model->setQuery(*q);
        return model;
     }

     QSqlQueryModel * visite::triDec()
     {
        QSqlQueryModel *model=new QSqlQueryModel();
       QSqlQuery *q = new QSqlQuery();

        q->prepare("SELECT * FROM VISITES ORDER BY DATE_VISITE DESC");
        q->exec();
        model->setQuery(*q);
        return model;
     }
     QSqlQueryModel * visite::chercher_visite(int numero)
      {
         QSqlQuery query;
         QString numero_str=QString::number(numero);
          QSqlQueryModel *model=new QSqlQueryModel();
          model ->setQuery("SELECT * FROM VISITES WHERE NUMERO LIKE '"+numero_str+"%'");
          return model;


      }

     QSqlQueryModel * visite::chercher_visite_2(int cin)
      {
          QSqlQuery query;

          QString cin_str=QString::number(cin);
          QSqlQueryModel *model=new QSqlQueryModel();
          //model ->setQuery("SELECT * FROM VISITES WHERE CIN_CLIENTS LIKE '"+cin_str+"%'");

          model->setQuery("SELECT DISTINCT VISITES.CIN_CLIENTS, CLIENTS.NOM, CLIENTS.PRENOM, VISITES.NB_VISITE, VISITES.MATRICULE_VEHICULE, VISITES.POINT "
                          "FROM VISITES INNER JOIN CLIENTS ON VISITES.CIN_CLIENTS = CLIENTS.CIN "
                          "WHERE VISITES.CIN_CLIENTS LIKE '%" + cin_str + "%'");
          return model;
}


     float visite::calculerremise(float montant, int nb_visites , int numero) {


         float remise = 0;

         QString num_str=QString::number(numero);
         QString montant_str=QString::number(montant);

         if (nb_visites >= 5 && nb_visites <= 10) {
             remise = 0.1;
         } else if (nb_visites >= 11 && nb_visites <= 20) {
             remise = 0.2;
         } else if (nb_visites >= 21) {
             remise = 0.25;
         } else {
             remise = 0.0;
         }


          montant = montant * (1.0 - remise);


         return montant;
     }

     bool visite::update_remise(int numero ,float montant){


         QString num_str=QString::number(numero);
         QString montant_str=QString::number(montant);

         QSqlQuery query;
         query.prepare("UPDATE VISITES SET MONTANT = :montant WHERE NUMERO = :numero");
         query.bindValue(":montant", montant_str);
         query.bindValue(":numero", num_str);
         return query.exec();
     }


     /* bool visite::chercher_id_c(QString id)
     {
         QSqlQuery query;

         query.prepare("SELECT id_emplye FROM CLIENTS WHERE CIN=:id");
         query.bindValue(":id", id);

         if(query.exec() && query.next())
             return true;
         else
             return false;

     }*/
     /* bool visite::calculerremise(float montant, int nb_visites , QString numero){

         float remise=0.0;

         if (nb_visites == 5){
             remise=0.05;
         }

         if(nb_visites >5 && nb_visites<=10){

            remise=0.1;
         }
         if(nb_visites>=11 && nb_visites<=20){

           remise=0.2;
         }
         if(nb_visites>=21){

           remise=0.25;
         }

         float montantremise=montant*remise;
         float montantavecremise=montant-montantremise;
         qDebug()<<montantavecremise;


         QSqlQuery query;


                    query.prepare("UPDATE VISITES SET MONTANT=:montantavecremise WHERE NUMERO=:numero");
                    query.bindValue(":numero",numero);
                    query.bindValue(":montantavecremise",montantavecremise);


        return
        query.exec();
      }
 */


