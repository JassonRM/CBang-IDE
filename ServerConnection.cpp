//
// Created by Jasson Rodríguez Méndez on 23/3/18.
//

#include "ServerConnection.h"


ServerConnection::ServerConnection() {
    adapter = new NetworkAdapter(serverAddress, serverPort);
    adapter->setOnReceive(&receive);
}

bool ServerConnection::send(QJsonDocument *data) {
    if(data->isObject()) {
        QByteArray message = data->toBinaryData();
        adapter->send(message);
        return true;
    }else{
        return false;
    }
}

ServerConnection *ServerConnection::getServerConnection() {
    static ServerConnection *serverConnection;
    if(serverConnection == nullptr){
        serverConnection = new ServerConnection();
    }
    return serverConnection;
}

bool ServerConnection::receive(QByteArray data) {
    QJsonDocument receivedData = QJsonDocument::fromBinaryData(data);
    if(receivedData.isObject()){
        ServerConnection::getServerConnection()->incomingData = receivedData;
        return true;
    }else{
        return false;
    }
}

void ServerConnection::setServerAddress(QString address, quint16 port) {
    this->serverAddress = address;
    this->serverPort = port;
}