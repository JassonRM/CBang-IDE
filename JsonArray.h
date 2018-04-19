//
// Created by marco on 07/04/18.
//

#ifndef CFACTORIAL_IDE_STRUCTURE_H
#define CFACTORIAL_IDE_STRUCTURE_H


#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include "Json.h"
/**
 * Representa una forma sencilla de manejar arreglos JSON
 */
class JsonArray {

    QJsonArray* variables = new QJsonArray;
    QJsonObject* json = new QJsonObject;

public:
    /**agrega un objeto JSON al arreglo
     *
     * @param jsonObject objeto por agregar
     */
    void add(Json* jsonObject);

    /**Agrega el valor y la llave asociada al objeto JSON
     *
     * @param key llave
     * @param value valor
     */
    void put(string key, string value);

    /**Agrega el valor y la llave asociada al objeto JSON
     *
     * @param key llave
     * @param value valor
     */
    void put(string key,int value);

    /**
     * Crea el request específico y lo pasa al ServerConnections
     */
    void submit();

    /**Obtiene la version en string del objeto JSON
     *
     * @return
     */
    string toString();
};


#endif //CFACTORIAL_IDE_STRUCTURE_H
