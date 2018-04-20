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
    return document;
}

bool Requests::isVariable(string identifier) {
    QJsonDocument* document = request(identifier, "Is Variable");
    QJsonObject value = document->object();
    if (value.isEmpty()){
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

void arithmeticSolver(Json* request){
    if (request->get("Type") == "int"){
        if (request->get("Value") != ""){
            int value = (int)te_interp(request->get("Value").data(),0);
            request->put("Value",value);
        }
    }
    else if (request->get("Type") == "double"){
        if (request->get("Value") != ""){
            double value = te_interp(request->get("Value").data(),0);
            request->put("Value",value);
        }
    }
    else if (request->get("Type") == "float"){
        if (request->get("Value") != ""){
            float value = (float)(request->get("Value").data(),0);
            request->put("Value",value);
        }
    }
    else if (request->get("Type") == "long"){
        if (request->get("Value") != ""){
            long value = (long)(request->get("Value").data(),0);
            request->put("Value",value);
        }
    }else{};
}

Json* Requests::newVariable(Json *request) {
    string type = request->get("Type");
    if (request->get("Request") == "Change Value"){
        arithmeticSolver(request);
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
        arithmeticSolver(request);
    }

    QJsonDocument* document = new QJsonDocument(*request->get());
    server->request(document);
    return nullptr;
}

Json* Requests::defineStruct(JsonArray *request) {
    request->put("Request","Define Struct");
    QJsonDocument* document = new QJsonDocument(*request->get());
    document = (server->request(document));
    return nullptr;
}

void Requests::closeScope(int scope) {
    Json *json = new Json();
    json->put("Request", "Close Scope");
    json->put("Scope", scope);
    QJsonDocument *document = new QJsonDocument(*json->get());
    delete (json);
    document = (server->request(document));
}