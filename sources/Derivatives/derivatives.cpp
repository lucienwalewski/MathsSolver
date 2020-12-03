#include "derivatives.hpp"
#include "Tokenizer.hpp"
AbstractFunction::AbstractFunction(vector<Token> fun){


    operation =  Operator();

    vector<Token>::iterator j = fun.begin();
    for (vector<Token>::iterator i = fun.begin();i<fun.end();i++){
        if (i->get_type() > 0){
            if (i -> get_type() > operation.get_type()){
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

AbstractFunction* AbstractFunction:: get_left(){
    return left;
}

void AbstractFunction::set_left(AbstractFunction *left){
    this->left = left;
}

AbstractFunction* AbstractFunction:: get_right(){
    return right;
}

void AbstractFunction::set_right(AbstractFunction *right){
    this->right = right;
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

    if(this->operation.get_type() == 5){
        return add(this->get_left(), this->get_right());
    }
    if(this->operation.get_type() == 4){
        return subtract(this->get_left(), this->get_right());
    }
    if(this->operation.get_type() == 3){
        return multiply(this->get_left(), this->get_right());
    }
    if(this->operation.get_type() == 2){
        return divide(this->get_left(), this->get_right());
    }
    if(this->operation.get_type() == 1){
        return chain_rule(this->get_left(), this->get_right());
    }

}


template <typename Function1, typename Function2> AbstractFunction AbstractFunction::add(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(function1.solve(), function2, Operator("*")), AbstractFunction(function2.solve(), function1, Operator("*")), Operator("+"));
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::subtract(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(AbstractFunction(function1.solve(), function2, Operator("*")), AbstractFunction(function1, function2.solve(),Operator("*")),Operator("-")), AbstractFunction(PolynomialFunction(2), function2, Operator("~")),Operator("/"));
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::multiply(Function1 function1, Function2 function2){
    return AbstractFunction(function1.solve(), function2.solve(), Operator("+"));
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::divide(Function1 function1, Function2 function2){
    return AbstractFunction(function1.solve(), function2.solve(), Operator("-"));
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::chain_rule(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(function1.solve(), function2,Operator("~")), function2.solve(), Operator("*"));
};


SinFunction::SinFunction(){
    left = nullptr;
    right = nullptr;
    operation = Operator();
    str_label= "sin";
}
template <typename Function1> Function1 SinFunction::solve(){

    return CosFunction();

}




CosFunction::CosFunction(){
    left = nullptr;
    right = nullptr;
    operation = Operator();
    str_label= "cos";
}

template <typename Function1> Function1 CosFunction::solve(){
    return AbstractFunction(ConstantFunction(-1), SinFunction(), Operator("*"));
}






ExponentialFunction::ExponentialFunction(int base){
    this->base = base;
    left = nullptr;
    right = nullptr;
    operation = Operator();
    str_label="log(";
}
int ExponentialFunction::get_base(){
    return base;
}
template <typename Function1> Function1 ExponentialFunction::solve(){
    return AbstractFunction(this, LogarithmicFunction('e'), Operator("*"));
}




ConstantFunction::ConstantFunction(int c){
    this->c = c;
    left = nullptr;
    right = nullptr;
    operation = Operator();
    str_label = "";
}
int ConstantFunction::get_c(){
    return c;
}
template <typename Function1> Function1 ConstantFunction::solve(){
    return ConstantFunction(0);
}





LogarithmicFunction::LogarithmicFunction(int base){
    this->base = base;
    left = nullptr;
    right = nullptr;
    operation = Operator();
    str_label = "log";
}
int LogarithmicFunction::get_base(){
    return base;
}
template <typename Function1> Function1 LogarithmicFunction::solve(){
    int base = this->get_base();
    int lnbase;
    return AbstractFunction(ConstantFunction(1), AbstractFunction(ConstantFunction(lnbase), PolynomialFunction(1), Operator("*")), Operator("/"));
}







PolynomialFunction::PolynomialFunction(int exponent){
    this->exponent = exponent;
    left = nullptr;
    right = nullptr;
    operation = Operator();
    str_label = "";
}
template <typename Function1> Function1 PolynomialFunction::solve(){
    int c = this->get_exponent();
    return AbstractFunction(ConstantFunction(c), PolynomialFunction(c-1), Operator("*"));
}



