//
// Created by marco on 19/03/18.
//

#include <QtWidgets>
#include "MainWindow.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    MainWindow window;

    window.show();

    ServerConnection *memoryServer = ServerConnection::getServerConnection();
    memoryServer->connect();

    QString data = "{\n"
                   "\"Request\" : \"New Variable\",\n"
                   "\"Identifier\" : \"num\",\n"
                   "\"Scope\" : 0,\n"
                   "\"Type\" : \"int\",\n"
                   "\"Value\":1\n"
                   "}";
    QJsonDocument message =  QJsonDocument::fromJson(data.toUtf8());
    QJsonDocument response = memoryServer->request(&message);
    std::cout<<"Respuesta: "<<response.toJson().data()<<std::endl;


}