#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView_employe->setModel(E.afficher());
    ui->tableView_vehicule->setModel(V.afficher());
    ui->client_table->setModel(c.afficher_tous_client());
    ui->tableView_reclamation->setModel(R.afficher());
    ui->tableView_visite->setModel(Vs.afficher());

    ui->lineEdit_saisir_mdp->setEchoMode(QLineEdit::Password);
    connect(ui->lineEdit_recherche_supprimer_employe,&QLineEdit::textChanged,this,&MainWindow::on_boutton_rechercher_employe_clicked);
    connect(ui->lineEdit_chercher_supprimer_vehicule,&QLineEdit::textChanged,this,&MainWindow::on_button_rechercher_vehicule_clicked);
    connect(ui->lineEdit_rechercher_supprimer_reclamation,&QLineEdit::textChanged,this,&MainWindow::on_button_rechercher_reclamation_clicked);
    connect(ui->lineEdit_chercher_visite,&QLineEdit::textChanged,this,&MainWindow::on_recherche_visite_clicked);

    //initialiser arduino

    int ret = A.connect_arduino();
       switch(ret)
       {
       case (0): qDebug() << "arduino is available and connected to"<<A.getarduino_port_name();

          break;

         case (1):  qDebug() << "arduino is available but not  connected to"<<A.getarduino_port_name();
           break;
       case (-1):
            qDebug() << "arduino is not  available";
       }
    QObject:: connect (A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label_employe()));
       QObject:: connect (A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label_visite()));
         QObject:: connect (A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label_reclamation()));



    //matricule

    ui->lineEdit_matricule->setMaxLength(10);
    ui->lineEdit_matricule->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+")));

    //marque
   ui->lineEdit_marque->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+")));

    //AGE

     ui->lineEdit_age->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));

     //NB_CHEVAUX

     ui->lineEdit_nbchevaux->setMaxLength(3);
     ui->lineEdit_nbchevaux->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));

     //PUISSANCE

     ui->lineEdit_puissance->setValidator(new QRegExpValidator(QRegExp("[0-9.]+")));

     //CARBURANT

     ui->lineEdit_carburant->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));

    //CIN
     ui->lineEdit_cin->setMaxLength(8);
     ui->lineEdit_cin->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));

     ui->lineEdit_etat_modifier->setText("0");
     ui->lineEdit_nom_client->setMaxLength(20);
     ui->lineEdit_nom_client_modifier->setMaxLength(20);
      ui->lineEdit_prenom_client->setMaxLength(20);
     ui->lineEdit_prenom_client_modifeir->setMaxLength(20);
     ui->lineEdit_cin_client->setValidator(new QIntValidator(0,99999999,this));
     ui->lineEdit_nom_client->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));
     ui->lineEdit_prenom_client->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));

     ui->client_tel->setValidator(new QIntValidator(0, 99999999, this));

     QRegularExpression alphaRegex("^[a-zA-Z]*$");

     ui->client_prenom->setValidator(new QRegularExpressionValidator(alphaRegex, this));
     ui->client_nom->setValidator(new QRegularExpressionValidator(alphaRegex, this));
     ui->client_cin->setValidator(new QIntValidator(0, 99999999, this));
     ui->client_rech->setValidator(new QIntValidator(0, 99999999, this));

     ui->client_tel->setMaxLength(8);
     ui->client_cin->setMaxLength(8);
     ui->client_rech->setMaxLength(8);
     ui->client_nom->setMaxLength(20);
     ui->client_prenom->setMaxLength(20);
     ui->client_adress->setMaxLength(30);

     ui->lineEdit_id->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));
     ui->lineEdit_id->setMaxLength(4);
     ui->lineEdit_mdp->setMaxLength(5);
     ui->lineEdit_sup->setMaxLength(3);
     ui->lineEdit_n->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));
     ui->lineEdit_p->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));
     ui->lineEdit_sup->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));
     ui->lineEdit_g->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));
     ui->lineEdit_s->setValidator(new QRegExpValidator(QRegExp("[0-9.]+")));
     ui->lineEdit_montant->setText("30");

     ui->lineEdit_nbvisites->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));
     ui->lineEdit_id_visite->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));
     ui->lineEdit_montant->setValidator(new QIntValidator(0, 9999, this));
     ui->comboBox_resultat_visite->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));
      ui->lineEdit_hs->setValidator(new QIntValidator(0, 99, this));
      ui->lineEdit_he->setValidator(new QIntValidator(0, 99, this));
      ui->lineEdit_matriculevehicule->setMaxLength(9);

     QFile file(":/Images/Images/voiture.jpg");
     if(!file.open(QIODevice::ReadOnly |QIODevice::Text))
     {
         qDebug()<<"erreur d'ouverture du fichier";
         return;
     }
  QTextStream in(&file);
  qDebug()<<in.readAll();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_boutton_connecter_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_boutton_connexion_login_clicked()
{
    QString id_str=ui->lineEdit_saisir_id->text();
        QString mdp=ui->lineEdit_saisir_mdp->text();
        QSqlQuery query;

        query.prepare("SELECT * FROM EMPLOYES WHERE ID=:id AND MDP=:mdp");
        query.bindValue(":id",id_str);
        query.bindValue(":mdp",mdp);

        if(query.exec() && query.next())
        {
            QString grade=query.value(5).toString();

            if(grade=="admin")
            {

                QString message=QString("Bienvenue Mr/Mme %1 %2").arg(query.value(1).toString()).arg(query.value(2).toString());
                QMessageBox::information(nullptr, QObject::tr("OK"), message, QMessageBox::Cancel);

                ui->stackedWidget->setCurrentIndex(3);
            }
            else if(grade=="autre employe")
            {

                QString message=QString("Bienvenue Mr/Mme %1 %2").arg(query.value(1).toString()).arg(query.value(2).toString());
                QMessageBox::information(nullptr, QObject::tr("OK"), message, QMessageBox::Cancel);
                ui->stackedWidget->setCurrentIndex(4);
            }
            else if(grade=="agent")
            {
                QString message=QString("Bienvenue Mr/Mme %1 %2").arg(query.value(1).toString()).arg(query.value(2).toString());
                QMessageBox::information(nullptr, QObject::tr("OK"), message, QMessageBox::Cancel);
                ui->stackedWidget->setCurrentIndex(6);
            }
            ui->lineEdit_saisir_mdp->clear();
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                           QObject::tr("Identifiant ou mot de passe est incorrect.\n"
                                                       "click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_boutton_gestions_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_boutton_ajouter_employe_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
         QString nom=ui->lineEdit_n->text();
         QString prenom=ui->lineEdit_p->text();
         QString email=ui->lineEdit_em->text();
         QString mdp=ui->lineEdit_mdp->text();
        QString grade=ui->lineEdit_g->text();
         float salaire=ui->lineEdit_s->text().toFloat();
        int nb_heure_supp=ui->lineEdit_sup->text().toInt();

       Emp e(id,nom,prenom,email,mdp,grade,salaire,nb_heure_supp);

    if (e.verifier_grade(e.getgrade())&& e.verif_email(e.getemail()))
    {
        bool test=e.ajouter();
         if(test)
         {
              ui->tableView_employe->setModel(e.afficher());
                    QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                        QObject::tr("Ajout effectué\n"
                                                                    "click cancel to exit."),QMessageBox::Cancel);
                     }
                 else
                     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                           QObject::tr("Ajout non effectué.\n"
                                                       "click Cancel to exit."),QMessageBox::Cancel);
 }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                          QObject::tr("Verifier Votre Grade ou votre email Car il est invalide.\n"
                                                      "click Cancel to exit."),QMessageBox::Cancel);
}



void MainWindow::on_boutton_supprimer_employe_clicked()
{
    int id=ui->lineEdit_recherche_supprimer_employe->text().toInt();



       bool test=E.supprimer(id);

       if(test)
       {
           ui->tableView_employe->setModel(E.afficher());
           QMessageBox:: information(nullptr, QObject::tr("OK"),
                                               QObject::tr("Suppression effectué\n"
                                                           "click cancel to exit."),QMessageBox::Cancel);
            }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Suppression non effectué.\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);

       ui->lineEdit_recherche_supprimer_employe->clear();
}




