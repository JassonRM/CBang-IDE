//
// Created by marco on 27/03/18.
//

#include "Json.h"
#include "Requests.h"
#include <loguru.hpp>

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

void Json::put(string key,double value){
    QJsonValue *jsonValue = new QJsonValue(value);
    this->json->insert(QString::fromStdString(key),*jsonValue);
    delete(jsonValue);
}

void Json::put(string key,float value){
    QJsonValue *jsonValue = new QJsonValue(value);
    this->json->insert(QString::fromStdString(key),*jsonValue);
    delete(jsonValue);
}

void Json::put(string key,long value){
    QJsonValue *jsonValue = new QJsonValue(qint64(value));
    this->json->insert(QString::fromStdString(key),*jsonValue);
    delete(jsonValue);
}

void Json::putJsonValue(string key,QJsonValue value){
    this->json->insert(QString::fromStdString(key),value);
}


string Json::addValue(string value, Token* token){
    if (this->get("Struct") == "true"){
        if (token->type != IDENTIFIER || !Requests::isVariable(value)
                || Requests::variableType(value) != this->get("Type")
                || this->get("Value") != ""){

            LOG_F(ERROR,"UNKNOWN ERROR");
            return "";
        }
        this->put("Value", value);
        return " ";

    }
    string response = " ";
    if (token->type == IDENTIFIER){
        Json* var = Requests::variableValue(token->value);

        if(this->get("Type") == ""){
            this->put("Type",var->get("Type"));
        }

        if (var->get("Value") == ""){
            response = "variable" +token->value+ "doesn't exist";
            LOG_F(ERROR,response.data());
            return response;
        }
        else if (var->get("Type") != this->get("Type")){
            response = "Types don't match";
            LOG_F(ERROR,response.data());
            return response;
        }
        value = var->get("Value");
    }else if (token->type == LITERAL) {

        if (this->get("Type") == "long") {
            try {
                boost::lexical_cast<long>(value);
            } catch (boost::bad_lexical_cast) {
                response = "Error in line" + to_string(token->line) + " : Variable \"" + this->get("Identifier") + "\" is not of type long";
                LOG_F(ERROR,response.data());
                return response;
            }
        } else if (this->get("Type") == "int") {
            try {
                boost::lexical_cast<int>(value);
            } catch (boost::bad_lexical_cast) {
                response = "Error in line" + to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                           "\" is not of type int\n";
                LOG_F(ERROR,response.data());
                return response;
            }
        } else if (this->get("Type") == "float") {
            try {
                boost::lexical_cast<float>(value);
            } catch (boost::bad_lexical_cast) {
                response = "Error in line" + to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                           "\" is not of type float\n";
                LOG_F(ERROR,response.data());
                return response;
            }
        } else if (this->get("Type") == "double") {
            try {
                boost::lexical_cast<double>(value);
            } catch (boost::bad_lexical_cast) {
                response = "Error in line" + to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                           "\" is not of type double";
                LOG_F(ERROR,response.data());
                return response;
            }
        } else if (this->get("Type") == "char") {
            if (!regex_match(value, regex("\'.\'"))) {
                response = "Error in line" + to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                           "\" is not of type char";
                LOG_F(ERROR,response.data());
                return response;
            }

        }
    }else if (token->type == OPERATOR) {
            string type = this->get("Type");
            if(this->get("Value") == ""){
                LOG_F(ERROR,"UNKNOWN ERROR");
                return "ERROR";
            }
            if (type != "int" && type != "double" && type != "float" && type != "long" && type != "") {
                response = "Error in line" + to_string(token->line) + " : Can't use <" + token->value +
                           "> operator with non numeric data type\n";
                LOG_F(ERROR,response.data());
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

string Json::addValue(string value, tokenType type){
    Token* token = new Token(value,type);
    string response = addValue(value,token);
    delete(token);
    return response;
}

string Json::addValueUnchecked(string value){
    this->put("Value", this->get("Value").append(value));
}

void Json::arithmeticSolver(){

    if (this->get("Type") == "int"){
        if (this->get("Value") != ""){
            int value = (int)te_interp(this->get("Value").data(),0);
            this->put("Value",value);
        }
    }
    else if (this->get("Type") == "double"){
        if (this->get("Value") != ""){
            double value = boost::lexical_cast<double>(this->get("Value"));
            this->put("Value",value);
        }
    }
    else if (this->get("Type") == "float"){
        if (this->get("Value") != ""){
            float value = boost::lexical_cast<float>(this->get("Value"));
            cout <<this->get("Value");
            this->put("Value",value);
        }
    }
    else if (this->get("Type") == "long"){
        if (this->get("Value") != ""){
            long value = (long)te_interp(this->get("Value").data(),0);
            this->put("Value",value);
        }
    }else{};
}