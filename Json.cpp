//
// Created by marco on 27/03/18.
//

#include "Json.h"
#include "Requests.h"
void Json::put(string key,string value){
    QJsonValue *jsonValue = new QJsonValue(QString::fromStdString(value));
    this->json->insert(QString::fromStdString(key),*jsonValue);
    delete(jsonValue);
}
void Json::put(string key,int value){
    QJsonValue *jsonValue = new QJsonValue(value);
    this->json->insert(QString::fromStdString(key),*jsonValue);
    delete(jsonValue);
}

void Json::putJsonValue(string key,QJsonValue value){
    this->json->insert(QString::fromStdString(key),value);
}


string Json::addValue(string value, Token* token){
    string response = " ";
    if (token->type == IDENTIFIER){
        Json* var = Requests::variableValue(token->value);
        if (var == nullptr){
            response = "variable doesn't exist";
            return response;
        }
        else if (var->get("Type") != this->get("Type") && this->get("Type") != ""){
            response = "types don't match";
            return response;
        }
        value = var->get("Value");
    }else if (token->type == LITERAL) {

        if (this->get("Type") == "long") {
            try {
                boost::lexical_cast<long>(value);
            } catch (boost::bad_lexical_cast) {
                response = "Error in line" + to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                           "\" is not of type long\n";
                return response;
            }
        } else if (this->get("Type") == "int") {
            try {
                int value = boost::lexical_cast<int>(value);
            } catch (boost::bad_lexical_cast) {
                response = "Error in line" + to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                           "\" is not of type int\n";
                return response;
            }
        } else if (this->get("Type") == "float") {
            try {
                boost::lexical_cast<float>(value);
            } catch (boost::bad_lexical_cast) {
                response = "Error in line" + to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                           "\" is not of type float\n";
                return response;
            }
        } else if (this->get("Type") == "double") {
            try {
                boost::lexical_cast<double>(value);
            } catch (boost::bad_lexical_cast) {
                response = "Error in line" + to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                           "\" is not of type double\n";
                return response;
            }
        } else if (this->get("Type") == "char") {
            if (!regex_match(value, regex("\'[A-Za-z]\'"))) {
                response = "Error in line" + to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                           "\" is not of type double\n";
                return response;
            }

        }
    }else if (token->type == OPERATOR) {
            string type = this->get("Type");
            if (type != "int" && type != "double" && type != "float" && type != "long" && type != "") {
                response = "Error in line" + to_string(token->line) + " : Can't use <" + token->value +
                           "> operator with non numeric data type\n";
                return response;
            }
    }
    this->put("Value", this->get("Value").append(value));
    return response;
}

QJsonObject* Json::get(){
    return this->json;
}

string Json::get(string key){

    const QJsonValue &jsonValue = json->value(QString::fromStdString(key));
    if (jsonValue.isUndefined()){
        return "";
    }
    return jsonValue.toString().toStdString();
}

string Json::toString(){
    QJsonDocument doc(*this->json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson.toStdString();
}

void Json::submit() {
    if(this->get("Request")== "Change Value"){
        cout <<this->toString()<<endl;
        return;
    }
    this->put("Request", "New Variable");
    cout <<this->toString()<<endl;
}

string Json::addValue(string value, tokenType type){
    Token* token = new Token(value,type);
    string response = addValue(value,token);
    delete(token);
    return response;
}