void MainWindow::on_tableView_employe_activated(const QModelIndex &index)
{
    ui->tableView_employe->setModel(E.afficher());
    QString val=ui->tableView_employe->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM EMPLOYES WHERE ID='"+val+"'");
    if(qry.exec())
    {
     while(qry.next())
     {
      ui->lineEdit_id->setText(qry.value(0).toString());
      ui->lineEdit_n->setText(qry.value(1).toString());
      ui->lineEdit_p->setText(qry.value(2).toString());
      ui->lineEdit_mdp->setText(qry.value(3).toString());
      ui->lineEdit_em->setText(qry.value(4).toString());
      ui->lineEdit_g->setText(qry.value(5).toString());
      ui->lineEdit_s->setText(qry.value(6).toString());
      ui->lineEdit_sup->setText(qry.value(7).toString());
     }
    }
    else
    {
     QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}


void MainWindow::on_boutton_modifier_employe_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
         QString nom=ui->lineEdit_n->text();
         QString prenom=ui->lineEdit_p->text();
         QString email=ui->lineEdit_em->text();
         QString mdp=ui->lineEdit_mdp->text();
        QString grade=ui->lineEdit_g->text();
         float salaire=ui->lineEdit_s->text().toFloat();
        int nb_heure_supp=ui->lineEdit_sup->text().toInt();

       Emp e(id,nom,prenom,email,mdp,grade,salaire,nb_heure_supp);

       bool test=e.modifier(id);

       if(test)
       { ui->tableView_employe->setModel(e.afficher());
           QMessageBox:: information(nullptr, QObject::tr("OK"),
                                               QObject::tr("modification effectuee\n"
                                                           "click cancel to exit."),QMessageBox::Cancel);
       }
       else
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("modification non effectuee.\n"
                                             "click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_boutton_rechercher_employe_clicked()
{
        QString recherche=ui->lineEdit_recherche_supprimer_employe->text();
        ui->tableView_employe->setModel(E.Rechercher(recherche ));

}

void MainWindow::on_boutton_PDF_employe_clicked()
{
    QTableView table_emp;
    QSqlQueryModel * Mod=new  QSqlQueryModel();
    QString value=ui->lineEdit_id_imprimer->text();
         //Connection c;

         QSqlQuery qry;
         qry.prepare("select * from EMPLOYES where id='"+value+"'");
         qry.exec();
         Mod->setQuery(qry);
         table_emp.setModel(Mod);
         //c.closeconnection();

         QString strStream;
         QTextStream out(&strStream);

       /*  const int rowCount = tab_affaire.model()->rowCount();
         const int columnCount =  tab_affaire.model()->columnCount();*/

         const QString strTitle ="Document";



         out <<  "<html>\n"
                               //"<img src=':/icons/icons/icone.png'/>"
                              "<head>\n"
                                  "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                              <<  QString("<title>%1</title>\n").arg(strTitle)
                              <<  "</head>\n"
                                  "<style> h3{"
                                  "font-family: Century Gothic; color: #333; font-weight: lighter;"
                                  "}\n"
                                  "</style>\n"
                              "<body bgcolor=#ffffff link=#5000A0>\n"
                             << QString("<h1 style=\" font-size: 100px; font-family: Century Gothic; color: #e80e90; font-weight: lighter; text-align: center;\">%1</h1>\n").arg("Fiche d'employé")
                             <<"<br>";

                            QString id = table_emp.model()->data(table_emp.model()->index(0, 0)).toString().simplified();

                            out << QString("<h3>ID : %1</h3>").arg((!id.isEmpty()) ? id : QString("&nbsp;"));
                            QString nom = table_emp.model()->data(table_emp.model()->index(0, 1)).toString().simplified();
                            out << QString("<h3>NOM : %1</h3>").arg((!nom.isEmpty()) ?nom : QString("&nbsp;"));
                            QString prenom = table_emp.model()->data(table_emp.model()->index(0, 2)).toString().simplified();
                            out << QString("<h3>PRENOM : %1</h3>").arg((!prenom.isEmpty()) ? prenom : QString("&nbsp;"));
                            QString email = table_emp.model()->data(table_emp.model()->index(0, 3)).toString().simplified();
                            out << QString("<h3 bkcolor=0> EMAIL: %1</h3>").arg((!email.isEmpty()) ? email : QString("&nbsp;"));
                            QString mdp = table_emp.model()->data(table_emp.model()->index(0, 4)).toString().simplified();
                            out << QString("<h3 bkcolor=0>MDP : %1</h3>").arg((!mdp.isEmpty()) ?mdp: QString("&nbsp;"));
                            QString grade = table_emp.model()->data(table_emp.model()->index(0, 5)).toString().simplified();
                            out << QString("<h3 bkcolor=0>GRADE : %1</h3>").arg((!grade.isEmpty()) ? grade : QString("&nbsp;"));
                            QString salaire = table_emp.model()->data(table_emp.model()->index(0, 6)).toString().simplified();
                            out << QString("<h3 bkcolor=0>SALAIRE  : %1</h3>").arg((!salaire .isEmpty()) ? salaire  : QString("&nbsp;"));
                            QString nbhs = table_emp.model()->data(table_emp.model()->index(0, 6)).toString().simplified();
                            out << QString("<h3 bkcolor=0>NBHS : %1</h3>").arg((!nbhs .isEmpty()) ? nbhs  : QString("&nbsp;"));

                            out<<
                              "</body>\n"
                              "</html>\n";

                                  QTextDocument *document = new QTextDocument();
                                                  document->setHtml(strStream);

                                                  QPrinter printer;
                                                  QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                                                  if (dialog->exec() == QDialog::Accepted) {

                                                      document->print(&printer);
                                                  }

                                                  printer.setOutputFormat(QPrinter::PdfFormat);
                                                  printer.setPaperSize(QPrinter::A2);
       printer.setOutputFileName("employes.pdf+");
       printer.setPageMargins(QMarginsF(15, 15, 15, 15));

       delete document;
}

void MainWindow::on_boutton_statistique_employe_clicked()
{
    QSqlQueryModel * mod = new QSqlQueryModel();
        mod->setQuery("select * from EMPLOYES where SALAIRE < 500 ");
        float salaire=mod->rowCount();
        mod->setQuery("select * from EMPLOYES where SALAIRE  between 500 and 1000 ");
        float salairee=mod->rowCount();
        mod->setQuery("select * from EMPLOYES where SALAIRE>1000 ");
        float salaireee=mod->rowCount();
        float total=salaire+salairee+salaireee;
        QString a=QString("moins de 500 Dinars "+QString::number((salaire*100)/total,'f',2)+"%" );
        QString b=QString("entre 500 et 1000 Dinars "+QString::number((salairee*100)/total,'f',2)+"%" );
        QString c=QString("+1000 Dinars "+QString::number((salaireee*100)/total,'f',2)+"%" );
        QPieSeries *series = new QPieSeries();
        series->append(a,salaire);
        series->append(b,salairee);
        series->append(c,salaireee);
        if (salaire!=0)
        {QPieSlice *slice = series->slices().at(0);
            slice->setLabelVisible();
            slice->setPen(QPen());}
        if ( salairee!=0)
        {
            // Add label, explode and define brush for 2nd slice
            QPieSlice *slice1 = series->slices().at(1);
            //slice1->setExploded();
            slice1->setLabelVisible();
        }
        if(salaireee!=0)
        {
            // Add labels to rest of slices
            QPieSlice *slice2 = series->slices().at(2);
            //slice1->setExploded();
            slice2->setLabelVisible();
        }
        // Create the chart widget
        QChart *chart = new QChart();
        // Add data to chart with title and hide legend
        chart->addSeries(series);
        chart->setTitle("Pourcentage Par salaire :salaire "+ QString::number(total));
        chart->legend()->hide();
        // Used to display the chart
        QChartView *chartView = new QChartView(chart);

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
         chartView->setRenderHint(QPainter::Antialiasing);
         chartView->resize(1000,500);

        chartView->show();
}



void MainWindow::on_boutton_retour_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_boutton_quitter_2_clicked()
{
    this->close();
}


void MainWindow::on_pushButton_mdp_oubli_clicked()
{
    QString id=ui->lineEdit_saisir_id->text();
    Emp E;
    if(id!="" && E.chercher_employe(id))
        ui->stackedWidget->setCurrentIndex(2);

    else if(id=="")
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Veuillez saisir votre ID\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("ID que vous avez donner est invalide\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_verif_mdp_clicked()
{
     QString salaire_st=ui->lineEdit_salaire_qs->text();
        QString nbhss=ui->lineEdit_nbhs_qs->text();
        QString idd=ui->lineEdit_saisir_id->text();
        QSqlQuery query;
        query.prepare("SELECT * FROM EMPLOYES WHERE SALAIRE=:salaire AND NBHS=:nbhs");
        query.bindValue(":salaire", salaire_st);
        query.bindValue(":nbhs",nbhss);
         QString mdp=query.value(4).toString();
         if(query.exec() && query.next())
         {
         QString id=query.value(0).toString();
         QString mdp=query.value(4).toString();
         if(id==idd)
         { QMessageBox::information(0, "Mot de passe", "Votre mot de passe est : " + mdp);
             ui->stackedWidget->setCurrentIndex(1);
         }
          else {
             QMessageBox::warning(0, "Erreur", "La réponse à la question secrète est incorrecte.");
         }
         }
         else {
            QMessageBox::warning(0, "Erreur", "veuillez verifier votre salaire et votre heures supplementaires.");
        }
}

void MainWindow::on_button_ajouter_vehicule_clicked()
{
    QString matricule=ui->lineEdit_matricule->text();
    QString marque=ui->lineEdit_marque->text();
    QString type=ui->comboBox_type->currentText();
    float puissance=ui->lineEdit_puissance->text().toFloat();
    int age=ui->lineEdit_age->text().toInt();
    int nbchevaux=ui->lineEdit_nbchevaux->text().toInt();
    QString carburant=ui->lineEdit_carburant->text();
    QString cin=ui->lineEdit_cin_client_vehicule->text();

    QString imageV=ui->lineEdit_photo->text();


    QFile imageFile(imageV);
    if (!imageFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Erreur: impossible d'ouvrir le fichier d'image";
        return;
    }
    // Lire les données de l'image à partir du fichier
    QByteArray imageData = imageFile.readAll();



    vehicule V(matricule,marque,type,puissance,age,nbchevaux,carburant,cin,imageData);


    QString cin_crypt=V.encrypt(cin);
   if(V.chercher_client(cin_crypt))
   {
    bool test=V.ajouter();

    if(test)
    {
        ui->tableView_vehicule->setModel(V.afficher());

               QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                   QObject::tr("Ajout effectué\n"
                                                               "click cancel to exit."),QMessageBox::Cancel);

               QString chemin_image=ui->lineEdit_photo->text();

               QString repertoire="C:/"+V.getmatricule()+"_"+V.getcin();


               QDir dossier;

               if(!dossier.mkdir(repertoire))
                   qWarning() << "Impossible de créer le dossier";

               QString destination=QString("%1/%2").arg(repertoire).arg(QFileInfo(chemin_image).fileName());

               if(!QFile::copy(chemin_image,destination))
               {
                   qWarning() << "Impossible de copier l'image";
                   return;
               }
               QMessageBox::information(nullptr, QObject::tr("OK"),
                                        QObject::tr("Image créée avec succès\n"
                                                    "cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
   }
    else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Ajout non effectué.\n"
                                              "click Cancel to exit."),QMessageBox::Cancel);

   }

   else
       QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                             QObject::tr("Client n'existe pas.\n"
                                         "click Cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_boutton_choisir_image_vehicule_clicked()
{
    QString file = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image",QDir::homePath(), "Images (*.png *.xpm *.jpg *.jpeg)");
    ui->lineEdit_photo->setText(file);
}

void MainWindow::on_radioButton_croissant_clicked()
{
    ui->tableView_vehicule->setModel(V.tri_croissant());
}

void MainWindow::on_radioButton_decroissant_clicked()
{
    ui->tableView_vehicule->setModel(V.tri_decroissant());
}

void MainWindow::on_button_rechercher_vehicule_clicked()
{
    QString mat=ui->lineEdit_chercher_supprimer_vehicule->text();
    ui->tableView_vehicule->setModel(V.rechercher(mat));
}

void MainWindow::on_tableView_vehicule_activated(const QModelIndex &index)
{
    vehicule v;

       ui->tableView_vehicule->setModel(v.afficher());
       QString val=ui->tableView_vehicule->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("SELECT * FROM VEHICULES WHERE MATRICULE='"+val+"'");
       if(qry.exec())
       {
        while(qry.next())
        {
         ui->lineEdit_matricule->setText(qry.value(0).toString());
         ui->lineEdit_marque->setText(qry.value(1).toString());
         ui->comboBox_type->setCurrentText(qry.value(2).toString());
         ui->lineEdit_puissance->setText(qry.value(3).toString());
         ui->lineEdit_age->setText(qry.value(4).toString());
         ui->lineEdit_nbchevaux->setText(qry.value(5).toString());
         ui->lineEdit_carburant->setText(qry.value(6).toString());
         ui->lineEdit_cin_client_vehicule->setText(qry.value(7).toString());
        }
       }
       else
       {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
       }
}

void MainWindow::on_button_modifier_vehicule_clicked()
{
    ui->lineEdit_photo->clear();
    QString matricule=ui->lineEdit_matricule->text();
    QString marque=ui->lineEdit_marque->text();
    QString type=ui->comboBox_type->currentText();
    int age=ui->lineEdit_age->text().toInt();
    int nbchevaux=ui->lineEdit_nbchevaux->text().toInt();
     float puissance=ui->lineEdit_puissance->text().toFloat();
     QString carburant=ui->lineEdit_carburant->text();
     QString cin=ui->lineEdit_cin_client_vehicule->text();

     QString imageV=ui->lineEdit_photo->text();

     QFile imageFile(imageV);


     // Lire les données de l'image à partir du fichier
     QByteArray imageData = imageFile.readAll();
     vehicule V(matricule,marque,type,puissance,age,nbchevaux,carburant,cin,imageData);

     if(imageV=="")
     {
         QString cin_crypt=V.encrypt(V.getcin());
     if(V.chercher_client(cin_crypt))
     {

         bool test=V.modifier(matricule);
     if(test)
     {
         ui->tableView_vehicule->setModel(V.afficher());
         QMessageBox:: information(nullptr, QObject::tr("OK"),
                                             QObject::tr("modification effectuee\n"
                                                       "click cancel to exit."),QMessageBox::Cancel);
     }
     else
         QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                               QObject::tr("modification non effectuee.\n"
                                         "click Cancel to exit."),QMessageBox::Cancel);
     }
     else

             QMessageBox::critical(nullptr, QObject::tr("Not OK"),

                                               QObject::tr("CIN que vous avez entrez est invalide.\n"
                                                           "click Cancel to exit."),QMessageBox::Cancel);


     }
     else
     {
         QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                           QObject::tr("Remarque!! vous ne pouvez pas inserer l'image pour des raisons de sécrurité.\n"
                                                       "click Cancel to exit."),QMessageBox::Cancel);
         ui->lineEdit_photo->clear();

     }

}

void MainWindow::on_button_supprimer_vehicule_clicked()
{
    QString matricule=ui->lineEdit_chercher_supprimer_vehicule->text();

    if(matricule!="" && V.chercher_matricule(matricule))
     {
    bool test=V.supprimer(matricule);
    if(test)
    {
        ui->tableView_vehicule->setModel(V.afficher());
        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                            QObject::tr("Suppression effectué\n"
                                                        "click cancel to exit."),QMessageBox::Cancel);
         }
     else
         QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                               QObject::tr("Suppression non effectué.\n"
                                       "click Cancel to exit."),QMessageBox::Cancel);
}
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Matricule à supprimer est invalide.\n"
                                      "click Cancel to exit."),QMessageBox::Cancel);
}


