//
// Created by marco on 27/03/18.
//

#include "Variable.h"

void Variable::put(string key,string value){
    QJsonValue *jsonValue = new QJsonValue(QString::fromStdString(value));
    this->json->insert(QString::fromStdString(key),*jsonValue);
    delete(jsonValue);
}
void Variable::put(string key,int value){
    QJsonValue *jsonValue = new QJsonValue(value);
    this->json->insert(QString::fromStdString(key),*jsonValue);
    delete(jsonValue);
}


Variable* findVariable(string){
    return nullptr;
};

void Variable::addValue(string value, Token* token){
    //TODO only allow operators for numeric types
    if (token->type == IDENTIFIER){
        //TODO request value of identifier
        Variable* var = findVariable(token->value);
        if (var == nullptr){
            cerr << "variable doesn't exist"<<endl;
            return;
        }
        if (var->get("Type") != this->get("Type")){
            cout << "types don't match"<<endl;
            return;
        }
        value = var->get("Value");
    }else if (token->type == LITERAL){
        cout << "is "<<value <<" of type "<< this->get("Type")<<endl;
    }
    else if(token->type == OPERATOR){
        string type = this->get("Type");
        if (type != "int" && type != "double" && type != "float" && type != "long"){
            cerr <<"invalid syntax"<<endl;
            return;
        }
    }
    this->put("Value",this->get("Value").append(value));
    
}

QJsonObject* Variable::get(){

    return this->json;
}

string Variable::get(string key){

    const QJsonValue &jsonValue = json->value(QString::fromStdString(key));
    if (jsonValue.isUndefined()){
        return "";
    }
    return jsonValue.toString().toStdString();
}

string Variable::toString(){
    QJsonDocument doc(*this->json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson.toStdString();
}