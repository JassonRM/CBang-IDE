//
// Created by marco on 28/03/18.
//

#include "Parser.h"
#include "loguru.hpp"

vector<Token*>* tokens = nullptr;

void parseString(string code, MainWindow* window){
    windowReference = window;
    tokens = lex(code);
    parse(tokens);
    QFile file("/home/marco/everything.log");
    file.open(QIODevice::ReadOnly);
    string response;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (line == "\n"){
            continue;
        }
        response.append(line);
        response.append("\n");
    }
    windowReference->appLog(response);
    file.close();
}

void step(){
    if (tokens == nullptr){
        return;
    }
    parse(tokens);
    QFile file("/home/marco/everything.log");
    file.open(QIODevice::ReadOnly);
    string response;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (line == "\n"){
            continue;
        }
        response.append(line);
        response.append("\n");
    }
    windowReference->appLog(response);
    file.close();

}



void parse(vector<Token*>* tokens){

    int tokensDropped = 0;

    int FULL_REFERENCE = REFERENCE*OPEN_REFERENCE_SEPARATOR*DATA_TYPE*CLOSE_REFERENCE_SEPARATOR;

    Json* currentVar = nullptr;
    JsonArray* structure = nullptr;

    Json* printer = nullptr;
    bool printing = false;

    vector<tokenType>* functions = new vector<tokenType>();
    int parenthesis = 0;
    int count = 1;


    for (auto && token:*tokens) {
        tokensDropped++;
        if (!functions->empty()){
            tokenType function = functions->back();
            if (function == ADDRESS){
                if (token->type == OPERATOR){
                    if(token->value == "("){
                        parenthesis++;
                    }
                    else if(token->value == ")"){
                        parenthesis--;
                        if (parenthesis == 0){
                            functions->pop_back();
                        }
                    }else{
                        LOG_F(ERROR,"Operator error");
                        return;
                    }
                }
                else if(token->type == IDENTIFIER){
                    if (parenthesis <= 0){
                        LOG_F(ERROR,"Parenthesis error");
                        break;
                    }else{
                        if (currentVar != nullptr) {
                                Json* response = Requests::variableAddress(token->value);
                                if (currentVar->get("Type") == "Reference " + response->get("Type")){
                                    currentVar->addValueUnchecked(response->get("Address"));
                                    delete(response);
                                    continue;
                                }
                                else{
                                    LOG_F(ERROR,"Types don't match ");
                                    return;
                                }

                        }else if (printing){
                            string response = printer->addValue(Requests::variableAddress(token->value)->get("Address"),LITERAL);
                            if (response != " "){
                                return;
                            }
                        }
                    }
                }
                else{
                    LOG_F(ERROR,"UNKNOWN ERROR");
                    break;
                }

            }else if (function == VALUE){
                if (token->type == OPERATOR){
                    if(token->value == "("){
                        parenthesis++;
                    }
                    else if(token->value == ")"){
                        parenthesis--;
                        if (parenthesis == 0){
                            functions->pop_back();
                        }
                    }else {
                        LOG_F(ERROR,"Operator error");
                        return;
                    }
                }
                else if(token->type == IDENTIFIER){
                    if (parenthesis <= 0){
                        LOG_F(ERROR,"Parenthesis error");
                        break;
                    }else{
                        if (currentVar != nullptr) {
                            Json* response = Requests::referenceValue(token->value);
                            if (currentVar->get("Type") == response->get("Type")){
                                currentVar->addValueUnchecked(response->get("Value"));
                                delete(response);
                            }
                            else{
                                LOG_F(ERROR,"UNKNOWN ERROR");
                                return;
                            }

                        }else if (printing){
                            string response = printer->addValue(Requests::referenceValue(token->value)->get("Value"),LITERAL);
                            if (response != " "){
                                LOG_F(ERROR,"UNKNOWN ERROR");
                                return;
                            }
                        }else{
                            LOG_F(ERROR,"UNKNOWN ERROR");
                            break;
                        }
                    }
                }
                else{
                    LOG_F(ERROR,"UNKNOWN ERROR");
                    break;
                }
            }else if(function == PRINT){
                if (token->type == OPERATOR){
                    if(token->value == "("){
                        parenthesis++;
                    }
                    else if(token->value == ")"){
                        if (parenthesis == 0){
                            return;
                        }
                        parenthesis--;

                    }else{
                        printer->addValue(token->value,OPERATOR);
                    }
                }
                else if(token->type == IDENTIFIER){
                    if (parenthesis <= 0){
                        LOG_F(ERROR,"Parenthesis error");
                        break;
                    }else{
                        printer->addValue(token->value,token);
                    }
                }else if(token->type == LITERAL){
                    printer->addValue(token->value,token);
                }
                else if(token->type == LINE_SEPARATOR){
                    if (parenthesis == 0 && printer->get("Value") != ""){
                        string a = printer->toString();
                        windowReference->stdOut1(printer->get("Value"));
                    }else{
                        LOG_F(ERROR,"UNKNOWN ERROR");
                        return;
                    }
                }
                else if(token->type == ADDRESS){
                    functions->push_back(ADDRESS);
                }else if(token->type == VALUE){
                    functions->push_back(VALUE);
                }else{
                    LOG_F(ERROR,"UNKNOWN ERROR");
                    break;
                }
            }

        }
        else if (token->type == DATA_TYPE || token->type == REFERENCE){
            if (count == REFERENCE*OPEN_REFERENCE_SEPARATOR){
                string newType = "Reference";
                newType.append(" ").append(token->value);
                currentVar->put("Type",newType);
                count *= DATA_TYPE;
                continue;
            }

            else if (count != 1 && structure == nullptr){
                string err = "Error in line" + to_string(token->line) + " : Wrong use of keyword <" + token->value +">";
                LOG_F(ERROR,err.data());
                return;
            }
            count *= token->type;
            currentVar = new Json();
            currentVar->put("Type",token->value);
            currentVar->put("Scope",currentScope);

        }else if (token->type == IDENTIFIER){

            if (count == DATA_TYPE || count == FULL_REFERENCE){
                if (Requests::isVariable(token->value) || Requests::isStruct(token->value)){
                    return;

                }
                currentVar->put("Identifier",token->value);

            }else if (count % ASSIGNMENT == 0) {
                string response = currentVar->addValue(token->value,token);
                if (response != " "){
                    return;
                }
            }else if(structure != nullptr && currentVar == nullptr) {
                structure->put("Identifier", token->value);
            }
            else if(count == 1){
                if (Requests::isStruct(token->value)){
                    currentVar = new Json();
                    currentVar->put("Type",token->value);
                    currentVar->put("Scope",currentScope);
                    currentVar->put("Struct","true");
                    currentVar->put("Scope",currentScope);
                    count *= DATA_TYPE;
                    continue;
                }else if(Requests::isVariable(token->value)){
                    string type = Requests::variableType(token->value);
                    currentVar = new Json();
                    currentVar->put("Identifier",token->value);
                    currentVar->put("Request", "Change Value");
                    currentVar->put("Type",type);
                }

            }else{
                return;
            }

            count *= IDENTIFIER;
        }else if (token->type == ASSIGNMENT){
            if (count == DATA_TYPE*IDENTIFIER ||
                count == IDENTIFIER || count == FULL_REFERENCE*IDENTIFIER){
                count *= ASSIGNMENT;
            }
            else{
                delete(currentVar);
                string err = ("Error in line" + to_string(token->line) + " : Assignment operator \"=\" out of context\n");
                LOG_F(ERROR,err.data());
                return;
            }
        }else if (token->type == LITERAL){
            if (count % (DATA_TYPE*IDENTIFIER*ASSIGNMENT) == 0 ||
                count % (IDENTIFIER*ASSIGNMENT) == 0 || count % (FULL_REFERENCE*IDENTIFIER*ASSIGNMENT) == 0){
                string response = currentVar->addValue(token->value,token);
                if (response != " "){
                    return;
                }
            }else{
                string err ="Error in line" + to_string(token->line) + " : Literal <"+token->value + "> out of context\n";
                LOG_F(ERROR,err.data());
                return;
            }

        }else if (token->type == LINE_SEPARATOR){
            if(structure == nullptr && currentVar != nullptr){
                Requests::newVariable(currentVar);
            }else if (currentVar == nullptr && structure != nullptr){
                structure->submit(); // adds variables
                Requests::defineStruct(structure);
                delete(structure);
                structure = nullptr;
            }
            else if(printing){
                cout << printer->toString()<< endl;
                delete(printer);
                printer = nullptr;
                break;

            }
            else{
                structure->add(currentVar);
                delete(currentVar);
                currentVar = nullptr;
                count = 1;
                continue;
            }
            delete(currentVar);
            currentVar = nullptr;
            break;

        }else if (token->type == OPERATOR){

            if(currentVar != nullptr){
                string response = currentVar->addValue(token->value,token);
                if (response != " "){

                    return;
                }
            }
        }else if (token->type == OPEN_REFERENCE_SEPARATOR){
            if (count == REFERENCE){
                count *= OPEN_REFERENCE_SEPARATOR;
            }else{
                string err ="Error in line" + to_string(token->line) + " : Wrong use of \"<\"\n";
                LOG_F(ERROR,err.data());
                return;
            }
        }else if (token->type == CLOSE_REFERENCE_SEPARATOR){
            if (count == REFERENCE*OPEN_REFERENCE_SEPARATOR*DATA_TYPE){
                count *= CLOSE_REFERENCE_SEPARATOR;
            }else{
                string err ="Error in line" + to_string(token->line)+ " : Wrong use of \">\"\n";
                LOG_F(ERROR,err.data());
                return;
            }
        }else if(token->type == OPEN_SCOPE){
            if (count == STRUCT){
                structure = new JsonArray();
                structure->put("Scope",currentScope);
                count = 1;
            }else{currentScope++;}
        }
        else if(token->type == CLOSE_SCOPE){
            if (structure != nullptr){

            }else{
                Requests::closeScope(currentScope);
                currentScope--;
            }

        }
        else if(token->type == STRUCT){
            if (count != 1){
                string err = "Error in line" + to_string(token->line)+ " : Wrong use of keyword <struct>\n";
                LOG_F(ERROR,err.data());
                return;
            }
            count *= STRUCT;

        }
        else if(token->type == END_LINE){
            continue;
        }else if(token->type == ADDRESS){
            functions->push_back(ADDRESS);
        }else if(token->type == PRINT){
            functions->push_back(PRINT);
            printer = new Json();
            printing = true;
        }else if(token->type == VALUE) {
            functions->push_back(VALUE);
        } else{
            string err = "Error in line" + to_string(token->line) + "\n";
            LOG_F(ERROR,err.data());
            return;
        }
    }
    tokens->erase(tokens->begin(),tokens->begin()+tokensDropped);
    if (currentVar != nullptr && tokens->size() == 0) {
        string err = "<;> missing : Unfinished variable\n";
        LOG_F(ERROR,err.data());
        return;
    }else if(currentScope != 0 && tokens->size() == 0){
        string err = "<}> missing : Scope not closed\n";
        LOG_F(ERROR,err.data());
        return;
    }else if(structure != nullptr){
        string err ="<}> or <;> missing : Unfinished structure\n";
        LOG_F(ERROR,err.data());
        return;
    }


}

vector<Token*>* lex(string code){
    using namespace boost;
    typedef tokenizer<char_separator<char>> tokenizer;

    char_separator<char> sep(" ","\n+-/*%;{}<>=()\t",drop_empty_tokens);

    vector<Token*>* result = new vector<Token*>();

    tokenizer tokens(code,sep);
    Token::lineNum = 1;
    for(tokenizer::iterator beg=tokens.begin(); beg!=tokens.end();++beg){

        result->push_back(new Token(*beg));
    }
    return result;
}