void MainWindow::on_button_convertir_pdf_vehicule_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->tableView_vehicule->model()->rowCount();
    const int columnCount =ui->tableView_vehicule->model()->columnCount();


    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("vehicule")
            <<  "</head>\n"
            "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                "<h1>Liste des Vehicules</h1>"


                "<table border=1 cellspacing=0 cellpadding=2>\n";
    // headers
        out << "<thead><tr bgcolor=#f0f0f0>";
        for (int column = 0; column < columnCount; column++)
                out << QString("<th>%1</th>").arg(ui->tableView_vehicule->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";
        // data table
           for (int row = 0; row < rowCount; row++)
           {
               out << "<tr>";
               for (int column = 0; column < columnCount; column++)
               {
                       QString data = ui->tableView_vehicule->model()->data(ui->tableView_vehicule->model()->index(row, column)).toString().simplified();
                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));

               }
               out << "</tr>\n";
           }
           out <<  "</table>\n"
               "</body>\n"

                   "</html>\n";


QTextDocument *document = new QTextDocument();
document->setHtml(strStream);

QPrinter printer(QPrinter::PrinterResolution);
printer.setOutputFormat(QPrinter::PdfFormat);
printer.setOutputFileName("ListeDesVehicules.pdf");
document->print(&printer);
}


