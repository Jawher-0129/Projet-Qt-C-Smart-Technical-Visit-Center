#include "vehicule.h"
vehicule::vehicule()
{
    matricule="";
    marque="";
    type="";
    puissance=0;
    age=0;
    nbchevaux=0;
    carburant="";
    cin="";
}

vehicule::vehicule(QString matricule,QString marque,QString type,float puissance,int age,int nbchevaux,QString carburant,QString cin,QByteArray imageV)
{
    this->matricule=matricule;
    this->marque=marque;
    this->type=type;
    this->puissance=puissance;
    this->age=age;
    this->nbchevaux=nbchevaux;
    this->carburant=carburant;
    this->cin=cin;
    this->imageV=imageV;
}

QString vehicule::getcin()
{
    return cin;
}
QString vehicule::getmatricule()
{
    return matricule;
}

QString vehicule::getmarque()
{
    return marque;
}

QString vehicule::getype()
{
    return type;
}

float vehicule::getpuissance()
{
    return puissance;
}

int vehicule::getage()
{
    return age;
}

int vehicule::getnbchevaux()
{
    return nbchevaux;
}

QString vehicule::getcarburant()
{
    return carburant;
}

void vehicule::setmatricule(QString mat)
{
    matricule=mat;
}

void vehicule::setmarque(QString marq)
{
    marque=marq;
}

void vehicule::settype(QString tp)
{
    type=tp;
}

void vehicule::setpuissance(float puiss)
{
    puissance=puiss;
}

void vehicule::setage(int ag)
{
    age=ag;
}

void vehicule::setnbchevaux(int nbchev)
{
    nbchevaux=nbchev;
}

void vehicule::setcarburant(QString carb)
{
    carburant=carb;
}

void vehicule::setcin(QString c)
{
    cin=c;
}

bool vehicule::chercher_matricule(QString matricule)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM VEHICULES WHERE MATRICULE=:matricule");
    query.bindValue(":matricule",matricule);

    if(query.exec() && query.next())
        return true;
    else
        return false;
}

bool vehicule::chercher_client(QString cin)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM CLIENTS WHERE CIN=:cin");
    query.bindValue(":cin",cin);

    if(query.exec() && query.next())
        return true;
    else
        return false;
}

bool vehicule::ajouter()
{
    QSqlQuery query;
    QString puissanceString=QString::number(puissance);
    QString ageString=QString::number(age);
    QString nbchevauxString=QString::number(nbchevaux);

    query.prepare("INSERT INTO VEHICULES (MATRICULE,MARQUE,TYPE,PUISSANCE,AGE,NB_CHEVAUX,CARBURANT,CIN,IMAGE_VEHICULE)""VALUES(:matricule,:marque,:type,:puissance,:age,:nb_chevaux,:carburant,:cin,:image)");
    query.bindValue(":matricule",matricule);
    query.bindValue(":marque",marque);
    query.bindValue(":type",type);
    query.bindValue(":puissance",puissanceString);
    query.bindValue(":age",ageString);
    query.bindValue(":nb_chevaux",nbchevauxString);
    query.bindValue(":carburant",carburant);
    query.bindValue(":cin",cin);
    query.bindValue(":image",imageV);
    return query.exec();
}

bool vehicule::supprimer(QString matricule)
{
    QSqlQuery query;

    QMessageBox::StandardButton reply = QMessageBox::question(
                    nullptr,
                    "Confirmation de suppression",
                    "Êtes-vous sûr de vouloir supprimer cette Vehicule ?",
                    QMessageBox::Yes | QMessageBox::No
                    );

        if (reply == QMessageBox::Yes)
        {
    query.prepare("DELETE FROM VEHICULES WHERE MATRICULE=:matricule");
    query.bindValue(":matricule",matricule);
        }
    return query.exec();
}

QSqlQueryModel * vehicule::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT MATRICULE,MARQUE,TYPE,PUISSANCE,AGE,NB_CHEVAUX,CARBURANT,CIN FROM VEHICULES");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Marque"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Puissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Age"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Nombre_chevaux"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Carburant"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("CIN"));
    return model;
}

