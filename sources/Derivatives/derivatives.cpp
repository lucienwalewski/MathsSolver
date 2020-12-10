#include "derivatives.hpp"
#include "Tokenizer.hpp"

AbstractFunction::AbstractFunction(vector<Token> fun){
    str_label = vect_to_str(fun);
    // parentheses(&fun);
    operation =  Operator();
    int counter = 0;
    vector<Token>::iterator j = fun.begin();
    for (vector<Token>::iterator i = fun.begin();i<fun.end();i++){
        if (i->get_type() > 0){
            if (i -> get_type() == 7){
                if (i -> get_value() == "("){
                    counter += 1;}
                else {counter -= 1;}}

            else if (i -> get_type() > operation.get_type() and counter == 0){
                operation = Operator(i->get_value());

                j = i;
            }

        }


    }
    if (operation.get_type() > 0){
        vector<Token> l; vector<Token> r;
        for (vector<Token>::iterator i = fun.begin();i<fun.end();i++){
            if (i<j){
                l.push_back(*i);
            }
            if (i>j){
                r.push_back(*j);
            }
        *left = AbstractFunction(l);*right = AbstractFunction(r);
    }
    left = nullptr;right = nullptr;

    }
}





AbstractFunction::AbstractFunction(){
    this->left = nullptr;
    this->right = nullptr;

    this->operation = Operator();
    this->str_label = "";

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
    for (int i = 0; int(fun.size());i++){
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
    return AbstractFunction(AbstractFunction(function1.solve(), function2, Operator(mul)), AbstractFunction(function2.solve(), function1, Operator(mul)), Operator(addition));
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::divide(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(AbstractFunction(function1.solve(), function2, mul), AbstractFunction(function1, function2.solve(), mul), sub), AbstractFunction(PolynomialFunction(Token(get_str_label()), Token("2")), function2, comp), divi);
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::add(Function1 function1, Function2 function2){
    return AbstractFunction(function1.solve(), function2.solve(), addition);
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::subtract(Function1 function1, Function2 function2){
    return AbstractFunction(function1.solve(), function2.solve(), sub);
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::chain_rule(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(function1.solve(), function2, comp), function2.solve(), mul);

};


SinFunction::SinFunction(Token val){
    left = nullptr;
    right = nullptr;
    operation = Operator(none);

    str_label= "sin";
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
    operation = Operator(none);

    str_label= "cos";
    value = val;
}
Token CosFunction::get_value(){
    return value;
}

template <typename Function1> Function1 CosFunction::solve(){
    return AbstractFunction(ConstantFunction(Token("-1")), SinFunction(value), Operator(mul));

}




ExponentialFunction::ExponentialFunction(Token base){

    this->base = base;
    left = nullptr;
    right = nullptr;
    operation = Operator(none);

    str_label="log(";
}
Token ExponentialFunction::get_base(){
    return base;
}

template <typename Function1> Function1 ExponentialFunction::solve(){
    return AbstractFunction(this, LogarithmicFunction(Token(base), Token("e")), Operator(mul));

}




ConstantFunction::ConstantFunction(Token c){
    this->c = c;
    left = nullptr;
    right = nullptr;
    operation = Operator(none);

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
    operation = Operator(none);

    str_label = "log";
}
Token LogarithmicFunction::get_base(){
    return base;
}
Token LogarithmicFunction::get_value(){
    return value;
}
template <typename Function1> Function1 LogarithmicFunction::solve(){
    Token base = this->get_base();
    return AbstractFunction(ConstantFunction(Token("1")), AbstractFunction(LogarithmicFunction(base, Token("e")), PolynomialFunction(value, Token("1")), Operator(mul)), Operator(divi));

}







PolynomialFunction::PolynomialFunction(Token base, Token exponent){

    this->exponent = exponent;
    this->base = base;
    left = nullptr;
    right = nullptr;
    operation = Operator(none);

    str_label = "";
}
Token PolynomialFunction::get_exponent(){
    return exponent;
}
Token PolynomialFunction::get_base(){
    return base;
}
template <typename Function1> Function1 PolynomialFunction::solve(){
    Token c = this->get_exponent();
    string new_exponent = c.get_value() + "-1";
    return AbstractFunction(ConstantFunction(c), PolynomialFunction(base, Token(new_exponent)), Operator(mul));

}



