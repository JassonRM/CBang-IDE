//
// Created by Jasson Rodríguez Méndez on 23/3/18.
//

#ifndef CFACTORIAL_IDE_SERVERCONNECTION_H
#define CFACTORIAL_IDE_SERVERCONNECTION_H

#include <QJsonDocument>

#include "NetworkAdapter.h"

class ServerConnection {
private:
    NetworkAdapter *adapter;
    QJsonDocument incomingData;
    QString serverAddress = "localhost";
    quint16 serverPort = 8080;

    //Private constructor
    ServerConnection();

    //Avoid copies
    ServerConnection(ServerConnection const& copy); // Not implemented
    ServerConnection& operator=(ServerConnection const& copy); // Not implemented


public:
    static ServerConnection *getServerConnection();

    bool send(QJsonDocument *data);

    bool static receive(QByteArray data);

    static QJsonDocument getData();

    void setServerAddress(QString address, quint16 port);
};


#endif //CFACTORIAL_IDE_SERVERCONNECTION_H
