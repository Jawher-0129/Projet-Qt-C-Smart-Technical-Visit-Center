#include "client.h"
using namespace QtCharts;

client::client()
{
    nom="";
    prenom="";
    adress="";
    cin="";
    email="";
    sexe="";
    tel="";
    date="";
}

client::client(QString cin,QString nom,QString prenom,QString adress,QString date,QString email,QString tel,QString sexe)
{
    this->nom=nom;
    this->prenom=prenom;
    this->adress=adress;
    this->cin=cin;

    this->email=email;
    this->sexe=sexe;
    this->tel=tel;
    this->date=date;
}

QString client::getnom()
{
    return nom;
}
QString client::getprenom()
{
    return prenom;
}
QString client::getadress()
{
    return adress;
}
QString client::getcin()
{
    return cin;
}
QString client::getemail()
{
    return email;
}
QString client::getsexe()
{
    return sexe;
}
QString client::gettel()
{
    return tel;
}
QString client::getdate()
{
    return date;
}

void client::setnom(QString n)
{
    nom=n;
}
void client::setprenom(QString p)
{
    prenom=p;
}
void client::setadress(QString a)
{
    adress=a;
}
void client::setcin(QString c)
{
    cin=c;
}
void client::setemail(QString e)
{
    email=e;
}
void client::setsexe(QString s)
{
    sexe=s;
}
void client::settel(QString t)
{
    tel=t;
}
void client::setdate(QString d)
{
    date=d;
}

//-------------------- checks mail validation done
bool client::isValidEmail(QString email) {
    QRegularExpression regex("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}");

       // We use QRegularExpressionMatch to test if the email matches the regex pattern
       QRegularExpressionMatch match = regex.match(email);

       // If the match is valid, return true. Otherwise, return false.
       return match.hasMatch();
}

//-------------------- recherche  done
bool client::chercher_client(QString cin)
{
    QSqlQuery query;

    query.prepare("SELECT CIN,NOM,PRENOM,ADRESSE,DATE_NAISSANCE,EMAIL,TEL,SEXE FROM CLIENTS WHERE CIN=:cin");
    query.bindValue(":cin", cin);

    if(query.exec() && query.next())
        return true;
    else
        return false;

}




//-------------------- ajoute done
bool client::ajouter_clilent()
{
    QSqlQuery query;

    query.prepare("INSERT INTO CLIENTS (CIN,NOM,PRENOM,ADRESSE,DATE_NAISSANCE,EMAIL,TEL,SEXE)""VALUES(:cin,:nom,:prenom,:adress,:date,:email,:tel,:sexe)");
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":sexe",sexe);
    query.bindValue(":adress",adress);
    query.bindValue(":tel",tel);
    query.bindValue(":date",date);

    return query.exec();

}
//-------------------- supprim done
bool client::supprimer_client(QString cin)
{
    QSqlQuery query;

    query.prepare("DELETE FROM CLIENTS WHERE CIN=:cin");
    query.bindValue(":cin",cin);

    return query.exec();
}
//-------------------- modif done
bool client::modifier_client(QString cin)
{
    QSqlQuery query;

    if(nom!="")
            {
                 query.prepare("UPDATE CLIENTS SET NOM=:nom WHERE CIN=:cin");
                 query.bindValue(":cin",cin);
                 query.bindValue(":nom",nom);

                 query.exec();

            }
    if(prenom!="")
            {
                 query.prepare("UPDATE CLIENTS SET PRENOM=:prenom WHERE CIN=:cin");
                  query.bindValue(":cin",cin);
                   query.bindValue(":prenom",prenom);
                    query.exec();
            }
    if(adress!="")
            {
                 query.prepare("UPDATE CLIENTS SET ADRESSE=:adress WHERE CIN=:cin");
                  query.bindValue(":cin",cin);
                  query.bindValue(":adress",adress);

                   query.exec();
            }
    if(date!="")
            {
                 query.prepare("UPDATE CLIENTS SET DATE_NAISSANCE=:date WHERE CIN=:cin");
                  query.bindValue(":cin",cin);
                  query.bindValue(":date",date);
                  query.exec();
            }
    if(email!="")
            {
                 query.prepare("UPDATE CLIENTS SET EMAIL=:email WHERE CIN=:cin");
                  query.bindValue(":cin",cin);
                 query.bindValue(":email",email);
                 query.exec();

            }
    if(tel!="")
            {
                 query.prepare("UPDATE CLIENTS SET TEL=:tel WHERE CIN=:cin");
                  query.bindValue(":cin",cin);
                  query.bindValue(":tel",tel);
                  query.exec();
            }
    if(sexe!="")
            {
                 query.prepare("UPDATE CLIENTS SET SEXE=:sexe WHERE CIN=:cin");
                 query.bindValue(":cin",cin);
                 query.bindValue(":sexe",sexe);
                 query.exec();
            }

    return query.exec();

}

