#include "derivatives.hpp"
#include "Tokenizer.hpp"

//bring back AbstractFunction as a name

map<string, int> type_m = {{"~",1},{"^",2},{"/",3},{"*",4},{"-",5},{"+",6},{"(",7},{")",8},{"_",9}};

AF::AF(vector<Token> fun){
    end = false;
    type = 1;
    vect_label = fun;
    in_str_label = vect_to_str(fun);
    // parentheses(&fun);
    if((int)fun.size() == 1 && !fun[0].is_super_token()){
        this->left = nullptr;
        this->right = nullptr;
        this->operation = Operator();
        end = true;
        this->str_label = fun[0].get_value();
        this->type = fun[0].get_type();
        this->in_str_label = fun[0].get_value();
        // setting leaf_mark
    }
    else{

        if ((int)fun.size() == 1 && fun[0].is_super_token()){
            fun = simplify(fun[0].get_value(),'x');
            type = fun[0].get_type();
        }

         operation =  Operator();
         int counter = 0;
         int j = 0;
         for (int i = 0; i < (int)fun.size(); i++){
             if (fun[i].get_type() > 0){
                 if (fun[i].get_type() == 7)
                     counter++;
                 else if (fun[i].get_type() == 8)
                     counter++;
                 else if (fun[i].get_type() > operation.get_type() && counter == 0){
                     operation = Operator(fun[i].get_value());
                     j = i;
                 }
             }
         }

         if (operation.get_type() > 0){
             vector<Token> l, r;

             for (int i = 0; i < (int)fun.size(); i++){
                 if(i < j)
                     l.push_back(fun[i]);
                 else if (i > j)
                     r.push_back(fun[i]);
             }

             //explanation needed??? insert??? no need for this line?
           /*  if (fun[0].is_super_token()){
                 l = simplify(fun[0].get_value(),'x');
             }
             if (fun[2].is_super_token()){
                 r = simplify(fun[2].get_value(),'x');
             }*/

             if ((int)l.size() == 1 && !l[0].is_super_token())
                 left = assign(l[0]);
             else
                 left =  new AF(l);

             if ((int)r.size() == 1 && !r[0].is_super_token())
                 right = assign(r[0]);
             else
                 right = new AF(r);

             str_label = left->get_str_label() + this->get_operation().get_value()+ right->get_str_label();
             //cout<< "Const: "<< str_label<< "\n";
         }
    }
}

AF* assign(Token fun){
    switch (fun.get_type()) {
        case -1: return new NumAF(fun); break;
        case -2:
            if (fun.get_value() == "exp")
                return new ExpAF();
            else if (fun.get_value() == "ln")
                return new LnAF();
            else if (fun.get_value() == "log")
                return new LogAF(10);
            else if (fun.get_value() == "cos")
                return new CosAF();
            else if (fun.get_value() == "sin")
                return new SinAF();
            else if (fun.get_value() == "tan")
                return new TanAF();
            else if (fun.get_value() == "sqrt")
                return new SqrtAF();
            break;
        case -3: return new VarAF(fun); break;
    }
}


AF::AF(AF left, AF right, Operator operation){
    this->left = &left;
    this->right = &right;
    end = false;
    this->operation = operation;
    this->str_label = "";
    this->in_str_label = "";

}

AF::AF(int type, Token end_token){
    this->left = nullptr;
    this->right = nullptr;
    this->operation = Operator();
    end = true;
    this->type = type;
    this->end_token = end_token;
}



AF AF:: get_left(){
    return *left;
}

void AF::set_left(AF *left){
    this->left = left;
}

AF AF:: get_right(){
    return *right;
}

void AF::set_right(AF *right){
    this->right = right;
}

string AF::get_string_operation(){
    return operation.get_value();
}


Operator AF::get_operation(){
    return operation;
}

void AF::set_operation(Operator operation){
    this->operation = operation;

}

string AF::get_str_label(){
    return str_label;
}

string AF::get_in_str_label(){
    return in_str_label;
}

string AF::display(int i){

    if (this->left == nullptr && this->right == nullptr){
        return get_str_label();
    }
    else{
        //cout<< i << " " << operation.get_value() << "\n";
        //string s = "(" +get_left().display(i+1) + " " + operation.get_value() + " " + get_right().display(i+1) + ")";
        string s1 = get_left().display(i+1);
        if (i == 0){
            cout <<"OK\n";
        }
        string s2 = get_right().display(i+1);
        if (i == 0){
            cout <<"OKK\n";
        }
        string s = "("+s1+operation.get_value()+s2+")";
        cout<<i<<" "<< s << "\n";
        if (i == 1){
            cout<<"k\n";
        }
        return s;
    }
}