void MainWindow::on_button_scanner_codeqr_clicked()
{

    using namespace qrcodegen;


                QString matricule=ui->lineEdit_matricule_codeqr->text();

                     QSqlQuery query;
                     query.prepare("SELECT * FROM VEHICULES WHERE MATRICULE=:matricule");
                     query.bindValue(":matricule",matricule);
                     query.exec();


                     if(query.next())
                     {
                     QString mat=query.value(0).toString().simplified();
                     QString marque=query.value(1).toString().simplified();
                     QString type=query.value(2).toString().simplified();
                     QString puissance=query.value(3).toString().simplified();
                     QString age=query.value(4).toString().simplified();
                     QString nb_chevaux=query.value(5).toString().simplified();
                     QString carb=query.value(6).toString().simplified();
                     QString cin=query.value(7).toString().simplified();

                QString text ="MATRICULE: "+mat+"\n"+"Marque: "+marque+"\n"+"TYPE: "+type+"\n"+"PUISSANCE: "+puissance+"\n"+"AGE: "+age+"\n"+"NOMBRE DE CHEVAUX: "+nb_chevaux+"\n"+"CARBURANT: "+carb+"\n"+"CIN: "+cin+"\n";
                  QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );

                  int taille = qr.getSize();
                  QImage im(taille,taille, QImage::Format_RGB32);
                    QRgb black = qRgb(0,0,0);
                    QRgb white = qRgb(255,255,255);
                  for (int i = 0; i < taille; i++)
                    for (int j = 0; j < taille; j++)
                      im.setPixel(i,j,qr.getModule(i,j) ? black : white );//setpixmap tafichilek qr code
                  ui->qrcode->setPixmap( QPixmap::fromImage(im.scaled(200,200,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly));
              }
                     else
                         QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                               QObject::tr("Veuillez Saisir un matricule valide\n"
                                                        "click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_boutton_generer_codeqr_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_button_retour_codeqr_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_boutton_verifier_image_vehicule_clicked()
{
    vehicule V;
    QString matricule=ui->lineEdit_chercher_supprimer_vehicule->text();
    QString chemin_dossier;
    QSqlQuery query;

    if(matricule!="" && V.chercher_matricule(matricule))
    {
        query.prepare("SELECT * FROM VEHICULES WHERE MATRICULE=:matricule");
        query.bindValue(":matricule",matricule);
        query.exec();

        QString mat=query.value(0).toString().simplified();
        QString marque=query.value(1).toString().simplified();
        QString type=query.value(2).toString().simplified();
        QString puissance=query.value(3).toString().simplified();
        QString age=query.value(4).toString().simplified();
        QString nb_chevaux=query.value(5).toString().simplified();
        QString carb=query.value(6).toString().simplified();
        QString cin=query.value(7).toString().simplified();


    QDir dir("C:/");
        QStringList dirs = dir.entryList();
        for (const auto& d : dirs)
        {
            if (d.startsWith(matricule))
            {
                chemin_dossier=d;
            }
        }
        chemin_dossier="C:/"+chemin_dossier;
          QDir dossier(chemin_dossier);

          QStringList filters;
              filters << "*.jpg" << "*.jpeg" << "*.png" << "*.gif";
              qDebug()<<filters[0];
               dossier.setNameFilters(filters);

                QFileInfoList files = dossier.entryInfoList();
               QString chemin_complet=chemin_dossier+"/"+files[0].fileName();
               QPixmap pixmap(chemin_complet);
               QChart *chart = new QChart();

               QChartView *chartView = new QChartView(chart);

               QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
               QGraphicsScene *scene = new QGraphicsScene(chartView);
               scene->addItem(item);

               // Ajouter la scène au QGraphicsView
               chartView->setScene(scene);
               chartView->show();


    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Matricule est invalide.\n"
                                      "click Cancel to exit."),QMessageBox::Cancel);


    qDebug()<<V.encrypt("01234");
}

void MainWindow::on_radioButton_croissant_employe_clicked()
{
    ui->tableView_employe->setModel(E.Trier_croissant_emp());
}

void MainWindow::on_radioButton_decroissant_employe_clicked()
{
    ui->tableView_employe->setModel(E.Trier_decroissant_emp());
}

void MainWindow::on_button_statistique_vehicule_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        int nombre_voiture,nombre_moto,nombre_camion;
        float pourcentage_voiture,pourcentage_camion,pourcentage_moto,total;

        model->setQuery("SELECT * FROM VEHICULES WHERE TYPE='Voiture'");
        nombre_voiture=model->rowCount();

        model->setQuery("SELECT * FROM VEHICULES WHERE TYPE='Camion'");
        nombre_camion=model->rowCount();

        model->setQuery("SELECT * FROM VEHICULES WHERE TYPE='Moto'");
        nombre_moto=model->rowCount();

        total=nombre_voiture+nombre_moto+nombre_camion;

        pourcentage_voiture=(nombre_voiture*100)/total;
        pourcentage_camion=(nombre_camion*100)/total;
        pourcentage_moto=(nombre_moto*100)/total;

        QString a=QString::number(pourcentage_voiture,'f',2);
        QString b=QString::number(pourcentage_camion,'f',2);
        QString c=QString::number(pourcentage_moto,'f',2);
        a="VOITURE: "+a+"%";
        b="CAMION: "+b+"%";
        c="MOTO: "+c+"%";

        QPieSeries  *series=new QPieSeries();

        series->append(a,nombre_voiture);
        series->append(b,nombre_camion);
        series->append(c,nombre_moto);

        if(nombre_voiture!=0)
        {
            QPieSlice *slice= series->slices().at(0);
            slice->setLabelVisible();
            slice->setExploded(true);
        }

        if(nombre_camion!=0)
        {
         QPieSlice *slice1= series->slices().at(1);
         slice1->setLabelVisible();
        }

        if(nombre_moto!=0)
        {
         QPieSlice *slice2=series->slices().at(2);
         slice2->setLabelVisible();
        }
        QChart * chart=new QChart();

        chart->addSeries(series);

        chart->setTitle("Pourcentage Par Type DE VEHICULE :Nombre Des VEHICULES "+ QString::number(total));

        QChartView * chartview=new QChartView(chart);

        // Set some chart options
        chartview->chart()->setAnimationOptions(QChart::SeriesAnimations);
        chartview->chart()->legend()->setAlignment(Qt::AlignRight);
        chartview->chart()->legend()->setFont(QFont("Arial", 15));
        // Set the size and position of the chart view
        QPropertyAnimation *animation = new QPropertyAnimation(series, "opacity");

        // Set the target object and property to animate
        animation->setTargetObject(series);
        animation->setPropertyName("opacity");

        // Set the duration and easing curve
        animation->setDuration(1000);
        animation->setEasingCurve(QEasingCurve::InOutQuad);
        animation->start();

        chartview->resize(1000,500);
        chartview->show();

        qDebug()<<V.decrypt("8901236");
}

void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_client_recherche_clicked()
{
    QString cin=ui->client_rech->text();
    ui->client_table->setModel(c.rechercher_client(cin));

   ui->client_rech->clear();
}

