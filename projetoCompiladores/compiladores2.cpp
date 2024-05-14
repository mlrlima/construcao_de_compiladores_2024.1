#include "../../projetoCompiladores/includes.hpp";

void programa(); //principal, q eh chamada pelo outro arquivo

bool ehTipo(string t);
vector<string> tipo{"int", "float", "double", "char", "bool", "boolean"};

bool declaracao();
bool declaracaoVariavel();
bool declaracaoFuncao();
bool declaracaoEstrutura();
//bool comentario();

bool expressao();
bool atribuicao();

bool parametros();
bool parametro();

bool bloco();

bool estruturaControle();

int onde2;
int qtdTokens=tokens.size();

bool bloco(){
    onde2++;
    if(token[onde2].first=='{'){
        if(token[onde2+1].first=='}'){
            onde++;
            return true;
        }

        if(declaracao()){
            onde++;
            if(token[onde2].first=='}'){
                return true;
            }
        }
    }

    return false;
}

bool parametro(){
    onde2++;
    if(ehTipo(token[onde2].first)){
        onde2++;
        if(token[onde2].second=="Identificador"){
            if(token[onde2+1].first=='[' && token[onde2+2].first==']'){
                onde+=2;
            }
            return true;
        }
    }
    return false;
}

bool parametros(){
    if(parametro()){
        if(tokens[onde2+1].first==","){
            onde2++;
            if(parametros()){
                return true;
            }
        }
        else{
            return true;
        }
    }
    return false;
}

bool ehTipo(string t){
    for(int i=0;i<tipo.size();i++){
        if(t==tipo[i]){
            return true;
        }
    }

    return false;
}

bool atribuicao(){
    onde2++;
    if(tokens[onde2].second=="Identificador"){
        onde2++;
        if(tokens[onde2].first=="="){
            if(expressao()){
                return true;
            }

            onde2++;

            if(tokens[onde2].second=="Identificador"){
                return true;
            }
            else if(ehOperadores2(tokens[onde2].first)){
                if(expressao()){
                    return true;
                }
                onde2++;
                if(tokens[onde2].second=="Identificador"){
                    return true;
                }
            }
        }
    }

    return false;
}

bool expressao(){
    if(atribuicao() || expressaoLogica()){
        return true;
    }

    return false;
}

bool declaracaoFuncao(){
    onde2++;
    if(ehTipo(tolkens[onde2].first)){
        onde2++;
        if(tolkens[onde2].second=="Identificador"){
            onde2++;
            if(tolkens[onde2].first=="(" && parametros()){
                onde2++;
                if(tolkens[onde2].first==")" && bloco()){
                    return true;
                }
            }
        }
    }
    return false;
}

bool declaracaoVariavel(){
    if(ehTipo(tokens[onde2].first) && tokens[onde2+1].second=="Identificador"){
        onde2+=2;
        if(tokens[onde2].first==";"){
            onde2++;
            return true;
        }
        else if(tokens[onde2].first=="="){
            onde2++;
            if(expressao()){
                onde2++;
                return true;
            }
        }
    }

    return false;
}

bool estruturaControle(){
    onde2++;
    if(tokens[onde2].first=="if" && tokens[onde2+1].first=="("){
        onde2++;
        if(expressao()){
            onde2++;
            if(tokens[onde2+1].first==")" && bloco()){
                if(tokens[onde2+1].first=="else"){
                    onde2++;
                    if(bloco()){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                return true;
            }
        }
    }
    else if(tokens[onde2].first=="while" && tokens[onde2+1].first=="("){
        onde2++;
        if(expressao()){
            onde2++;
            if(tokens[onde2+1].first==")" && bloco()){
                onde2++;
                return true;
            }
        }
    }
    else if(tokens[onde2].first=="for" && tokens[onde2+1].first=="("){
        onde2++;
        if(expressao()){
            onde2++;
            if(tokens[onde2].first==";"){
                if(expressao()){
                    onde2++;
                    if(tokens[onde2].first==";"){
                        if(expressao()){
                            onde2++;
                            if(tokens[onde2].first==")" && bloco()){
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    else if(tokens[onde2].first=="switch" && tokens[onde2+1].first=="("){
        onde2++;
        if(expressao()){
            onde2++;
            if(tokens[onde2].first==")" && caseLista()){
                return true;
            }
        }
    }
    else if(tokens[onde2].first=="break" && tokens[onde2+1].first==";"){
        onde2++;
        return true;
    }
    else if(tokens[onde2].first=="continue" && tokens[onde2+1].first==";"){
        onde2++;
        return true;
    }
    else if(tokens[onde2].first=="return" && expressao()){
        onde2++;
        if(tokens[onde2].first==";"){
            return true;
        }
    }

    return false;
}

bool declaracao(){
    if(declaracaoVariavel() || declaracaoFuncao() || declaracaoEstrutura()){
        return true;
    }

    return false;
}

bool programa(){
    
    onde2=-1;

    if(declaracao()){
        return true;
    }

    return false;

}
