#ifndef DUMESSENGERSOCKET_H
#define DUMESSENGERSOCKET_H
#include <QTcpSocket>

namespace DuarteCorporation {
class DuMessengerSocket : public QTcpSocket
{
     Q_OBJECT
public:
    DuMessengerSocket(qintptr handle,QObject *parent);

signals:
    void DuReadyRead(DuMessengerSocket *);
    void DuStateChanged(DuMessengerSocket *,int);
};
}
#endif // DUMESSENGERSOCKET_H
