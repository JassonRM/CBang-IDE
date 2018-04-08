//
// Created by marco on 28/03/18.
//

#include "Parser.h"
#include "Structure.h"

vector<Token*>* tokens = nullptr;

void parse(string code){

    if (tokens == nullptr){
        tokens = lex(code);
    }

    parse(tokens);

}


void parse(vector<Token*>* tokens){
    int tokensDropped = 0;

    int FULL_REFERENCE = REFERENCE*OPEN_REFERENCE_SEPARATOR*DATA_TYPE*CLOSE_REFERENCE_SEPARATOR;

    Variable* currentVar = nullptr;
    Structure* structure = nullptr;

    int count = 1;
    for (auto && token:*tokens) {
        tokensDropped++;
        if (token->type == DATA_TYPE || token->type == REFERENCE){
            if (count == REFERENCE*OPEN_REFERENCE_SEPARATOR){
                string newType = currentVar->get("Type");
                newType.append(" ").append(token->value);
                currentVar->put("Type",newType);
                count *= DATA_TYPE;
                continue;
            }

            else if (count != 1 && structure == nullptr){
                cerr << "invalid syntax"<<endl;
                return;
            }
            count *= token->type;
            currentVar = new Variable();
            currentVar->put("Type",token->value);
            currentVar->put("Scope",currentScope);

        }else if (token->type == IDENTIFIER){
            //TODO validate already existing variable
            if (count == DATA_TYPE || count == FULL_REFERENCE){

                currentVar->put("Identifier",token->value);

            }else if (count % ASSIGNMENT == 0) {
                currentVar->addValue(token->value,token);
            }else if(structure != nullptr){
                structure->put("Identifier", token->value);
            //}else if(findStructure() != nullptr){
            }else{

            }

            count *= IDENTIFIER;
        }else if (token->type == ASSIGNMENT){
            if (count == DATA_TYPE*IDENTIFIER ||
                count == IDENTIFIER || count == FULL_REFERENCE*IDENTIFIER){
                count *= ASSIGNMENT;
            }
            else{
                delete(currentVar);
                cerr << count<<endl;
                return;
            }
        }else if (token->type == LITERAL){
            if (count % (DATA_TYPE*IDENTIFIER*ASSIGNMENT) == 0 ||
                count % (IDENTIFIER*ASSIGNMENT) == 0 || count % (FULL_REFERENCE*IDENTIFIER*ASSIGNMENT) == 0){
                currentVar->addValue(token->value,token);
            }else{
                cerr<<"invalid syntax"<<endl;
                return;
            }

        }else if (token->type == LINE_SEPARATOR){
            //currentVar->set();
            if(structure == nullptr){
                cout <<currentVar->toString()<<endl;

            }else if (currentVar == nullptr){
                structure->submit();
                delete(structure);
                structure = nullptr;

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
            count = 1;
            break;



            //varTable->push_back(currentVar);

            //TODO step


        }else if (token->type == OPERATOR){
            if(currentVar != nullptr){
                currentVar->addValue(token->value,token);
            }
        }else if (token->type == OPEN_REFERENCE_SEPARATOR){
            if (count == REFERENCE){
                count *= OPEN_REFERENCE_SEPARATOR;
            }else{
                cerr <<"syntax error"<<endl;
            }
        }else if (token->type == CLOSE_REFERENCE_SEPARATOR){
            if (count == REFERENCE*OPEN_REFERENCE_SEPARATOR*DATA_TYPE){
                count *= CLOSE_REFERENCE_SEPARATOR;
            }else{
                cerr <<"syntax error"<<endl;
            }
        }else if(token->type == OPEN_SCOPE){
            if (structure != nullptr){

            }else{currentScope++;}
        }
        else if(token->type == CLOSE_SCOPE){
            if (structure != nullptr){

            }else{
                //closeScope(currentScope);
                currentScope--;}

        }
        else if(token->type == STRUCT){
            if (count != 1){
                cout<<"syntax error"<<endl;
                return;
            }
            structure = new Structure();
        }
        else if(token->type == END_LINE){
            continue;
        }
        else{
            cout<<"syntax error"<<endl;
            return;
        }

    }
    tokens->erase(tokens->begin(),tokens->begin()+tokensDropped);
    if ((currentVar != nullptr || currentScope != 0) && tokens->size() == 0){
        cerr << "Semicolon missing"<<endl;
    }else if(structure != nullptr){
        cerr <<"} missing"<<endl;
    }


}

vector<Token*>* lex(string code){
    using namespace boost;
    typedef tokenizer<char_separator<char>> tokenizer;

    char_separator<char> sep(" ","\n+-/*%;{}<>()",drop_empty_tokens);

    vector<Token*>* result = new vector<Token*>();

    tokenizer tokens(code,sep);
    for(tokenizer::iterator beg=tokens.begin(); beg!=tokens.end();++beg){

        result->push_back(new Token(*beg));
    }
    return result;
}

