//
// Created by marco on 07/04/18.
//

#include "Structure.h"

void Structure::add(Variable* var){
    QJsonValue value = QJsonValue(*var->get());
    this->variables->append(value);
}

void Structure::put(string key,string value){
    QJsonValue *jsonValue = new QJsonValue(QString::fromStdString(value));
    this->json->insert(QString::fromStdString(key),*jsonValue);
    delete(jsonValue);
}

void Structure::submit() {
    QJsonValue *jsonValue = new QJsonValue(*variables);
    this->json->insert("Variables",*jsonValue);
    delete(jsonValue);
    //TODO request
    cout << this->toString() <<endl;

}

string Structure::toString(){
    QJsonDocument doc(*this->json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson.toStdString();
}