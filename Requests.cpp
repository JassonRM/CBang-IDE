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
    document = (server->request(document));
}

bool Requests::isVariable(string identifier) {
    QJsonDocument* document = request(identifier, "Is Variable");
    return !document->object().isEmpty();

}

bool Requests::isStruct(string identifier) {
    QJsonDocument* document = request(identifier, "Is Struct");
    return !document->object().isEmpty();
}

string Requests::variableType(string identifier){
    QJsonDocument* document = request(identifier, "Get Type");
    QJsonValue value = document->object().value("Type");
    if (value.isUndefined()){
        return " ";
    }
    return value.toString().toStdString();
}

Json* Requests::variableValue(string identifier) {
    QJsonDocument* document = request(identifier, "Get Value");
    QJsonValue value = document->object().value("Value");
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
Json* Requests::variableAddress(string identifier){
    QJsonDocument* document = request(identifier, "Get Address");
    QJsonValue address = document->object().value("Address");
    QJsonValue type = document->object().value("Type");
    if (address.isUndefined()){
        return nullptr;
    }
    Json* json = new Json();
    json->put("Identifier",identifier);
    json->putJsonValue("Address",address);
    json->putJsonValue("Type",type);
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
