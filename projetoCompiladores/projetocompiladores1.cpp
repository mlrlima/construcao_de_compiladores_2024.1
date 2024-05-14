/* Primeira parte do Projeto Compiladores - Analisador Léxico
Nome: Maria Luiza Ribeiro de Lima
RA: 848982
*/
//#include<bits/stdc++.h>
#include "../../faculdade/projetoCompiladores/includes.hpp";


//verificar os tipos de acordo com os vetores abaixo
bool ehEspeciais(char a);
bool ehLetra(char a);
bool ehNumero(char a);
bool ehReservadas(string p);
bool ehOperadores1(char a);
bool ehOperadores2(string a);
void transformarNum(string n);

vector < pair <string, string> > tokens;
vector <string> RESERVADAS{"int", "float", "char", "double", "bool", "void", "if", "else", "for", "while", "scanf", "printf", "string", "continue", "break", "include", "return", "println","switch","case"};
vector <char> OPERADORES1{'+', '-', '*', '/', '%', '!', '>', '<', '=', '|', '&'};
vector <string> OPERADORES2{"+", "-", "*", "/", "%", "!", ">", "<", "=", "||", "&&", "+=", "-=", "==", "<=", ">=", "!=","/=","%=","*="};
vector <char> ESPECIAIS{'(', ')', '[', ']', '{', '}', ',', ';'};

bool ehEspeciais(char a){
    for(int i=0;i<ESPECIAIS.size();i++){
        if(a==ESPECIAIS[i]){
            return true;
        }
    }
    return false;
}

bool ehLetra(char a){
    if(a>='a' && a<='z'){
        return true;
    }
    
    if(a>='A' && a<='Z'){
        return true;
    }

    return false;
}

bool ehNumero(char a){
    for(int i=0;i<10;i++){
        if(a-'0'==i){
            return true;
        }
    }

    return false;
}

bool ehReservadas(string p){
    for(int i=0;i<RESERVADAS.size();i++){
        if(p==RESERVADAS[i]){
            return true;
        }
    }
    return false;
}

bool ehOperadores1(char a){
    for(int i=0;i<OPERADORES1.size();i++){
        if(a==OPERADORES1[i]){
            return true;
        }
    }
    return false;
}

bool ehOperadores2(string a){
    for(int i=0;i<OPERADORES2.size();i++){
        if(a==OPERADORES2[i]){
            return true;
        }
    }
    return false;
}

void transformarNum(string n){
    int i=1, s=n.size(), num=0;
    num+=(n[0]-'0');
    
    if(i==s){
        tokens.push_back(make_pair(n,"Numero inteiro"));
        cout<<num<<" - Numero inteiro"<<endl;
        return;
    }
    
    //cout<<"num"<<endl;
    while(n[i]!='.'){
        num*=10;
        num+=(n[i]-'0');
        
        i++;
        if(i==s){
            tokens.push_back(make_pair(n,"Numero inteiro"));
            cout<<num<<" - Numero inteiro"<<endl;
            return;
        }
    }

    double numd=num, dez=0.1, d;
    while(i<s){
        d=(n[i]-'0');
        d*=dez;
        dez*=0.1;
        numd+=d;
        
        i++;
    }
    
    tokens.push_back(make_pair(n,"Numero decimal"));
    cout<<n<<" - Numero decimal"<<endl;
    return;
}

int main(){

    string linha;
    int onde,linhasize;
    bool comentarioGrande=false;


    while(getline(cin,linha)){
        if(linha[0]=='\n' || linha==""){continue;}
        onde=0;
        linhasize=linha.size();

        if(comentarioGrande){
            for(int i=1;i<linhasize;i++){
                onde=i;
                if(linha[i-1]=='*' && linha[i]=='/'){
                    comentarioGrande=false;
                    break;
                }
            }
        }

        while(onde<linhasize){
            if(linha[onde]==' ' || linha[onde]=='\t'){
                onde++;
                continue;
            }
            
            //caso for um comentário, ignorar
            if(onde!=linhasize-1 && linha[onde]=='/' && linha[onde+1]=='/'){
                break;
            }
            if(onde!=linhasize-1 && linha[onde]=='/' && linha[onde+1]=='*'){
                comentarioGrande=true;
                break;
            }


            if(linha[onde]==34){
                vector <char> t;
                t.push_back(linha[onde]);

                do{
                    onde++;
                    t.push_back(linha[onde]);
                }while(linha[onde]!='"');

                string te(t.begin(), t.end());

                tokens.push_back(make_pair(te,"Texto"));
                cout<<te<<" - Texto"<<endl;
                onde++;
                continue;

            }

            if(ehEspeciais(linha[onde])){
                vector <char> e;
                e.push_back(linha[onde]);
                string ee(e.begin(), e.end());
                tokens.push_back(make_pair(ee,"Especial"));
                cout<<linha[onde]<<" - Especial"<<endl;
                onde++;
                continue;
            }

            if(ehLetra(linha[onde])){
                vector <char> p;

                p.push_back(linha[onde]);
                onde++;

                while(ehLetra(linha[onde]) || ehNumero(linha[onde]) || linha[onde]=='_'){
                    p.push_back(linha[onde]);
                    onde++;
                }

                string palavra(p.begin(), p.end());

                if(ehReservadas(palavra)){

                    tokens.push_back(make_pair(palavra,"Reservada"));
                    cout<<palavra<< " - Reservada"<<endl;
                    continue;
                }
                tokens.push_back(make_pair(palavra,"Identificador"));
                cout<<palavra<< " - Identificador"<<endl;
            
                continue;
            }
        
            if(ehOperadores1(linha[onde])){
                vector <char> op;

                op.push_back(linha[onde]);
                onde++;

                if(ehOperadores1(linha[onde])){
                    op.push_back(linha[onde]);
                    onde++;
                }

                string operador(op.begin(), op.end());

                if(ehOperadores2(operador)){

                    tokens.push_back(make_pair(operador,"Operador"));
                    cout<<operador<<" - Operador"<<endl;
                    continue;
                }

                cout<<"ERRO. Token invalido"<<endl;
                return 0;
            }

            if(ehNumero(linha[onde])){
                vector <char> n;
                n.push_back(linha[onde]);

                onde++;

                while(true){
                    if(ehLetra(linha[onde])){
                        cout<<"ERRO. Token invalido"<<endl;
                        return 0;
                    }

                    if(ehNumero(linha[onde]) || linha[onde]=='.'){
                        n.push_back(linha[onde]);
                        onde++;
                        continue;
                    }

                    break;
                }

                if(n.back()=='.'){
                    cout<<"ERRO. Token invalido"<<endl;
                    return 0;
                }
                string num(n.begin(), n.end());
                transformarNum(num);
                continue;
            }

            cout<<"ERRO. Token invalido"<<endl;
            return 0;
        }
        
        cout<<endl<<"Lista de tokens ate agora: "<<endl;
        for(int i=0;i<tokens.size();i++){
            cout<<tokens[i].first<<" -> "<<tokens[i].second<<endl;
        }
        cout<<endl;

    }

    //cout<<"Lista de tokens final: "<<endl;
    //for(int i=0;i<tokens.size();i++){
    //    cout<<tokens[i].first<<" -> "<<tokens[i].second<<endl;
    //}

    return 0;
}