void MainWindow::on_ajouter_client_clicked()
{
    QString cin=ui->client_cin->text();

    QString nom=ui->client_nom->text();
    QString prenom=ui->client_prenom->text();
    QString adress=ui->client_adress->text();

    QDate selectedDate = ui->client_date->date();
    QDate currentDate = QDate::currentDate();

    QString date = selectedDate.toString("yyyy-MM-dd");
    QString sexe = ui->client_sexe->currentText();

    QString email=ui->client_email->text();
    QString tel=ui->client_tel->text();

    int age = selectedDate.daysTo(currentDate) / 365; // Calculate age in years
    if (age < 18) {
        QMessageBox::critical(nullptr, QObject::tr("Ajoute"),
            QObject::tr("Client must be at least 18 years old.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    if(cin!="" && nom!="" && prenom!="" && adress!="" && email!="" && tel!=""  )
    {
            if(c.isValidEmail(email))
            {
                        if(!c.chercher_client(cin))
                            {

                            QString encrypted_cin = c.encrypt(cin);
                            client c(encrypted_cin, nom, prenom, adress, date, email, tel, sexe);
                                bool test=c.ajouter_clilent();

                                        if(test)
                                        {
                                                        QMessageBox:: information(nullptr, QObject::tr("ADD"),
                                                        QObject::tr("Ajout effectué\n"
                                                        "click cancel to exit."),QMessageBox::Cancel);

                                                        ui->client_cin->clear();
                                                        ui->client_nom->clear();

                                                        ui->client_prenom->clear();
                                                        ui->client_adress->clear();

                                                        ui->client_email->clear();
                                                        ui->client_tel->clear();

                                                          ui->client_table->setModel(c.afficher_tous_client());
                                        }
                                        else
                                        {
                                                            QMessageBox::critical(nullptr, QObject::tr("ADD"),
                                                            QObject::tr("Ajout non effectué.\n"
                                                            "click Cancel to exit."),QMessageBox::Cancel);
                                        }


                            }
                        else
                            {
                                QMessageBox::critical(nullptr, QObject::tr("ADD"),
                                QObject::tr("Client already in.\n"
                                "click Cancel to exit."),QMessageBox::Cancel);
                            }
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("ADD"),
                QObject::tr("Email is wrong in.\n"
                "click Cancel to exit."),QMessageBox::Cancel);
            }
    }
    else
    {
         QMessageBox::critical(nullptr, QObject::tr("ADD"),
         QObject::tr("something is empty.\n"
         "click Cancel to exit."),QMessageBox::Cancel);

    }
}

void MainWindow::on_client_table_activated(const QModelIndex &index)
{
    ui->client_table->setModel(c.afficher_tous_client());

    QString val=ui->client_table->model()->data(index).toString();
    QSqlQuery qry;

    qry.prepare("SELECT * FROM CLIENTS WHERE CIN='"+val+"'");

    if(qry.exec())
            {
                 if(qry.next())
                 {
                      ui->client_cin->setText(c.decrypt(qry.value(0).toString()));
                      ui->client_nom->setText(qry.value(1).toString());
                      ui->client_prenom->setText(qry.value(2).toString());
                      ui->client_email->setText(qry.value(3).toString());
                      ui->client_sexe->setCurrentText(qry.value(4).toString());
                      ui->client_adress->setText(qry.value(5).toString());
                      ui->client_tel->setText(qry.value(6).toString());
                      QDate date = QDate::fromString(qry.value(7).toString(), "yyyy-MM-dd");
                      ui->client_date->setDate(date);

                }
    }
}

void MainWindow::on_client_modifier_clicked()
{
    QString cin=ui->client_cin->text();
    QString nom=ui->client_nom->text();
    QString prenom=ui->client_prenom->text();
    QString adress=ui->client_adress->text();
    QString email=ui->client_email->text();
    QString tel=ui->client_tel->text();

    QDate selectedDate = ui->client_date->date();
    QDate currentDate = QDate::currentDate();
    int age = selectedDate.daysTo(currentDate) / 365; // Calculate age in years
    if (age < 18) {
        QMessageBox::critical(nullptr, QObject::tr("MODIF"),
            QObject::tr("Client must be at least 18 years old.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    QString date = selectedDate.toString("yyyy-MM-dd");
    QString sexe = ui->client_sexe->currentText();

   if(cin!="")
   {

           if(c.chercher_client(c.encrypt(cin)) )
           {
                   if(email=="" || c.isValidEmail(email) )
                   {                                   client c(cin,nom,prenom,adress,date,email,tel,sexe);
                                   bool test=c.modifier_client(c.encrypt(cin));

                               if(test)
                                   {
                                           ui->client_cin->clear();
                                           ui->client_nom->clear();

                                           ui->client_prenom->clear();
                                           ui->client_adress->clear();

                                           ui->client_email->clear();
                                           ui->client_tel->clear();

                                           QMessageBox:: information(nullptr, QObject::tr("MODIF"),
                                           QObject::tr("MODIF done\n"
                                           "click cancel to exit."),QMessageBox::Cancel);

                                             ui->client_table->setModel(c.afficher_tous_client());
                                   }
                               else
                                   {
                                               QMessageBox::critical(nullptr, QObject::tr("MODIF"),
                                               QObject::tr("modif non effectué.\n"
                                               "click Cancel to exit."),QMessageBox::Cancel);
                                   }
                      }
                   else
                   {
                       QMessageBox::critical(nullptr, QObject::tr("ADD"),
                       QObject::tr("Email is wrong in.\n"
                       "click Cancel to exit."),QMessageBox::Cancel);
                   }

           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("MODIF"),
               QObject::tr("client not found.\n"
              "click Cancel to exit."),QMessageBox::Cancel);

           }

   }
   else
   {
       QMessageBox::critical(nullptr, QObject::tr("MODIF"),
       QObject::tr("CIN is empty.\n"
       "click Cancel to exit."),QMessageBox::Cancel);
   }
}

void MainWindow::on_client_supprimer_clicked()
{
    QString cin=ui->client_rech->text();

    if(cin!="")
    {
          if(c.chercher_client(c.encrypt(cin)))
                    {
                            bool test=c.supprimer_client(c.encrypt(cin));

                                   if(test)
                                       {
                                               ui->client_cin->clear();
                                               ui->client_nom->clear();

                                               ui->client_prenom->clear();
                                               ui->client_adress->clear();

                                               ui->client_email->clear();
                                               ui->client_tel->clear();

                                               ui->client_rech->clear();

                                             QMessageBox:: information(nullptr, QObject::tr("Delete"),
                                             QObject::tr("Deleted done\n"
                                             "click cancel to exit."),QMessageBox::Cancel);

                                              ui->client_table->setModel(c.afficher_tous_client());
                                        }
                                       else
                                       {
                                               QMessageBox::critical(nullptr, QObject::tr("Delete"),
                                               QObject::tr("Delete not working.\n"
                                               "click Cancel to exit."),QMessageBox::Cancel);
                                       }

                     }
          else
          {
              QMessageBox::critical(nullptr, QObject::tr("Delete"),
              QObject::tr("Client not found to be deleted.\n"
              "click Cancel to exit."),QMessageBox::Cancel);
          }

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Delete"),
        QObject::tr("recherche is empty.\n"
        "click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_recherche_affiche_6_clicked()
{
    c.client_affiche_stats();
}

void MainWindow::on_go_to_mail_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_client_return_mail_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_client_convert_to_pdf_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->client_table->model()->rowCount();
    const int columnCount =ui->client_table->model()->columnCount();

    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("CLIENTS")
            <<  "</head>\n"
            "<body bgcolor=#75a2f0 link=#5000A0>\n"

                "<h1>Liste des Clients</h1>"

                "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
        out << "<thead><tr bgcolor=#f0f0f0>";

        for (int column = 0; column < columnCount; column++)
            {
                out << QString("<th>%1</th>").arg(ui->client_table->model()->headerData(column, Qt::Horizontal).toString());
            }

        out << "</tr></thead>\n";

        // data table
           for (int row = 0; row < rowCount; row++)
           {
               out << "<tr>";

               for (int column = 0; column < columnCount; column++)
                   {
                           QString data = ui->client_table->model()->data(ui->client_table->model()->index(row, column)).toString().simplified();
                           out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));

                   }
               out << "</tr>\n";
           }

           out <<  "</table>\n"
                   "</body>\n"
                   "</html>\n";

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("Liste des Clients.pdf");
        document->print(&printer);
}

void MainWindow::on_send_mail_2_clicked()
{
    client c;

    smtp* ssmtp = new smtp("tester44.tester2@gmail.com", "hpevdqbvclzebhxa", "smtp.gmail.com", 465);

            connect(ssmtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            QString email=ui->client_email_to_send_2->text();

            QString b=ui->client_email_subject_2->text();

            QString ob=ui->client_email_text_2->toPlainText();

             if(email!="" && b!="" && ob!="" )
                {
                              if(c.isValidEmail(email))
                              {
                                  ssmtp->sendMail("tester44.tester2@gmail.com", email , b,ob);
                                  QMessageBox::information(nullptr, QObject::tr("EMAIL"),
                                  QObject::tr("Email Envoyé avec succees.\n"
                                  "click Cancel to exit"),QMessageBox::Cancel);
                              }
                              else
                              {
                                  QMessageBox::critical(nullptr, QObject::tr("EMAIL"),
                                  QObject::tr("Email is wrong in.\n"
                                  "click Cancel to exit."),QMessageBox::Cancel);
                              }
                }
             else
                {
                        QMessageBox::critical(nullptr, QObject::tr("EMAIL"),
                        QObject::tr("something is empty.\n"
                        "click Cancel to exit."),QMessageBox::Cancel);
                }
}

void MainWindow::on_boutton_gestions_clients_autre_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_button_retour_vehicule_clicked()
{
    QString id_str=ui->lineEdit_saisir_id->text();

        QSqlQuery query;

        query.prepare("SELECT * FROM EMPLOYES WHERE ID=:id");
        query.bindValue(":id",id_str);

        if(query.exec() && query.next())
        {
            QString grade=query.value(5).toString();

            if(grade=="agent")
                ui->stackedWidget->setCurrentIndex(1);
            else
                ui->stackedWidget->setCurrentIndex(3);
        }
}

void MainWindow::on_return_list_c_clicked()
{
    QString id_str=ui->lineEdit_saisir_id->text();

        QSqlQuery query;

        query.prepare("SELECT * FROM EMPLOYES WHERE ID=:id");
        query.bindValue(":id",id_str);

        if(query.exec() && query.next())
        {
            QString grade=query.value(5).toString();

            if(grade=="admin")
                ui->stackedWidget->setCurrentIndex(3);
            else
                ui->stackedWidget->setCurrentIndex(4);
        }
}

void MainWindow::on_boutton_ajout_reclamation_clicked()
{
    QString nom_client=ui->lineEdit_nom_client->text();
    QString prenom_client=ui->lineEdit_prenom_client->text();
    QString email_client=ui->lineEdit_email_client->text();
    QString type=ui->comboBox->currentText();
    QString cin_client=ui->lineEdit_cin_client->text();
    QString message=ui->plainTextEdit->toPlainText();

    int etat=0;
    reclamation R(nom_client,prenom_client,email_client,type,cin_client,etat,message);


    if (R.verif_email(email_client))
    {
        if(R.chercher_client(R.encrypt(R.getcin_client())))
        {

        bool test=R.ajouter();
    if(test)
    {
        ui->tableView_reclamation->setModel(R.afficher());
        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                           QObject::tr("Ajout effectué\n"
                                                                       "click cancel to exit."),QMessageBox::Cancel);
                        }
                    else
                        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                              QObject::tr("Ajout non effectué\n"

                                                          "click Cancel to exit."),QMessageBox::Cancel);
    }
        else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué,client n'existe pas\n"

                                          "click Cancel to exit."),QMessageBox::Cancel);


    }

    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Email invalide !!!\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_boutton_supprimer_reclamation_clicked()
{
    int num=ui->lineEdit_rechercher_supprimer_reclamation->text().toInt();

    if(R.chercher_reclamation(num))
    {

    bool test=R.supprimer(num);

    if(test)
    {

        ui->tableView_reclamation->setModel(R.afficher());
        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                           QObject::tr("Suppression effectué\n"
                                                                       "click cancel to exit."),QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectué.\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);

    }
}

void MainWindow::on_boutton_modifier_reclamation_2_clicked()
{
    QString cin_client=ui->lineEdit_cin_client_modifier->text();
    QString nom_client=ui->lineEdit_nom_client_modifier->text();
    QString prenom_client=ui->lineEdit_prenom_client_modifeir->text();
    QString email_client=ui->lineEdit_email_client_modifier->text();
    QString type=ui->comboBox_2->currentText();
    int etat=ui->lineEdit_etat_modifier->text().toInt();
    QString message=ui->plainTextEdit->toPlainText();
    int num=ui->lineEdit_numero_modifier->text().toInt();

    reclamation R(nom_client,prenom_client,email_client,type,cin_client,etat,message);

    bool test=R.modifier(num);
    if(R.verif_email(email_client))
        qDebug()<<"Modification";
    {
    if(test)
     {
        ui->tableView_reclamation->setModel(R.afficher());
        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                           QObject::tr("Modification effectué\n"
                                                                       "click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Modification non effectué.\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);
    }

}

void MainWindow::on_boutton_modifier_reclamation_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::on_pushButton_33_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_boutton_chatbox_clicked()
{
    DuarteCorporation::widget w;
    w.exec();
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_boutton_gestions_reclamations_autre_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_button_rechercher_reclamation_clicked()
{
    QString valeur=ui->lineEdit_rechercher_supprimer_reclamation->text();
    ui->tableView_reclamation->setModel(R.rechercher_reclamation_numero(valeur));
}

void MainWindow::on_pushButton_28_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    int nb_service,nb_qualite,nb_prix,nb_autres;
    float pourcentage_serivce,pourcentage_qualite,pourcentage_prix,pourcentage_autres,total;

    model->setQuery("SELECT * FROM RECLAMATIONS WHERE TYPE_RECLAMATION='Service'");
    nb_service=model->rowCount();

    model->setQuery("SELECT * FROM RECLAMATIONS WHERE TYPE_RECLAMATION='Qualite'");
    nb_qualite=model->rowCount();

    model->setQuery("SELECT * FROM RECLAMATIONS WHERE TYPE_RECLAMATION='Prix'");
    nb_prix=model->rowCount();

    model->setQuery("SELECT * FROM RECLAMATIONS WHERE TYPE_RECLAMATION='Autres'");
    nb_autres=model->rowCount();

    total=nb_service+nb_qualite+nb_prix+nb_autres;

    pourcentage_serivce=(nb_service*100)/total;
    pourcentage_qualite=(nb_qualite*100)/total;
    pourcentage_prix=(nb_prix*100)/total;
    pourcentage_autres=(nb_autres*100)/total;


    QString a=QString::number(pourcentage_serivce,'f',2);
    QString b=QString::number(pourcentage_qualite,'f',2);
    QString c=QString::number(pourcentage_prix,'f',2);
    QString d=QString::number(pourcentage_autres,'f',2);
    a="Service: "+a+"%";
    b="Qualité: "+b+"%";
    c="Prix: "+c+"%";
    d="Autres: "+d+"%";

    QPieSeries  *series=new QPieSeries();

    series->append(a,nb_service);
    series->append(b,nb_qualite);
    series->append(c,nb_prix);
    series->append(d,nb_autres);

    if(nb_service!=0)
    {
        QPieSlice *slice= series->slices().at(0);
        slice->setLabelVisible();
        slice->setExploded(true);
    }

    if(nb_qualite!=0)
    {
     QPieSlice *slice1= series->slices().at(1);
     slice1->setLabelVisible();
    }

    if(nb_prix!=0)
    {
     QPieSlice *slice2=series->slices().at(2);
     slice2->setLabelVisible();
    }

    if(nb_autres!=0)
    {
     QPieSlice *slice3=series->slices().at(3);
     slice3->setLabelVisible();
    }

    QChart * chart=new QChart();

    chart->addSeries(series);

    chart->setTitle("Pourcentage Par Type DE RECLAMATIONS :Nombre Des RECLAMATIONS "+ QString::number(total));

    QChartView * chartview=new QChartView(chart);

    // Set some chart options
    chartview->chart()->setAnimationOptions(QChart::SeriesAnimations);
    chartview->chart()->legend()->setAlignment(Qt::AlignRight);
    chartview->chart()->legend()->setFont(QFont("Arial", 15));
    // Set the size and position of the chart view
    QPropertyAnimation *animation = new QPropertyAnimation(series, "opacity");

    // Set the target object and property to animate
    animation->setTargetObject(series);
    animation->setPropertyName("opacity");

    // Set the duration and easing curve
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
     chartview->setRenderHint(QPainter::Antialiasing);
     chartview->resize(1000,500);
    chartview->show();
}

void MainWindow::on_radioButton_tri_croissant_reclamation_clicked()
{
    ui->tableView_reclamation->setModel(R.triC());
}

void MainWindow::on_radioButton_tri_decroissant_reclamation_clicked()
{
    ui->tableView_reclamation->setModel(R.triDec());
}

void MainWindow::on_boutton_retour_reclamation_clicked()
{
    QString id_str=ui->lineEdit_saisir_id->text();

        QSqlQuery query;

        query.prepare("SELECT * FROM EMPLOYES WHERE ID=:id");
        query.bindValue(":id",id_str);

        if(query.exec() && query.next())
        {
            QString grade=query.value(5).toString();

            if(grade=="admin")
                ui->stackedWidget->setCurrentIndex(3);
            else
                ui->stackedWidget->setCurrentIndex(4);
        }
}

void MainWindow::on_radioButton_tri_croissant_client_clicked()
{
    ui->client_table->setModel(c.afficher_client_tri_cor());
}

void MainWindow::on_radioButton_tri_decroissant_client_clicked()
{
    ui->client_table->setModel(c.afficher_client_tri_dec());
}

void MainWindow::on_boutton_ajouter_visite_clicked()
{
    QDate today = QDate::currentDate();
    QDate selectedDate = ui->dateEdit_date->date();

    if (selectedDate < today) {
        QMessageBox::critical(nullptr, QObject::tr("INSERT"),
            QObject::tr("Invalid date. Date must be from today or the future.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }
    //QDate selectedDate = ui->dateEdit_date->date();
    QString date = selectedDate.toString("yyyy-MM-dd");
    QString resultat=ui->comboBox_resultat_visite->currentText();
    float montant=ui->lineEdit_montant->text().toFloat();
    int nb_visite=ui->lineEdit_nbvisites->text().toInt();
    int heure_entree=ui->lineEdit_he->text().toInt();

    int heure_sortie=ui->lineEdit_hs->text().toInt();
    int id=ui->lineEdit_id_visite->text().toInt();
    QString matricule_vehicule=ui->lineEdit_matriculevehicule->text();
    visite Vs(date,resultat,montant,nb_visite,heure_entree,heure_sortie,id,matricule_vehicule);


    if (Vs.getheuresortie()<= Vs.getheureentree()){
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("il faut que l'heure sortie inferieur a heure entree.\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);
    }
    else
    {
   bool test=Vs.ajouter();

        if(test)
        {
            ui->tableView_visite->setModel(Vs.afficher());
            QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                QObject::tr("Ajout effectuee\n"
                                                            "click cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Ajout non effectuee.\n"
                                            "click Cancel to exit."),QMessageBox::Cancel);
    }
}



void MainWindow::on_pushButton_supprimer_visite_clicked()
{
    QString matricule=ui->lineEdit_supprimer_visite->text();

        bool test=Vs.supprimer(matricule);

        if(test)
        {
            ui->tableView_visite->setModel(Vs.afficher());
            QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                               QObject::tr("Suppression effectué\n"
                                                                           "click cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Suppression non effectué.\n"
                                              "click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_tableView_visite_activated(const QModelIndex &index)
{
    visite Vs;

           ui->tableView_visite->setModel(Vs.afficher());
           QString val=ui->tableView_visite->model()->data(index).toString();
           QSqlQuery qry;
           qry.prepare("SELECT * FROM VISITES WHERE NUMERO='"+val+"'");
           if(qry.exec())
           {
            if(qry.next())
            {
             ui->lineEdit_supprimer_visite->setText(qry.value(0).toString());
             ui->lineEdit_nbvisites->setText(qry.value(4).toString());
             ui->lineEdit_montant->setText(qry.value(3).toString());
             //ui->comboBox_type->setCurrentText(qry.value(2).toString());
             ui->lineEdit_he->setText(qry.value(5).toString());
             ui->lineEdit_hs->setText(qry.value(6).toString());
             ui->dateEdit_date->setDate(qry.value(1).toDate());
             ui->comboBox->setCurrentText(qry.value(1).toString());
             ui->lineEdit_id_visite->setText(qry.value(7).toString());
             ui->lineEdit_matriculevehicule->setText(qry.value(8).toString());
                     }
                    }
                    else
                    {
                     QMessageBox::critical(this,tr("error::"),qry.lastError().text());
                    }
}

void MainWindow::on_pushButton_modifier_visite_clicked()
{
    QDate selectedDate = ui->dateEdit_date->date();
            QString date = selectedDate.toString("yyyy-MM-dd");
            QDate today = QDate::currentDate();

            if (selectedDate < today) {
                QMessageBox::critical(nullptr, QObject::tr("MODIF"),
                    QObject::tr("Invalid date. Date must be from today or the future.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
                return;
            }
            QString resultat=ui->comboBox_resultat_visite->currentText();
            float montant=ui->lineEdit_montant->text().toFloat();
            int nb_visite=ui->lineEdit_nbvisites->text().toInt();
            int heure_entree=ui->lineEdit_he->text().toInt();
            int heure_sortie=ui->lineEdit_hs->text().toInt();
            QString matricule=ui->lineEdit_matriculevehicule->text();
            int id=ui->lineEdit_id->text().toInt();
            QString matricule_vehicule=ui->lineEdit_matriculevehicule->text();
            QString num=ui->lineEdit_supprimer_visite->text();
            visite Vs(date,resultat,montant,nb_visite,heure_entree,heure_sortie,id,matricule_vehicule);
              int numero=ui->lineEdit_supprimer_visite->text().toInt();
              if (Vs.getheuresortie()<= Vs.getheureentree()){
                  QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                        QObject::tr("il faut que l'heure sortie inferieur a heure entree.\n"
                                                    "click Cancel to exit."),QMessageBox::Cancel);
              }
              else{
             bool test=Vs.modifier(numero);
             if(test)
             {
                 ui->tableView_visite->setModel(Vs.afficher());

                 QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                     QObject::tr("modification effectuee\n"
                                                                 "click cancel to exit."),QMessageBox::Cancel);
             }
             else
                 QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                       QObject::tr("modification non effectuee.\n"
                                                   "click Cancel to exit."),QMessageBox::Cancel);
              }
}

void MainWindow::on_pdf_clicked()
{
    QString strStream;
        QTextStream out(&strStream);
        const int rowCount = ui->tableView_visite->model()->rowCount();
        const int columnCount =ui->tableView_visite->model()->columnCount();

        out <<  "<html>\n"
                "<head>\n"
                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                <<  QString("<title>%1</title>\n").arg("visite")
                <<  "</head>\n"
                "<body bgcolor=#75a2f0 link=#5000A0>\n"
                    "<h1>Liste des Visites</h1>"


                    "<table border=1 cellspacing=0 cellpadding=2>\n";
        // headers
            out << "<thead><tr bgcolor=#f0f0f0>";
            for (int column = 0; column < columnCount; column++)
                    out << QString("<th>%1</th>").arg(ui->tableView_visite->model()->headerData(column, Qt::Horizontal).toString());
            out << "</tr></thead>\n";

        // data table
               for (int row = 0; row < rowCount; row++)
               {
                   out << "<tr>";
                   for (int column = 0; column < columnCount; column++)
                   {
                           QString data = ui->tableView_visite->model()->data(ui->tableView_visite->model()->index(row, column)).toString().simplified();
                           out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));

                   }
                   out << "</tr>\n";
               }
               out <<  "</table>\n"




                   "</body>\n"

                       "</html>\n";


    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("ListedesVisites.pdf");
    document->print(&printer);
}

void MainWindow::on_statistique_visite_clicked()
{
    QSqlQueryModel * mod = new QSqlQueryModel();
              mod->setQuery("select * from VISITES where MONTANT < 40 ");
              float montant=mod->rowCount();
              mod->setQuery("select * from VISITES where MONTANT  between 40 and 50 ");
              float montantt=mod->rowCount();
              mod->setQuery("select * from VISITES where MONTANT>50 ");
              float montanttt=mod->rowCount();
              float total=montant+montantt+montanttt;
              QString a=QString("moins de 40 Dinars "+QString::number((montant*100)/total,'f',2)+"%" );
              QString b=QString("entre 40 et 50 Dinars "+QString::number((montantt*100)/total,'f',2)+"%" );
              QString c=QString("+50 Dinars "+QString::number((montanttt*100)/total,'f',2)+"%" );
              QPieSeries *series = new QPieSeries();
              series->append(a,montant);
              series->append(b,montantt);
              series->append(c,montanttt);
              if (montant!=0)
              {QPieSlice *slice = series->slices().at(0);
                  slice->setLabelVisible();
                  slice->setPen(QPen());}
              if ( montantt!=0)
              {

                  QPieSlice *slice1 = series->slices().at(1);

                  slice1->setLabelVisible();
              }
              if(montanttt!=0)
              {

                  QPieSlice *slice2 = series->slices().at(2);

                  slice2->setLabelVisible();
              }
              // Create the chart widget
              QChart *chart = new QChart();
              //  titlre
              chart->addSeries(series);
              chart->setTitle("Pourcentage Par montant :montant "+ QString::number(total));
              chart->legend()->hide();



              QChartView *chartView = new QChartView(chart);
              chartView->setRenderHint(QPainter::Antialiasing);
              chartView->resize(1000,500);
              chartView->show();
              chartView->chart()->setAnimationOptions(QChart::SeriesAnimations);
              chartView->chart()->legend()->setAlignment(Qt::AlignRight);
              chartView->chart()->legend()->setFont(QFont("Arial", 15));

}

void MainWindow::on_recherche_visite_clicked()
{



    int numero=ui->lineEdit_chercher_visite->text().toInt();
    ui->tableView_visite->setModel(Vs.chercher_visite(numero));
   /* bool test=Vs.chercher_visite_1(numero);
     if(test)
    {
            ui->tableView_visite->setModel(Vs.chercher_visite(numero));
    }
    else
     {
         QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                               QObject::tr("visite not found.\n"
                                           "click Cancel to exit."),QMessageBox::Cancel);
    }*/
}

void MainWindow::on_Croissante_visite_clicked()
{
    ui->tableView_visite->setModel(Vs.triC());
}

void MainWindow::on_decroissante_visite_clicked()
{
    ui->tableView_visite->setModel(Vs.triDec());
}

void MainWindow::on_pushButton_remise_visite_clicked()
{
    float montant=ui->lineEdit_montant->text().toFloat();
    int numero=ui->lineEdit_supprimer_visite->text().toInt();
    int nb_visites=ui->lineEdit_nbvisites->text().toInt();

if (nb_visites>=5){

     float montant_remise=Vs.calculerremise( montant,  nb_visites, numero);

    bool test=Vs.update_remise(numero,montant_remise);
                if(test)
                {
                    ui->tableView_visite->setModel(Vs.afficher());
                    QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                        QObject::tr("remise effectuee\n"
                                                                    "click cancel to exit."),QMessageBox::Cancel);
                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                          QObject::tr("remise non effectuee.\n"
                                                      "click Cancel to exit."),QMessageBox::Cancel);
}
else
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                          QObject::tr("il faut plus que 4 visites pour avoir la remise e.\n"
                                      "click Cancel to exit."),QMessageBox::Cancel);
}

/*void MainWindow::on_video_2_clicked()
{
    QString filename = "C:/Users/jawhe/OneDrive/Bureau/2a8-smart-technical-visit-center-integration_ranim/videomouna.mp4"; // Replace with the path to your video file
    QUrl videoUrl = QUrl::fromLocalFile(filename);

    QMediaPlayer *player = new QMediaPlayer;
    QVideoWidget *videoWidget = new QVideoWidget;

    player->setMedia(videoUrl);
    player->setVideoOutput(videoWidget);

    // Modification de la résolution de la fenêtre vidéo
    videoWidget->setFixedSize(640, 480);

    videoWidget->show();

    player->play();

    connect(player, &QMediaPlayer::stateChanged, [=](QMediaPlayer::State state){
        if(state == QMediaPlayer::StoppedState){
            player->stop();
        }
    });
}
*/
void MainWindow::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
}

void MainWindow::on_boutton_gestions_visites_autre_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
}

void MainWindow::update_label_employe()
{
    QString data=A.read_from_arduino();

    QString ch=ui->lineEdit_id_employe_arduino->text();
    int id=ui->lineEdit_id_employe_arduino->text().toInt();


    if(data=="*")
        ui->lineEdit_id_employe_arduino->clear();
    else if(data=="A")
        ui->lineEdit_id_employe_arduino->backspace();
    else if(data=="D")
    {
        if(A.chercher_id_employe(id))
        {
            if(A.verif_etat(id)==0)
            {
            QSqlQuery query;
            query.prepare("SELECT * FROM EMPLOYES WHERE ID=:id");
            query.bindValue(":id",ch);
            query.exec();
            if(query.next())
            {
                MainWindow::on_boutton_parking_adruino_clicked();
            QString message=QString("Bienvenue Mr/Mme %1 %2").arg(query.value(1).toString()).arg(query.value(2).toString());
                            QMessageBox::information(nullptr, QObject::tr("OK"), message, QMessageBox::Cancel);
                      ui->lineEdit_id_employe_arduino->clear();
            }
            }
            else
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                                     QObject::tr("Vehicule est deja entre !!!.\n"
                                                             "click Cancel to exit."),QMessageBox::Cancel);

        }

        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Identifiant incorrect.\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);

    }

   else
    {
    ch=ch+data;
    qDebug()<<data;
    ui->lineEdit_id_employe_arduino->setText(ch);
    }
}

void MainWindow::on_boutton_parking_adruino_clicked()
{
    int data=ui->lineEdit_id_employe_arduino->text().toInt();

       if(data!=0)
       {
       qDebug()<<"res:"<<A.chercher_id_employe(data);
       if(A.chercher_id_employe(data)!=0)
       {
           if(A.verif_etat(data)==0)
           {
         A.write_to_arduino("1");
         bool test=A.update_etat(data);
           }
           else
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                     QObject::tr("Vehicule a été dejà entrée !!!.\n"
                                             "click Cancel to exit."),QMessageBox::Cancel);
       }
       else if(A.chercher_id_employe(data)==0)
       {
       A.write_to_arduino("0");
       QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                             QObject::tr("Identifiant incorrect.\n"
                                     "click Cancel to exit."),QMessageBox::Cancel);
       }
       }
        data=0;

        ui->lineEdit_id_employe_arduino->clear();
}

