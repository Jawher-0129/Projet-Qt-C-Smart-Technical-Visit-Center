#ifndef DUMESSENGERSERVER_H
#define DUMESSENGERSERVER_H
#include "DuMessengerSocket.h"
#include <QTcpServer>
namespace DuarteCorporation
{
class  DuMessengerSocket;
class  DuMessengerServer : public QTcpServer
{
public:
    DuMessengerServer(QObject *parent=nullptr);
    bool startServer(quint16 port);

protected:
    void incomingConnection(qintptr handle);
private:
    QList <DuMessengerSocket *> mSockets;
};
}
#endif // DUMESSENGERSERVER_H
