//
// Created by marco on 27/03/18.
//

#ifndef CODEPARSER_VARIABLE_H
#define CODEPARSER_VARIABLE_H

#include <iostream>
#include <vector>
#include <QtCore/QJsonObject>
#include "Token.h"
#include <QtCore/QJsonDocument>

using namespace std;
/**
 *Representa una forma sencilla de manejar QJsonObjects
 */
class Json {
private:
    QJsonObject* json = new QJsonObject();

public:
    /**Agrega el valor y la llave asociada al objeto JSON
     *
     * @param key llave
     * @param value valor
     */
    void put(string key,string value);

    /**Agrega el valor y la llave asociada al objeto JSON
     *
     * @param key llave
     * @param value valor
     */
    void put(string key,int value);

    void put(string key,float value);

    void put(string key,double value);

    void put(string key,long value);

    /**Agrega el valor y la llave asociada al objeto JSON
     *
     * @param key llave
     * @param value valor
     */
    void putJsonValue(string key, QJsonValue value);

    /**Agrega un valor a la llave "Value" del objeto JSON
     *
     * @param value Valor
     * @param token Token del valor por agregar
     * @return
     */
    string addValue(string value, Token* token);

    /**Agrega un valor a la llave "Value" del objeto JSON
     *
     * @param value Valor
     * @param token Tipo de token del valor por agregar
     * @return
     */
    string addValue(string,tokenType);

    /**Obtiene el QJsonObject asociado al objeto
     *
     * @return
     */
    QJsonObject* get();

    /**Obtiene el valor asociado a una llave específica
     *
     * @param key
     * @return
     */
    string get(string key);

    /**
     * Crea el request específico y lo pasa al ServerConnections
     */
    void submit();

    /**Obtiene la version en string del objeto JSON
     *
     * @return
     */
    string toString();

    string addValueUnchecked(string value);

};

#endif //CODEPARSER_VARIABLE_H