void MainWindow::on_verifier_arduino_visite_clicked()
{
    qDebug() << "Bouton Verifier Clicked" ;
            int data=ui->visite_arduino_line->text().toInt();
            QString data_str=ui->visite_arduino_line->text();
            qDebug() << data;
            qDebug() << data_str;

            if(data!=0)
            {

            //qDebug()<<data.toLongLong();
            qDebug()<<"res:"<<A.chercher_numero_v(data);
                if(A.chercher_numero_v(data)==1)
                    {
                      A.write_to_arduino("1");
                    }

                else if(A.chercher_numero_v(data)==0)
                     {
                         A.write_to_arduino("0");
                     }
                else
                {
                    QMessageBox::critical(nullptr, QObject::tr("Numero"),
                    QObject::tr("Numero not found.\n"
                    "click Cancel to exit"),QMessageBox::Cancel);

                }

            }
             data=0;
}

void MainWindow::update_label_visite()
{
    QString data=A.read_from_arduino();
  //  qDebug()<<data<<"test";
    QString keyPressed = data.trimmed();

   if(!keyPressed.isEmpty()) {
        qDebug() << keyPressed;
        if (keyPressed.toInt() != 0 || keyPressed == "0")
            ui->visite_arduino_line->insert(keyPressed);
        else if (keyPressed == "*")
            ui->visite_arduino_line->backspace();
        else if (keyPressed == "#")
            MainWindow::on_verifier_arduino_visite_clicked();
    }

}

