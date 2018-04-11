//
// Created by Jasson Rodríguez Méndez on 23/3/18.
//

#ifndef CFACTORIAL_IDE_SERVERCONNECTION_H
#define CFACTORIAL_IDE_SERVERCONNECTION_H

#include <QJsonDocument>
#include <QTcpSocket>
#include <array>


class ServerConnection {
private:
    QString address = "localhost";
    quint16 port = 2000;
    QTcpSocket *socket = nullptr;
    std::array<char, 4096> buffer;

    //Private constructor
    ServerConnection();

    //Avoid copies
    ServerConnection(ServerConnection const& copy); // Not implemented
    ServerConnection& operator=(ServerConnection const& copy); // Not implemented

public:
    static ServerConnection *getServerConnection();

    QJsonDocument request(QJsonDocument *data);

    void connect(QString address, quint16 port);

    void connect();
};


#endif //CFACTORIAL_IDE_SERVERCONNECTION_H
