//
// Created by Jasson Rodríguez Méndez on 23/3/18.
//

#ifndef CFACTORIAL_IDE_NETWORKADAPTER_H
#define CFACTORIAL_IDE_NETWORKADAPTER_H

#include <QTcpSocket>

class NetworkAdapter {
private:
    QString address;
    quint16 port;

    QTcpSocket *socket = nullptr;

    bool (*onReceive)(QByteArray);

public:
    NetworkAdapter(QString address, quint16 port);
    bool connect();
    void send(QByteArray);
    void setOnReceive(bool (*func)(QByteArray));

public slots:
    void receive();
};


#endif //CFACTORIAL_IDE_NETWORKADAPTER_H