bool vehicule::modifier(QString matricule)
{
    QSqlQuery query;

    QString puissanceString=QString::number(puissance);
    QString ageString=QString::number(age);
    QString nbchevauxString=QString::number(nbchevaux);

    if(marque!="")
    {
        query.prepare("UPDATE VEHICULES SET MARQUE=:marque WHERE MATRICULE=:mat");
        query.bindValue(":mat",matricule);
        query.bindValue(":marque",marque);
        query.exec();
    }

    if(type!="")
    {
        query.prepare("UPDATE VEHICULES SET TYPE=:type WHERE MATRICULE=:mat");
        query.bindValue(":type",type);
        query.bindValue(":mat",matricule);
        query.exec();
    }

    if(puissanceString!="")
    {
       query.prepare("UPDATE VEHICULES SET PUISSANCE=:puiss WHERE MATRICULE=:mat");
       query.bindValue(":puiss",puissanceString);
       query.bindValue(":mat",matricule);
       query.exec();
    }

    if(ageString!="")
    {
        query.prepare("UPDATE VEHICULES SET AGE=:age WHERE MATRICULE=:mat");
        query.bindValue(":age",ageString);
        query.bindValue(":mat",matricule);
        query.exec();
    }

    if(nbchevauxString!="")
    {
        query.prepare("UPDATE VEHICULES SET NB_CHEVAUX=:nb_chevaux WHERE MATRICULE=:mat");
        query.bindValue(":nb_chevaux",nbchevauxString);
        query.bindValue(":mat",matricule);
        query.exec();
    }

    if(carburant!="")
    {
        query.prepare("UPDATE VEHICULES SET CARBURANT=:carb WHERE MATRICULE=:mat");
        query.bindValue(":carb",carburant);
        query.bindValue(":mat",matricule);
        query.exec();
    }
    if(cin!="")
    {
    if(chercher_client(encrypt(cin)))
    {
        query.prepare("UPDATE VEHICULES SET CIN=:cin WHERE MATRICULE=:mat");
        query.bindValue(":cin",cin);
        query.bindValue(":mat",matricule);
        query.exec();
    }
    }
    return query.exec();
}

QSqlQueryModel *vehicule::tri_croissant()
{
   QSqlQueryModel *model = new QSqlQueryModel();
   model->setQuery("SELECT MATRICULE,MARQUE,TYPE,PUISSANCE,AGE,NB_CHEVAUX,CARBURANT,CIN FROM VEHICULES ORDER BY AGE ");
   return model;
}

QSqlQueryModel *vehicule::tri_decroissant()
{
   QSqlQueryModel *model = new QSqlQueryModel();

   model->setQuery("SELECT MATRICULE,MARQUE,TYPE,PUISSANCE,AGE,NB_CHEVAUX,CARBURANT,CIN FROM VEHICULES ORDER BY AGE DESC");

   return model;
}

QSqlQueryModel *vehicule::rechercher(QString mat)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("SELECT MATRICULE,MARQUE,TYPE,PUISSANCE,AGE,NB_CHEVAUX,CARBURANT,CIN FROM VEHICULES WHERE MATRICULE LIKE '"+mat+"%'");
    return model;
}

QString vehicule::encrypt(QString cin)
{
    QString result;
    int shift = cin.right(1).toInt(); // use the last digit as the shift amount
    for(int i=0; i<cin.length()-1; i++) {
        // shift each digit by 'shift' amount and add it to the result
        result += QString::number((cin.at(i).digitValue() + shift) % 10);
    }
    // append the last digit to the end of the result
    result += cin.right(1);
    return result;
}

QString vehicule::decrypt(QString encrypted_cin)
{
    QString result;
    int shift = encrypted_cin.right(1).toInt(); // get the shift amount from the last digit
    for(int i=0; i<encrypted_cin.length()-1; i++) {
        // shift each digit back by 'shift' amount and add it to the result
        result += QString::number((encrypted_cin.at(i).digitValue() + 10 - shift) % 10);
    }
    // append the last digit to the end of the result
    result += encrypted_cin.right(1);
    return result;
}
