//
// Created by marco on 07/04/18.
//

#include "JsonArray.h"

void JsonArray::add(Json* var){
    QJsonValue value = QJsonValue(*var->get());
    this->variables->append(value);
}

void JsonArray::put(string key,string value){
    QJsonValue *jsonValue = new QJsonValue(QString::fromStdString(value));
    this->json->insert(QString::fromStdString(key),*jsonValue);
    delete(jsonValue);
}

void JsonArray::put(string key,int value){
    QJsonValue *jsonValue = new QJsonValue(value);
    this->json->insert(QString::fromStdString(key),*jsonValue);
    delete(jsonValue);
}

void JsonArray::submit() {
    QJsonValue *jsonValue = new QJsonValue(*variables);
    this->json->insert("Variables",*jsonValue);
    delete(jsonValue);
    this->put("Request", "Define Struct");

}

string JsonArray::toString(){
    QJsonDocument doc(*this->json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson.toStdString();
}

QJsonObject* JsonArray::get(){
    return this->json;
}