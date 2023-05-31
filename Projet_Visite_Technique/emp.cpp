#include "emp.h"
Emp::Emp()
{
    id=0;
    nom="";
    prenom="";
    email="";
    mdp="";
    grade="";
    nb_heure_supp=0;
    salaire=0;
}

Emp::Emp(int id,QString nom,QString prenom,QString email,QString mdp,QString grade,float salaire,int nb_heure_supp)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->mdp=mdp;
    this->grade=grade;
    this->salaire=salaire;
    this->nb_heure_supp=nb_heure_supp;
}

void Emp::setid(int ident)
{
    id=ident;
}

void Emp::setnom(QString n)
{
    nom=n;
}

void Emp::setprenom(QString pr)
{
    prenom=pr;
}

void Emp::setemail(QString mail)
{
    email=mail;
}

void Emp::setmdp(QString motpasse)
{
    mdp=motpasse;
}

void Emp::setgrade(QString grad)
{
    grade=grad;
}

void Emp::setsalaire(float sal)
{
    salaire=sal;
}


 void Emp::setnbhs(int nbhs)
 {
     nb_heure_supp=nbhs;
 }

int Emp::getid()
{
    return id;


}
 QString Emp::getnom()
 {
     return nom;
 }
 QString Emp::getprenom()
 {
     return prenom;
 }
 QString Emp::getemail()
 {
     return email;
 }
 QString Emp::getgrade()
 {
     return grade;
 }
 float Emp::getsalaire()
 {
     return salaire;
 }

 int Emp::getnbhs()
 {
     return nb_heure_supp;
 }

 bool  Emp:: ajouter()
   {




        QSqlQuery query;

       QString id_string=QString::number(id);
        QString nb_heure_supp_string=QString::number(nb_heure_supp);
        QString salaire_string=QString::number(salaire);

        query.prepare("INSERT INTO EMPLOYES (ID,NOM,PRENOM,EMAIL,MDP,GRADE,SALAIRE,NBHS) "
                      "VALUES (:ID,:NOM,:PRENOM,:EMAIL,:MDP,:GRADE,:SALAIRE,:NBHS)");
        query.bindValue(0, id_string);
        query.bindValue(1, nom);
        query.bindValue(2, prenom);
        query.bindValue(3, email);
        query.bindValue(4, mdp);
        query.bindValue(5, grade);
        query.bindValue(6, salaire_string);
        query.bindValue(7,nb_heure_supp_string);
         return query.exec();
    }



 QSqlQueryModel * Emp:: afficher()
    {
           QSqlQueryModel *model= new   QSqlQueryModel ();

               model->setQuery("SELECT*  FROM EMPLOYES");
             model->setHeaderData(0, Qt::Horizontal,  QObject::tr("ID"));
               model->setHeaderData(1, Qt::Horizontal,  QObject ::tr("NOM"));
               model->setHeaderData(2, Qt::Horizontal,  QObject ::tr("PRENOM"));
               model->setHeaderData(3, Qt::Horizontal,  QObject ::tr("EMAIL"));
               model->setHeaderData(4, Qt::Horizontal,  QObject ::tr("MDP"));
               model->setHeaderData(5, Qt::Horizontal,  QObject ::tr("GRADE"));
               model->setHeaderData(6, Qt::Horizontal,  QObject ::tr("SALAIRE"));
               model->setHeaderData(7, Qt::Horizontal,  QObject ::tr("NHBS"));
            return  model;

    }
 bool  Emp::supprimer (int id)
  {
      QSqlQuery query;

      query.prepare("delete  from EMPLOYES where id=:id ");

      query.bindValue(0, id);


  return query.exec();

  }
 bool Emp::modifier(int id)
 {
     QSqlQuery query;

     QString idString=QString::number(id);
     QString salaireString=QString::number(salaire);
     QString nb_heure_suppString=QString::number(nb_heure_supp);

     query.prepare("UPDATE EMPLOYES SET NOM=:nom,PRENOM=:prenom,EMAIL=:email,MDP=:mdp,GRADE=:grade,SALAIRE=:salaire,NBHS=:nbhs WHERE ID=:id ");
     query.bindValue(":id",idString);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":email",email);
     query.bindValue(":mdp",mdp);
     query.bindValue(":grade",grade);
     query.bindValue(":salaire",salaireString);
     query.bindValue(":nbhs",nb_heure_suppString);

     return query.exec();
 }
 bool Emp::verifier_grade(QString grade)
  {
      if(!((grade=="admin") || (grade=="agent") || (grade=="autre employe")))
          return false;
      else
          return true;
  }
 bool Emp::verif_email(QString email)
  {

      if (!email.contains("@")) {
          return false;
      }

      int index = email.indexOf("@");
      if (email.indexOf(".", index) == -1) {
          return false;
      }
      if (email.startsWith(".") || email.startsWith("@") || email.endsWith(".") || email.endsWith("@")) {
          return false;
      }

      QRegExp regExp("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
      return regExp.exactMatch(email);
  }
 QSqlQueryModel *Emp::Rechercher(QString value )
 {
      QSqlQueryModel *modal=new QSqlQueryModel();
      modal->setQuery("select * from EMPLOYES where id like '%"+value+"%' or nom like '%"+value+"%' or prenom like '%"+value+"%'or email like '%"+value+"%'or grade like '%"+value+"%'");
      return modal;
 }
 QSqlQueryModel *Emp::Trier_croissant_emp ()
     { QSqlQueryModel* modal=new QSqlQueryModel();
       modal->setQuery("select * from EMPLOYES ORDER BY NOM ASC ");
       return modal;

}
 QSqlQueryModel *Emp::Trier_decroissant_emp ()
     { QSqlQueryModel* modal=new QSqlQueryModel();
       modal->setQuery("select * from EMPLOYES ORDER BY NOM DESC ");
       return modal;

}


bool Emp::chercher_employe(QString id)
{
   QSqlQuery query;

   query.prepare("SELECT * FROM EMPLOYES WHERE ID=:id");
   query.bindValue(":id",id);

   if(query.exec() && query.next())
       return true;
   else
       return false;
}