void MainWindow::update_label_reclamation()
{
    QString data=A.read_from_arduino();
    QString keyPressed = data.trimmed();
    qDebug()<<keyPressed;
    if(!keyPressed.isEmpty()) {
        qDebug() << keyPressed;
        if (keyPressed.toInt() != 0 || keyPressed == "0")
            ui->lineEdit_numero_arduino->insert(keyPressed);
        else if (keyPressed == "*")
            ui->lineEdit_numero_arduino->clear();
        else if (keyPressed == "A")
            ui->lineEdit_numero_arduino->backspace();
        else if (keyPressed == "D")
            MainWindow::on_verifier_reclamation_clicked();
    }
}


void MainWindow::on_verifier_reclamation_clicked()
{
    qDebug() << "Bouton Verifier Clicked" ;

    int data=ui->lineEdit_numero_arduino->text().toInt();
    QString data_str=ui->lineEdit_numero_arduino->text();
    qDebug() << data;
    qDebug() << data_str;

               if(data_str!="")
               {

               if(R.chercher_reclamation(data))
               {
                   int etatt=R.return_etat(data);


                   qDebug()<<etatt;

                   if(etatt==1)
                   {
                       QMessageBox::information(this, "Reclamation", "Reclamation traitée");
                   }
                   else
                       QMessageBox::information(this, "Reclamation", "Reclamation non traitée");
               }
               else
                   QMessageBox::information(this, "Reclamation", "Reclamation non trouvé");
               }
                data=0;
               if(data_str=="")
               {
                    QMessageBox::information(this, "Reclamation", "Veuillez remplir le champs");
               }
}



