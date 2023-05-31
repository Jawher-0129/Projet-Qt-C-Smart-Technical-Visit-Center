#include "arduino.h"

arduino::arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *arduino::getserial()
{
   return serial;
}
int arduino::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_available = true;
                   arduino_port_name=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << arduino_port_name;
        if(arduino_is_available){ // configuration de la communication ( débit...)
            serial->setPortName(arduino_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}

int arduino::close_arduino()
{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;
}


QString arduino::read_from_arduino()
{
    if(serial->isReadable()){
         data=serial->readAll(); //récupérer les données reçues
    }
    return data;

}

QByteArray arduino::read_from_arduino_reclamation()
{
    if(serial->isReadable())
    {
        data=serial->readAll(); //récupérer les données reçues
        return data_rec;
    }
    qDebug()<<"eerrooor";
    return 0;
}

int arduino::write_to_arduino( QByteArray d)
{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }
return -1;
}


int arduino::verif_etat(int id)
{
    QSqlDatabase bd = QSqlDatabase::database();
    QSqlQuery query;
    int etat;
    query.prepare("SELECT ETAT_ENTRE FROM EMPLOYES WHERE ID =:id");
    query.bindValue(0,id);

    query.exec();

    if(query.next())
    {
        etat=query.value(0).toInt();
        if(etat==0)
            return 0;
        else
            return 1;
    }
    return 1;
}

bool arduino::update_etat(int id)
{
    QSqlDatabase bd = QSqlDatabase::database();
    QString id_str=QString::number(id);
    QSqlQuery query;
    int etat=1;
    QString etat_str=QString::number(etat);

    query.prepare("UPDATE EMPLOYES SET ETAT_ENTRE=:etat WHERE ID=:id");
    query.bindValue(":etat",etat_str);
    query.bindValue(":id",id_str);
    return query.exec();

}

int arduino::chercher_id_employe(int id)
{
          QSqlDatabase bd = QSqlDatabase::database();
          int id_e;

              QSqlQuery query;
              query.prepare("SELECT ID FROM EMPLOYES WHERE ID =:id");
              query.bindValue(0,id);

              query.exec();
              if (query.next())
              {

                  id_e=query.value(0).toInt();

                   return id;

              }
              else {
                  return 0;
              }
 }


QString arduino::getdata()
{
  return data;
}
int arduino::chercher_numero_v(int id)
{

          QSqlDatabase bd = QSqlDatabase::database();
          QString x;

                 QSqlQuery query;
              query.prepare("SELECT RESULTAT FROM VISITES WHERE NUMERO =:id");
              query.bindValue(0,id);

              query.exec();
              if (query.next())
              {

                      x=query.value(0).toString();
                    if(x=="verifier")
                       return 1;
                    else
                        return 0;

             }
              else
                  {
                      return -1;
                  }

  }

int arduino::cherchernum_reclamation(int num)
{
    QSqlDatabase bd = QSqlDatabase::database();
    int x;

           QSqlQuery query;
        query.prepare("SELECT NUMERO FROM RECLAMATIONS WHERE NUMERO =:id");
        query.bindValue(0,num);

        query.exec();
        if (query.next())
        {

             x=query.value(0).toInt();
             return 1;
       }
        return -1;
}
