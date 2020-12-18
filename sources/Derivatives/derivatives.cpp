#include "derivatives.hpp"
#include "Tokenizer.hpp"
map<string, int> type_m = {{"~",1},{"^",2},{"/",3},{"*",4},{"-",5},{"+",6},{"(",7},{")",8},{"_",9}};

AbstractFunction::AbstractFunction(vector<Token> fun){
    vect_label = fun;
    in_str_label = vect_to_str(fun);
    cout << in_str_label << '\n';
    // parentheses(&fun);
    operation =  Operator();
    int counter = 0;
    vector<Token>::iterator j = fun.begin();
    for (vector<Token>::iterator i = fun.begin();i<fun.end();i++){
        if (i->get_type() > 0){
            int val = type_m[i->get_value()];
            cout << val<< "  " << i-> get_value()<<'\n';
            if ( val == 7){counter += 1;}
            else if (val == 8){counter -= 1;}
            else if (val > type_m[operation.get_value()] and counter == 0){
                operation = Operator(i->get_value());
                j = i;
            }

        }


    }
    cout << "string is " << in_str_label<<'\n';
    cout << "Operation: " << operation.get_value()<< " and val "<<operation.get_type() << '\n';
    if (type_m[operation.get_value()] > 0){
        cout << "Im here" << in_str_label<<'\n';
        vector<Token> l, r;
        for (vector<Token>::iterator i = fun.begin();i<fun.end();i++){
            if (i<j){
                l.push_back(*i);
            }
            else if (i>j){
                r.push_back(*i);

            }
        }
        cout << "left: "<< vect_to_str(l)<<" O: "<<j->get_value() << ". right: " << vect_to_str(r)<<'\n';

        if (int(l.size())>0){

            *left = AbstractFunction(l);
            cout << "whyyyyy";
        }
        if (int(r.size())>0){

            *right = AbstractFunction(r);
        }

        str_label = left->get_str_label() + this->get_operation().get_value()+ right->get_str_label();


    } else {
        cout << "still here"<<'\n';
        *this-> left = AbstractFunction();
        cout << "am I?";
        *this-> right = AbstractFunction();
    }
    cout << "success!" << in_str_label <<'\n';
}





AbstractFunction::AbstractFunction(){
    this->left = nullptr;
    this->right = nullptr;

    this->operation = Operator();
    this->str_label = "";
    this->in_str_label = "";

}


AbstractFunction AbstractFunction:: get_left(){
    return *left;
}

void AbstractFunction::set_left(AbstractFunction *left){
    this->left = left;
}

AbstractFunction AbstractFunction:: get_right(){
    return *right;
}

void AbstractFunction::set_right(AbstractFunction *right){
    this->right = right;
}
string AbstractFunction::get_string_operation(){
    return operation.get_value();
}
string vect_to_str(vector<Token> fun){
    string sfun = "";
    for (int i = 0; i< int(fun.size());i++){
        sfun += fun[i].get_value();
    }
    return sfun;
}
Operator AbstractFunction::get_operation(){
    return operation;
}

void AbstractFunction::set_operation(Operator operation){
    this->operation = operation;

}

string AbstractFunction::get_str_label(){
    return str_label;
}
string AbstractFunction::get_in_str_label(){
    return in_str_label;
}
string AbstractFunction::display(){
    if (this->left == nullptr and this->right == nullptr){
        cout << get_in_str_label() << '\n';
        return get_in_str_label();
    }else{
        return get_left().display() + operation.get_value() + get_right().display();
    }
}



template <typename Function1> Function1 AbstractFunction::solve(){

    if(this->get_operation().get_type() == 5){
        return add(this->get_left(), this->get_right());
    }
    if(this->get_operation().get_type() == 4){
        return subtract(this->get_left(), this->get_right());
    }
    if(this->get_operation().get_type() == 3){
        return multiply(this->get_left(), this->get_right());
    }
    if(this->get_operation().get_type() == 2){
        return divide(this->get_left(), this->get_right());
    }
    if(this->get_operation().get_type() == 1){

        return chain_rule(this->get_left(), this->get_right());
    }


    return nullptr;

}