QList<client> client::afficher_client()
{
     QList<client> persons;

     QSqlQuery query;

     query.prepare("SELECT * FROM CLIENTS");
     query.exec();

     while(query.next())
     {
         QString cin=query.value(0).toString();
         QString nom=query.value(1).toString();
         QString prenom=query.value(2).toString();
         QString email=query.value(3).toString();
         QString sexe=query.value(4).toString();
         QString adresse=query.value(5).toString();
         QString tel=query.value(6).toString();
         QString date=query.value(7).toString();
         cin=decrypt(cin);
         client C(cin,nom,prenom,adresse,date,email,tel,sexe);
         persons.append(C);
     }
     return persons;
}

QStandardItemModel *client::afficher_tous_client()
{
      QList<client> persons =afficher_client();
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(8);
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "NOM");
    model->setHeaderData(2, Qt::Horizontal, "PRENOM");
    model->setHeaderData(3, Qt::Horizontal, "EMAIL");
    model->setHeaderData(4, Qt::Horizontal, "SEXE");
    model->setHeaderData(5, Qt::Horizontal, "ADRESSE");
    model->setHeaderData(6, Qt::Horizontal, "TEL");
    model->setHeaderData(7, Qt::Horizontal, "DATE_NAISSANCE");

    for (client &person : persons)
    {
        QList<QStandardItem *> rowItems;
        rowItems.append(new QStandardItem(person.getcin()));
        rowItems.append(new QStandardItem(person.getnom()));
        rowItems.append(new QStandardItem(person.getprenom()));
        rowItems.append(new QStandardItem(person.getemail()));
        rowItems.append(new QStandardItem(person.getsexe()));
        rowItems.append(new QStandardItem(person.getadress()));
        rowItems.append(new QStandardItem(person.gettel()));
        rowItems.append(new QStandardItem(person.getdate()));
        model->appendRow(rowItems);
    }
    return model;
}

QStandardItemModel* client::afficher_client_tri_cor()
{
    QList<client> persons;

    QSqlQuery query;

    query.prepare("SELECT * FROM CLIENTS ORDER BY DATE_NAISSANCE ASC");
    query.exec();

    while(query.next())
    {
        QString cin=query.value(0).toString();
        QString nom=query.value(1).toString();
        QString prenom=query.value(2).toString();
        QString email=query.value(3).toString();
        QString sexe=query.value(4).toString();
        QString adresse=query.value(5).toString();
        QString tel=query.value(6).toString();
        QString date=query.value(7).toString();
        cin=decrypt(cin);
        client C(cin,nom,prenom,adresse,date,email,tel,sexe);
        persons.append(C);
    }
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(8);
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "NOM");
    model->setHeaderData(2, Qt::Horizontal, "PRENOM");
    model->setHeaderData(3, Qt::Horizontal, "EMAIL");
    model->setHeaderData(4, Qt::Horizontal, "SEXE");
    model->setHeaderData(5, Qt::Horizontal, "ADRESSE");
    model->setHeaderData(6, Qt::Horizontal, "TEL");
    model->setHeaderData(7, Qt::Horizontal, "DATE_NAISSANCE");

    for (client &person : persons)
    {
        QList<QStandardItem *> rowItems;
        rowItems.append(new QStandardItem(person.getcin()));
        rowItems.append(new QStandardItem(person.getnom()));
        rowItems.append(new QStandardItem(person.getprenom()));
        rowItems.append(new QStandardItem(person.getemail()));
        rowItems.append(new QStandardItem(person.getsexe()));
        rowItems.append(new QStandardItem(person.getadress()));
        rowItems.append(new QStandardItem(person.gettel()));
        rowItems.append(new QStandardItem(person.getdate()));
        model->appendRow(rowItems);
    }
    return model;
}

QStandardItemModel* client::rechercher_client(QString cin)
{

    QList<client> persons;

    QSqlQuery query;
    QString cin_crypt=encrypt(cin);

    query.prepare("SELECT * FROM CLIENTS WHERE CIN LIKE '"+cin_crypt+"%'");
    query.exec();

    while(query.next())
    {
        QString cin=query.value(0).toString();
        QString nom=query.value(1).toString();
        QString prenom=query.value(2).toString();
        QString email=query.value(3).toString();
        QString sexe=query.value(4).toString();
        QString adresse=query.value(5).toString();
        QString tel=query.value(6).toString();
        QString date=query.value(7).toString();
        cin=decrypt(cin);
        client C(cin,nom,prenom,adresse,date,email,tel,sexe);
        persons.append(C);
    }


    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(8);
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "NOM");
    model->setHeaderData(2, Qt::Horizontal, "PRENOM");
    model->setHeaderData(3, Qt::Horizontal, "EMAIL");
    model->setHeaderData(4, Qt::Horizontal, "SEXE");
    model->setHeaderData(5, Qt::Horizontal, "ADRESSE");
    model->setHeaderData(6, Qt::Horizontal, "TEL");
    model->setHeaderData(7, Qt::Horizontal, "DATE_NAISSANCE");

    for (client &person : persons)
    {
        QList<QStandardItem *> rowItems;
        rowItems.append(new QStandardItem(person.getcin()));
        rowItems.append(new QStandardItem(person.getnom()));
        rowItems.append(new QStandardItem(person.getprenom()));
        rowItems.append(new QStandardItem(person.getemail()));
        rowItems.append(new QStandardItem(person.getsexe()));
        rowItems.append(new QStandardItem(person.getadress()));
        rowItems.append(new QStandardItem(person.gettel()));
        rowItems.append(new QStandardItem(person.getdate()));
        model->appendRow(rowItems);
    }
    return model;
}


