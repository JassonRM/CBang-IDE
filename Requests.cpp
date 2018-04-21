//
// Created by marco on 14/04/18.
//

#include "Requests.h"

ServerConnection* Requests::server = ServerConnection::getServerConnection();

QJsonDocument* Requests::request(string identifier,string request){
    Json* json = new Json();
    json->put("Request",request);
    json->put("Identifier",identifier);
    QJsonDocument* document = new QJsonDocument(*json->get());
    delete (json);
    QJsonDocument* response = (server->request(document));
    delete(document);
    return response;
}

bool Requests::isVariable(string identifier) {
    QJsonDocument* document = request(identifier, "Is Variable");
    if (document->object().value("Result").isUndefined()){
        return false;
    }
    return document->object().value("Result").toBool();
}

bool Requests::isStruct(string identifier) {
    QJsonDocument* document = request(identifier, "Is Struct");
    if (document->object().value("Result").isUndefined()){
        return false;
    }
    return document->object().value("Result").toBool();
}

string Requests::variableType(string identifier){
    QJsonDocument* document = request(identifier, "Get Type");
    string value = document->object().value("Type").toString(" ").toStdString();
    return value;
}

Json* Requests::variableValue(string identifier) {
    Json* json = new Json();

    QJsonDocument* document = request(identifier, "Get Value");
    string type = document->object().value("Type").toString("").toStdString();
    if(type == ""){
        return nullptr;
    } else if (type == "int"){
        int value = document->object().value("Value").toInt();
        json->put("Value",std::to_string(value));
    }
    else if(type == "char"){
        int value = document->object().value("Value").toInt();
        char charValue = value;
        json->put("Value",charValue);
    }
    else if(type == "double"){
        double value = document->object().value("Value").toDouble();
        json->put("Value",std::to_string(value));
    }
    else if(type == "float"){
        float value = (float)document->object().value("Value").toDouble();
        json->put("Value",std::to_string(value));
    }
    else if(type == "long"){
        long value = boost::lexical_cast<long>(document->object().value("Value").toString().toStdString());
        json->put("Value",std::to_string(value));
    }
    json->put("Identifier",identifier);
    json->put("Type",type);
    string a = json->toString();
    return json;

}
Json* Requests::variableAddress(string identifier){
    QJsonDocument* document = request(identifier, "Get Address");
    int address = document->object().value("Address").toInt(-1);
    string type = document->object().value("Type").toString().toStdString();
    if (address == -1){
        return nullptr;
    }
    Json* json = new Json();
    json->put("Identifier",identifier);
    json->put("Address",to_string(address));
    json->put("Type",type);
    return json;
}

Json* Requests::referenceValue(string identifier){
    QJsonDocument* document = request(identifier, "Get Reference Value");
    QJsonValue value= document->object().value("Value");
    QJsonValue type = document->object().value("Type");
    if (value.isUndefined()){
        return nullptr;
    }
    Json* json = new Json();
    json->put("Identifier",identifier);
    json->putJsonValue("Value",value);
    json->putJsonValue("Type",type);
    return json;
    }


Json* Requests::newVariable(Json *request) {
    string type = request->get("Type");
    if (request->get("Request") == "Change Value"){
        request->arithmeticSolver();
    }else if(request->get("Struct") == "true"){
        request->get()->remove("Struct");
        if (request->get("Value") == ""){
            request->put("Request", "New Struct");
        }else{
            request->put("Request", "Copy Struct");
        }
    }else if( type == "Reference int" || type == "Reference char" || type == "Reference double" ||
            type == "Reference float" || type == "Reference long"){
        request->put("Request", "New Reference");
    }else{
        request->put("Request","New Variable");
        request->arithmeticSolver();
    }

    QJsonDocument* document = new QJsonDocument(*request->get());
    server->request(document);
    return nullptr;
}

Json* Requests::defineStruct(JsonArray *request) {
    request->put("Request","Define Struct");
    QJsonDocument* document = new QJsonDocument(*request->get());
    server->request(document);
    return nullptr;
}

void Requests::closeScope(int scope) {
    Json *json = new Json();
    json->put("Request", "Close Scope");
    json->put("Scope", scope);
    QJsonDocument *document = new QJsonDocument(*json->get());
    server->request(document);
}