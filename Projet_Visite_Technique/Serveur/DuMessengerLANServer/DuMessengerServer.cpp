#include "DuMessengerServer.h"
#include <QDebug>
#include <QTextStream>
namespace DuarteCorporation {


DuMessengerServer::DuMessengerServer(QObject *parent)
  :QTcpServer(parent)
{

}

bool DuMessengerServer::startServer(quint16 port)
{
    return listen(QHostAddress::Any,port);
}

void DuMessengerServer::incomingConnection(qintptr handle)
{
    auto socket= new DuMessengerSocket(handle,this);
    mSockets<<socket;

    for(auto i: mSockets)
    {
        QTextStream T(i);
        T<<"serveur: Se connecter"<<handle;
        i->flush();
    }

    connect (socket,&DuMessengerSocket::DuReadyRead,[&] (DuMessengerSocket *S){
        qDebug()<<"QReadyRead";
        QTextStream T(S);
       auto text=T.readAll();

       for (auto i:mSockets)
       {
           QTextStream K(i);
           K<<text;
       }

    });
    connect (socket,&DuMessengerSocket::DuStateChanged,[&] (DuMessengerSocket *S,int ST){
        qDebug()<<"DuStateChanged";
        if(ST==QTcpSocket::UnconnectedState){
            qDebug()<<"UnconnectedState";

            mSockets.removeOne(S);
            for(auto i:mSockets)
            {
                QTextStream K(i);
                K<<"Serveur: Client"
                <<S->socketDescriptor()
                <<"Se connecter...";
                i->flush();
            }
        }

    });

}

}

