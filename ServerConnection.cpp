//
// Created by Jasson Rodríguez Méndez on 23/3/18.
//

#include "ServerConnection.h"
#include <iostream>

ServerConnection::ServerConnection() {
    connect();
}

void ServerConnection::connect(QString address, quint16 port) {
    this->address = address;
    this->port = port;
    socket = new QTcpSocket();
    socket->connectToHost(address, port);
    if(socket->waitForConnected(5000)) {
        std::cout << "Conectado con " << address.toStdString() << " en el puerto " << port << std::endl;
    }else{
        qDebug()<<"No se ha podido conectar al servidor";
        qDebug() << socket->error();
    }
}

void ServerConnection::connect() {
    socket = new QTcpSocket();
    socket->connectToHost(address, port);
    if(socket->waitForConnected(5000)) {
        std::cout << "Conectado con " << address.toStdString() << " en el puerto " << port << std::endl;
    }else{
        std::cout<<"No se ha podido conectar al servidor"<<std::endl;
    }
}

QJsonDocument* ServerConnection::request(QJsonDocument *data) {
    if (data->isObject()) {
        socket->write(data->toJson().data());
        socket->flush();
        std::cout<<"Mensaje: "<<data->toJson().data()<<std::endl;

        QString received = "";

        socket->waitForReadyRead();

        received = socket->readAll();

        QJsonDocument receivedData = QJsonDocument::fromJson(received.toUtf8());


        while(!receivedData.isObject()){
            socket->waitForReadyRead();
            received.append(socket->readAll());
            receivedData = QJsonDocument::fromJson(received.toUtf8());
        }

        QJsonDocument* receivedDataPtr = new QJsonDocument(receivedData);
        //std::cout <<receivedDataPtr->toJson().toStdString()<<std::endl;
        return receivedDataPtr;
    }
}

ServerConnection *ServerConnection::getServerConnection() {
    static ServerConnection *serverConnection;
    if(serverConnection == nullptr){
        serverConnection = new ServerConnection();
    }
    return serverConnection;
}