double AF::get_value(double x, bool neg, bool div){
    switch (operation.get_type()) {
        case -1: return get_leaf_value(x, leaf_mark, get_str_label()); break;
        case 1: return get_left().get_value(get_right().get_value(x, false, false), false, false); break;
        case 2: return pow(get_left().get_value(x, false, false), get_right().get_value(x, false, true)); break;
        case 3:
            return get_left().get_value(x, false, false)/get_right().get_value(x, false, true);
            break;
        case 4: return get_left().get_value(x, false, false)*get_right().get_value(x, false, false); break;
        case 5:
            if (neg)
                return get_left().get_value(x, false, false)+get_right().get_value(x, true, false);
            else
                return get_left().get_value(x, false, false)-get_right().get_value(x, true, false);

            break;
        case 6:
            return get_left().get_value(x, false, false)+get_right().get_value(x, false, false); break;
        default: return 0;
    }
}


double AF::get_leaf_value(double x, int n, string val){
    switch (n) {
        case 0: return NumAF(Num(val)).get_value(x); break;
        case 1: return ExpAF().get_value(x); break;
        case 2: return LnAF().get_value(x); break;
        case 3: return LogAF(10).get_value(x); break;
        case 4: return CosAF().get_value(x); break;
        case 5: return SinAF().get_value(x); break;
        case 6: return TanAF().get_value(x); break;
        case 7: return SqrtAF().get_value(x); break;
        case 8: return VarAF(Variable(val)).get_value(x); break;
        default: return 0;
    }
}


ExpAF::ExpAF():AF(){
  value = Function("exp");
  str_label = value.get_value();
  in_str_label = value.get_value();
  type = value.get_type();
  leaf_mark = 1;
}

string ExpAF::get_derivative(){
    return str_label;
}

double ExpAF::get_value(double x, bool neg, bool div){
    return exp(x);
}

LnAF::LnAF():AF(){
    value = Function("ln");
    str_label = value.get_value();
    in_str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 2;
}

string LnAF::get_derivative(){
    return "1/";
}

double LnAF::get_value(double x, bool neg, bool div){
    return log(x);
}

LogAF::LogAF(double a):AF(){
    value = Function("log");
    str_label = value.get_value();
    in_str_label = value.get_value();
    type = value.get_type();
    base = a;
    leaf_mark = 3;
}

double LogAF::get_base(){
    return base;
}

string LogAF::get_derivative(){
    return "(1/ln("+to_string(base)+")*1/";
}

double LogAF::get_value(double x, bool neg, bool div){
    return log(x)/log(base);
}

CosAF::CosAF():AF(){
    value = Function("cos");
    str_label = value.get_value();
    in_str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 4;
}

string CosAF::get_derivative(){
    return "-sin";
}

double CosAF::get_value(double x, bool neg, bool div){
    return cos(x);
}

SinAF::SinAF():AF(){
    value = Function("sin");
    str_label = value.get_value();
    in_str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 5;
}

string SinAF::get_derivative(){
    return "cos";
}

double SinAF::get_value(double x, bool neg, bool div){
    return sin(x);
}

TanAF::TanAF():AF(){
    value = Function("tan");
    str_label = value.get_value();
    in_str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 6;
}

string TanAF::get_derivative(){
    return "1/cos^2";
}

double TanAF::get_value(double x, bool neg, bool div){
    return tan(x);
}

SqrtAF::SqrtAF():AF(){
    value = Function("sqrt");
    str_label = value.get_value();
    in_str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 7;
}

string SqrtAF::get_derivative(){
    return "-(1/2)*1/sqrt";
}

double SqrtAF::get_value(double x, bool neg, bool div){
    return sqrt(x);
}

NumAF::NumAF(Token T):AF() {
    value = T;
    str_label = value.get_value();
    in_str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 0;
}

string NumAF::get_derivative(){
    return "0";
}

double NumAF::get_value(double x, bool neg, bool div){
    return stod(value.get_value());
}

VarAF::VarAF(Token T):AF() {
    value = T;
    str_label = value.get_value();
    in_str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 8;
}

string VarAF::get_derivative(){
    return "1";
}

double VarAF::get_value(double x, bool neg, bool div){
    return x;
}

string vect_to_str(vector<Token> fun){
    string sfun = "";
    for (int i = 0; i< (int)fun.size(); i++){
        sfun += fun[i].get_value();
        if (i != int(fun.size())-1){
            sfun += " ";
        }
    }
    return sfun;
}
