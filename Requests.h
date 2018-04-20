//
// Created by marco on 14/04/18.
//

#ifndef CFACTORIAL_IDE_REQUESTS_H
#define CFACTORIAL_IDE_REQUESTS_H

#include <iostream>
#include <QtCore/QJsonDocument>
#include "Json.h"
#include "ServerConnection.h"
#include "tinyexpr.h"
#include "JsonArray.h"

using namespace std;

/**Representa una interfaz que facilita la creación de los
 * requests para ser enviados al servidor
 *
 */
class Requests {

private:
    static ServerConnection* server;
    static QJsonDocument* request(string, string);

public:

    /**Verifica si una variable existe en memoria
     *
     * @param identifier
     * @return
     */
    static bool isVariable(string identifier);

    /**Verifica si una estructura existe en memoria
     *
     * @param identifier
     * @return
     */
    static bool isStruct(string identifier);

    /**Obtiene el tipo del valor que almacena una variable
     *
     * @param identifier
     * @return
     */
    static string variableType(string identifier);

    /**Obtiene el valor que almacena una variable
     *
     * @param identifier
     * @return
     */
    static Json* variableValue(string identifier);

    /**Obtiene la posición relativa de memoria en la que
     * se encuentra una variable
     *
     * @param identifier
     * @return
     */
    static Json* variableAddress(string identifier);

    /**Obtiene el valor de la variable a la que apunta
     * una referencia
     *
     * @param identifier
     * @return
     */
    static Json* referenceValue(string identifier);

    static Json* newVariable(Json* request);

    static Json* defineStruct(JsonArray* request);

};



#endif //CFACTORIAL_IDE_REQUESTS_H