void MainWindow::on_boutton_retour_employe_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_13_clicked()
{
    QString id_str=ui->lineEdit_saisir_id->text();

        QSqlQuery query;

        query.prepare("SELECT * FROM EMPLOYES WHERE ID=:id");
        query.bindValue(":id",id_str);

        if(query.exec() && query.next())
        {
            QString grade=query.value(5).toString();

            if(grade=="admin")
                ui->stackedWidget->setCurrentIndex(3);
            else
                ui->stackedWidget->setCurrentIndex(4);
        }
}

void MainWindow::on_pushButton_27_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->tableView_reclamation->model()->rowCount();
    const int columnCount =ui->tableView_reclamation->model()->columnCount();


    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("reclamation")
            <<  "</head>\n"
            "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                "<h1>Liste des reclamations</h1>"


                "<table border=1 cellspacing=0 cellpadding=2>\n";
    // headers
        out << "<thead><tr bgcolor=#f0f0f0>";
        for (int column = 0; column < columnCount; column++)
                out << QString("<th>%1</th>").arg(ui->tableView_reclamation->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";
        // data table
           for (int row = 0; row < rowCount; row++)
           {
               out << "<tr>";
               for (int column = 0; column < columnCount; column++)
               {
                       QString data = ui->tableView_reclamation->model()->data(ui->tableView_reclamation->model()->index(row, column)).toString().simplified();
                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));

               }
               out << "</tr>\n";
           }
           out <<  "</table>\n"
               "</body>\n"

                   "</html>\n";


QTextDocument *document = new QTextDocument();
document->setHtml(strStream);

QPrinter printer(QPrinter::PrinterResolution);
printer.setOutputFormat(QPrinter::PdfFormat);
printer.setOutputFileName("ListeDesreclamations.pdf");
document->print(&printer);
}


