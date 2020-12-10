#include "functionPreprocessing.hpp"

string upload_function(){
    /*uploading of the given function*/
    string f, s="";
    getline(cin, f);

    for(int i=0; i<(int)f.size(); i++){
        if(f[i]==' ' || f[i]=='\t' || f[i]=='\n')
            continue;
        s+=f[i];
    }

    return s;
}

bool check_derivative(string f){
    /*check if program should perform derivation: potential idea - checking multiple derivation*/
    return ((int)f.size()>=3 && f[0]=='(' && f[(int)f.size()-1]=='\'' && f[(int)f.size()-2]==')');

    /*vector<Token> v;
    v= simplify(f, 'x');

    for(int i=0; i<(int)v.size(); i++)
        cout<<v[i].get_value()<<" "<<"\n";*/
}

bool check_equation(string &f){
    /*checking if equation solving should be performed*/
    bool find=false;
    string s;

    for(int i=0; i<(int)f.size(); i++){
        if(!find && f[i]=='=')
            find = true;
        else if(find && f[i]=='='){
            cout<<"Error\n";
            find=false;
            s="";
            break;
        }
        else if(find){
            if(f[i]=='+')
                s+='-';
            else if(f[i]=='-')
                s+='+';
            else
                s+=f[i];

        }
        else
            s+=f[i];
    }

    f=s;

    return find;
}

bool check_integral(string f){
    if(f.size()<5)
        return false;
    if(f.substr(0,4)=="/int")
        return true;
}