QStandardItemModel* client::afficher_client_tri_dec()
{

    QList<client> persons;

    QSqlQuery query;

    query.prepare("SELECT * FROM CLIENTS ORDER BY DATE_NAISSANCE DESC");
    query.exec();

    while(query.next())
    {
        QString cin=query.value(0).toString();
        QString nom=query.value(1).toString();
        QString prenom=query.value(2).toString();
        QString email=query.value(3).toString();
        QString sexe=query.value(4).toString();
        QString adresse=query.value(5).toString();
        QString tel=query.value(6).toString();
        QString date=query.value(7).toString();
        cin=decrypt(cin);
        client C(cin,nom,prenom,adresse,date,email,tel,sexe);
        persons.append(C);
    }


    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(8);
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "NOM");
    model->setHeaderData(2, Qt::Horizontal, "PRENOM");
    model->setHeaderData(3, Qt::Horizontal, "EMAIL");
    model->setHeaderData(4, Qt::Horizontal, "SEXE");
    model->setHeaderData(5, Qt::Horizontal, "ADRESSE");
    model->setHeaderData(6, Qt::Horizontal, "TEL");
    model->setHeaderData(7, Qt::Horizontal, "DATE_NAISSANCE");

    for (client &person : persons)
    {
        QList<QStandardItem *> rowItems;
        rowItems.append(new QStandardItem(person.getcin()));
        rowItems.append(new QStandardItem(person.getnom()));
        rowItems.append(new QStandardItem(person.getprenom()));
        rowItems.append(new QStandardItem(person.getemail()));
        rowItems.append(new QStandardItem(person.getsexe()));
        rowItems.append(new QStandardItem(person.getadress()));
        rowItems.append(new QStandardItem(person.gettel()));
        rowItems.append(new QStandardItem(person.getdate()));
        model->appendRow(rowItems);
    }
    return model;
}

//-------------------- affiche  stats done
void client::client_affiche_stats()
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENTS WHERE SEXE = 'Female'");
    query.exec();
    int femaleCount = query.next() ? query.value(0).toInt() : 0;

    query.prepare("SELECT COUNT(*) FROM CLIENTS WHERE SEXE = 'Male'");
    query.exec();
    int maleCount = query.next() ? query.value(0).toInt() : 0;

    // Get the total number of rows in the CLIENTS table
    query.exec("SELECT COUNT(*) FROM CLIENTS");

    int width = 1000; // desired width in pixels
        int height = 600; // desired height in pixel
        // Create the pie series and add slices to it
            QPieSeries *series = new QPieSeries();
            series->append("Female", femaleCount);
            series->append("Male",maleCount);

            foreach (QPieSlice *slice, series->slices()) {
                QString label = QString("%1: %2 (%3%)")
                    .arg(slice->label())
                    .arg(slice->value())
                    .arg(100 * slice->percentage(), 0, 'f', 2);
                slice->setLabel(label);
            }

            // Create a chart view to display the pie chart
            QChartView *chartView = new QChartView();
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->scene()->setSceneRect(0, 0, width, height);

            chartView->chart()->addSeries(series);
            chartView->chart()->setTitle("Statistique selon le sexe");

            // Set some chart options
            chartView->chart()->setAnimationOptions(QChart::SeriesAnimations);
            chartView->chart()->legend()->setAlignment(Qt::AlignRight);
            chartView->chart()->legend()->setFont(QFont("Arial", 15));
            // Set the size and position of the chart view
            QPropertyAnimation *animation = new QPropertyAnimation(series, "opacity");

            // Set the target object and property to animate
            animation->setTargetObject(series);
            animation->setPropertyName("opacity");

            // Set the duration and easing curve
            animation->setDuration(1000);
            animation->setEasingCurve(QEasingCurve::InOutQuad);
            animation->start();

            // Show the chart view
            chartView->show();
            chartView->update();

}


//-------------------- encrypt to done
QString client::encrypt(QString cin)
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
//-------------------- decrypt done
QString client::decrypt(QString encrypted_cin)
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


