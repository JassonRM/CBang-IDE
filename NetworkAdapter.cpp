//
// Created by Jasson Rodríguez Méndez on 23/3/18.
//

#include "NetworkAdapter.h"

NetworkAdapter::NetworkAdapter(QString address, quint16 port) {
    this->address = address;
    this->port = port;
}

bool NetworkAdapter::connect() {
    socket = new QTcpSocket();
    socket->connectToHost(address, port);
    socket->waitForConnected();
    if(socket->state() == QTcpSocket::ConnectedState) {
        return true;
    }else{
        return false;
    }
}

void NetworkAdapter::send(QByteArray data){
    socket->write(data);
}

void NetworkAdapter::setOnReceive(bool (*func)(QByteArray)) {
    this->onReceive = func;
}

void NetworkAdapter::receive() {
    QByteArray data = "";
    data.append(socket->readAll());
    bool isComplete = this->onReceive(data);
    while(!isComplete){
        data.append(socket->readAll());
    }
}