template <typename Function1, typename Function2> AbstractFunction AbstractFunction::multiply(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(function1.solve(), function2, Operator("*")), AbstractFunction(function2.solve(), function1, Operator("*")), Operator("+"));
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::divide(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(AbstractFunction(function1.solve(), function2, Operator("*")), AbstractFunction(function1, function2.solve(), Operator("*")), Operator("-")), AbstractFunction(PolynomialFunction(Token(get_str_label()), Token("2")), function2, Operator("~")), Operator("/"));
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::add(Function1 function1, Function2 function2){
    return AbstractFunction(function1.solve(), function2.solve(), "+");
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::subtract(Function1 function1, Function2 function2){
    return AbstractFunction(function1.solve(), function2.solve(), "-");
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::chain_rule(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(function1.solve(), function2, "~"), function2.solve(), "*");

};


SinFunction::SinFunction(Token val){
    left = nullptr;
    right = nullptr;
    operation = Operator();

    str_label= "sin(" + value.get_value() +")";
    value = val;
}

Token SinFunction::get_value(){
    return value;
}
template <typename Function1> Function1 SinFunction::solve(){

    return CosFunction(value);

}

CosFunction::CosFunction(Token val){

    left = nullptr;
    right = nullptr;
    operation = Operator();

    str_label= "cos(" + value.get_value() +")";
    value = val;
}
Token CosFunction::get_value(){
    return value;
}

template <typename Function1> Function1 CosFunction::solve(){
    return AbstractFunction(ConstantFunction(Token("-1")), SinFunction(value), Operator("*"));

}






ExponentialFunction::ExponentialFunction(Token base, Token val){

    this->base = base;
    left = nullptr;
    right = nullptr;
    operation = Operator();
    this->value = val;

    str_label = base.get_value() + "^" + value.get_value();
}
Token ExponentialFunction::get_base(){
    return base;
}

Token ExponentialFunction::get_value(){
    return value;
}
template <typename Function1> Function1 ExponentialFunction::solve(){
    if(base.get_value() == "e"){
        return ExponentialFunction(base, value);
    }
    return AbstractFunction(this, LogarithmicFunction(Token(base), Token("e")), Operator("*"));

}




ConstantFunction::ConstantFunction(Token c){
    this->c = c;
    left = nullptr;
    right = nullptr;
    operation = Operator();

    str_label = "";
}
Token ConstantFunction::get_c(){
    return c;
}
template <typename Function1> Function1 ConstantFunction::solve(){
    return ConstantFunction(Token("0"));
}




LogarithmicFunction::LogarithmicFunction(Token val, Token base){

    this->base = base;
    value = val;
    left = nullptr;
    right = nullptr;
    operation = Operator();

    str_label= "log_" + base.get_value() + "(" +value.get_value() + ")";
    if(base.get_value() == "e"){
        str_label = "ln(" + value.get_value() + ")";
    }

}
Token LogarithmicFunction::get_base(){
    return base;
}
Token LogarithmicFunction::get_value(){
    return value;
}
template <typename Function1> Function1 LogarithmicFunction::solve(){
    Token base = this->get_base();
    if(base.get_value() == "e"){
        return AbstractFunction(ConstantFunction(Token("1")), PolynomialFunction(value, Token("1")), Operator("/"));
    }
    return AbstractFunction(ConstantFunction(Token("1")), AbstractFunction(LogarithmicFunction(base, Token("e")), PolynomialFunction(value, Token("1")), Operator("*")), Operator("/"));

}







PolynomialFunction::PolynomialFunction(Token val, Token exponent){

    this->exponent = exponent;
    this->value = val;
    left = nullptr;
    right = nullptr;
    operation = Operator();

    str_label = "";
}
Token PolynomialFunction::get_exponent(){
    return exponent;
}
Token PolynomialFunction::get_value(){
    return value;
}
template <typename Function1> Function1 PolynomialFunction::solve(){
    string new_exponent = exponent.get_value() + "-1";
    return AbstractFunction(ConstantFunction(exponent), PolynomialFunction(value, Token(new_exponent)), Operator("*"));

}



