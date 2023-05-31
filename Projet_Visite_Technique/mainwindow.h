#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "emp.h"
#include "vehicule.h"
#include "qrcodegen.h"
#include <QMainWindow>
#include "client.h"
#include "smtp.h"
#include "reclamation.h"
#include "widget.h"
#include "visite.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMovie>
#include <QtGui>
#include <QtWidgets/QMainWindow>
#include "arduino.h"
class QMediaplayer;
class QVideoWidget;class QMediaplayer;
class QVideoWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_boutton_connecter_clicked();



    void on_boutton_connexion_login_clicked();

    void on_boutton_gestions_employe_clicked();

    void on_boutton_ajouter_employe_clicked();

    void on_boutton_supprimer_employe_clicked();

    void on_tableView_employe_activated(const QModelIndex &index);

    void on_boutton_modifier_employe_clicked();

    void on_boutton_rechercher_employe_clicked();

    void on_boutton_PDF_employe_clicked();

    void on_boutton_statistique_employe_clicked();

    void on_boutton_retour_employe_clicked();

    void on_boutton_quitter_2_clicked();

    void on_pushButton_mdp_oubli_clicked();

    void on_pushButton_verif_mdp_clicked();

    void on_button_ajouter_vehicule_clicked();

    void on_boutton_choisir_image_vehicule_clicked();

    void on_radioButton_croissant_clicked();

    void on_radioButton_decroissant_clicked();

    void on_button_rechercher_vehicule_clicked();

    void on_tableView_vehicule_activated(const QModelIndex &index);

    void on_button_modifier_vehicule_clicked();

    void on_button_supprimer_vehicule_clicked();

    void on_button_convertir_pdf_vehicule_clicked();



    void on_button_scanner_codeqr_clicked();

    void on_boutton_generer_codeqr_clicked();

    void on_button_retour_codeqr_clicked();

    void on_boutton_verifier_image_vehicule_clicked();


    void on_radioButton_croissant_employe_clicked();

    void on_radioButton_decroissant_employe_clicked();

    void on_button_statistique_vehicule_clicked();

    void on_pushButton_17_clicked();

    void on_client_recherche_clicked();

    void on_ajouter_client_clicked();

    void on_client_table_activated(const QModelIndex &index);

    void on_client_modifier_clicked();

    void on_client_supprimer_clicked();

    void on_recherche_affiche_6_clicked();

    void on_go_to_mail_clicked();

    void on_client_return_mail_2_clicked();

    void on_client_convert_to_pdf_clicked();

    void on_send_mail_2_clicked();

    void on_boutton_gestions_clients_autre_employe_clicked();

    void on_pushButton_18_clicked();

    void on_button_retour_vehicule_clicked();

    void on_return_list_c_clicked();

    void on_boutton_ajout_reclamation_clicked();

    void on_boutton_supprimer_reclamation_clicked();

    void on_boutton_modifier_reclamation_2_clicked();

    void on_boutton_modifier_reclamation_clicked();

    void on_pushButton_33_clicked();

    void on_boutton_chatbox_clicked();

    void on_pushButton_20_clicked();

    void on_boutton_gestions_reclamations_autre_employe_clicked();

    void on_button_rechercher_reclamation_clicked();

    void on_pushButton_28_clicked();

    void on_radioButton_tri_croissant_reclamation_clicked();

    void on_radioButton_tri_decroissant_reclamation_clicked();

    void on_boutton_retour_reclamation_clicked();

    void on_radioButton_tri_croissant_client_clicked();

    void on_radioButton_tri_decroissant_client_clicked();

    void on_boutton_ajouter_visite_clicked();


    void on_pushButton_supprimer_visite_clicked();

    void on_tableView_visite_activated(const QModelIndex &index);

    void on_pushButton_modifier_visite_clicked();

    void on_pdf_clicked();

    void on_statistique_visite_clicked();

    void on_recherche_visite_clicked();

    void on_Croissante_visite_clicked();

    void on_decroissante_visite_clicked();

    void on_pushButton_remise_visite_clicked();

    //void on_video_2_clicked();

    void on_pushButton_19_clicked();

    void on_boutton_gestions_visites_autre_employe_clicked();

    void update_label_employe();

     void update_label_visite();
     void update_label_reclamation();


    void on_boutton_parking_adruino_clicked();

    void on_verifier_arduino_visite_clicked();

    void on_verifier_reclamation_clicked();

    void on_boutton_retour_employe_2_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_27_clicked();





private:
    Ui::MainWindow *ui;
   Emp E;
   vehicule V;
   client c;
   reclamation R;
   visite Vs;
   arduino A;
 // QByteArray data;


};
#endif // MAINWINDOW_H
