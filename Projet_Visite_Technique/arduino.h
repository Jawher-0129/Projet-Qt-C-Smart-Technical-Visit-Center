#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
class arduino
{
public:
    arduino();
    QString getdata();
    int connect_arduino();
    int close_arduino();
    int write_to_arduino(QByteArray);
    QString read_from_arduino();
    QSerialPort * getserial();
    QString getarduino_port_name();
int chercher_id_employe(int id);
bool update_etat(int id);
int verif_etat(int id);

int cherchernum_reclamation(int num);
QByteArray read_from_arduino_reclamation();
    int chercher_numero_v(int id);

private:
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_producy_id=67;
    QString arduino_port_name;
    bool arduino_is_available;
    QString data;
    QByteArray data_rec;
};

#endif // ARDUINO_H
