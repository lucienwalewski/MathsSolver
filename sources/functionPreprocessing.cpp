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
}

bool check_equation(string f){
    /*checking if equation solving should be performed*/
    bool find=false;

    for(int i=0; i<(int)f.size(); i++){
        if(!find && f[i]=='=')
            find = true;
        else if(find && f[i]=='='){
            cout<<"Error\n";
            find=false;
            break;
        }
    }

    return find;
}

bool check_integral(string f){
    /*checking if integral solving should be performed*/
    if(f.size()<5)
        return false;
    if(f.substr(0,4)=="/int")
        return true;
    else
        return false;
}

void start_process(){
    string f= upload_function();
    vector<bool (*)()> v;
    int cnt=0;

    if(check_derivative(f))
        cnt++;
    if(check_equation(f))
        cnt++;
    if(check_integral(f))
        cnt++;

    if(cnt>1){
        cout<<"Invalid input";
        return;
    }


}


