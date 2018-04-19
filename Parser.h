//
// Created by marco on 28/03/18.
//

#ifndef CODEPARSER_PARSER_H
#define CODEPARSER_PARSER_H

#include <iostream>
#include <vector>
#include "Token.h"
#include "Json.h"
#include <boost/tokenizer.hpp>
#include <QJsonObject>
#include "JsonArray.h"
#include "MainWindow.h"
#include "ServerConnection.h"
#include "Requests.h"
using namespace std;

class MainWindow;

static int currentScope = 0;
static MainWindow* windowReference = nullptr;
static ServerConnection* server = ServerConnection::getServerConnection();

/**Ejecuta las funciones lex y parse
 *
 * @param code
 * @param window ventana para mostrar errores
 */
void parseString(string code, MainWindow* window);

/**
 * Analiza la secuencia de tokens y crea Requests según
 * se necesitan
 *
 * @param tokens
 */
void parse(vector<Token*>* tokens);

void step();

/**Se encarga de obtener la lista de tokens a partir del codigo
 * por parsear en forma de string
 *
 * @param code
 * @return
 */
vector<Token*>* lex(string code);




#endif //CODEPARSER_PARSER_H
