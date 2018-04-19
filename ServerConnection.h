//
// Created by Jasson Rodríguez Méndez on 23/3/18.
//

#ifndef CFACTORIAL_IDE_SERVERCONNECTION_H
#define CFACTORIAL_IDE_SERVERCONNECTION_H

#include <QJsonDocument>
#include <QTcpSocket>
#include <array>

/**
 * Se encarga de la conexion al servidor de memoria
 */
class ServerConnection {
private:
    /**
     * Direccion del servidor de memoria
     */
    QString address = "localhost";
    /**
     * Puerto en el que escucha el servidor
     */
    quint16 port = 2000;
    /**
     * Socket que se va a conectar al servidor
     */
    QTcpSocket *socket = nullptr;
    /**
     * Buffer de memoria para recibir datos
     */
    std::array<char, 4096> buffer;

    /**
     * Constructor privado para evitar multiples instancias
     */
    ServerConnection();

    /**
     * Evita copias, no esta implementado
     * @param copy
     */
    ServerConnection(ServerConnection const& copy); // Not implemented
    /**
     * Evita copias, no esta implementado
     * @param copy
     * @return
     */
    ServerConnection& operator=(ServerConnection const& copy); // Not implemented

public:
    /**
     * Singleton para obtener instancia de la conexion
     * @return instancia unica de ServerConnection
     */
    static ServerConnection *getServerConnection();

    /**
     * Realiza un request al servidor
     * @param data Informacion en formato JSON
     * @return Respuesta del servidor en formato JSON
     */
    QJsonDocument* request(QJsonDocument *data);

    /**
     * Inicializa la conexion al servidor en una direccion personalizada
     * @param address Direccion a la cual conectarse
     * @param port Puerto para conectarse
     */
    void connect(QString address, quint16 port);

    /**
     * Inicializa la conexion al servidor
     */
    void connect();
};


#endif //CFACTORIAL_IDE_SERVERCONNECTION_H
