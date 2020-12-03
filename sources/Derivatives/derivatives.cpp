#include "derivatives.hpp"

AbstractFunction::AbstractFunction(string fun){
    operation = no_op;
    str_label= fun;
    while (fun[0] == "("[0] and fun[-1] == ")"[0]){
        string new_f = "";
        for (string::iterator i = fun.begin() + 1;i<fun.end();i++){
            new_f += *i;
        }
        fun = new_f;
    }
    int counter = 0;
    string::iterator j = fun.begin();
    for (string::iterator i = fun.begin();i<fun.end();i++){
        if (*i == "("[0]){
            counter += 1;
        }
        if (*i == ")"[0]){
            counter += 1;
        }
        if (operators.find_first_of(*i,0) != string::npos and counter == 0){
            char op = *i;
            Operation new_o = no_op;
            op_to_enum(op, new_o);
            if (new_o > operation){
                operation = new_o;
                j = i;
            };
        }
    }
    string l = ""; string r = "";
    for (string::iterator i = fun.begin();i<fun.end();i++){
        if (i<j){
            l += *i;
        }
        if (i>j){
            r += *i;
        }
    *left = AbstractFunction(l);*right = AbstractFunction(r);
    }
}

void AbstractFunction::op_to_enum(char op,Operation &o){
    if (op == "+"[0]){
        o = addition;
    }
    if (op == "-"[0]){
        o = subtraction;
    }
    if (op == "*"[0]){
        o = multiplication;
    }
    if (op == "/"[0]){
        o = division;
    }
    if (op == "~"[0]){
        o = composition;
    }
}

string AbstractFunction::get_string_operation(){
    if (operation == 5){
        return "+";
    }
    else if (operation == 4){
        return "-";
    }
    else if(operation == 3){
        return "*";
    }
    else if (operation == 2){
        return "/";
    }
    else if (operation == 1){
        return "~";
    }
    return "";

}

AbstractFunction::AbstractFunction(){
    this->left = nullptr;
    this->right = nullptr;
    this->operation = no_op;
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

Operation AbstractFunction::get_operation(){
    return operation;
}

void AbstractFunction::set_operation(Operation operation){
    this->operation = operation;

}

string AbstractFunction::get_str_label(){
    return str_label;
}




template <typename Function1> Function1 AbstractFunction::solve(){

    if(this->get_operation() == 5){
        return add(this->get_left(), this->get_right());
    }
    if(this->get_operation() == 4){
        return subtract(this->get_left(), this->get_right());
    }
    if(this->get_operation() == 3){
        return multiply(this->get_left(), this->get_right());
    }
    if(this->get_operation() == 2){
        return divide(this->get_left(), this->get_right());
    }
    if(this->get_operation() == 1){
        return chain_rule(this->get_left(), this->get_right());
    }


    return nullptr;

}


template <typename Function1, typename Function2> AbstractFunction AbstractFunction::multiply(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(function1.solve(), function2, multiplication), AbstractFunction(function2.solve(), function1, multiplication), addition);
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::divide(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(AbstractFunction(function1.solve(), function2, multiplication), AbstractFunction(function1, function2.solve(),multiplication),subtraction), AbstractFunction(PolynomialFunction(Token(get_str_label()), Token("2")), function2, composition),division);
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::add(Function1 function1, Function2 function2){
    return AbstractFunction(function1.solve(), function2.solve(), addition);
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::subtract(Function1 function1, Function2 function2){
    return AbstractFunction(function1.solve(), function2.solve(), subtraction);
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::chain_rule(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(function1.solve(), function2,composition), function2.solve(), multiplication);
};


SinFunction::SinFunction(Token val){
    left = nullptr;
    right = nullptr;
    operation = no_op;
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
    operation = no_op;
    str_label= "cos";
    value = val;
}
Token CosFunction::get_value(){
    return value;
}

template <typename Function1> Function1 CosFunction::solve(){
    return AbstractFunction(ConstantFunction(Token("-1")), SinFunction(value), multiplication);
}






ExponentialFunction::ExponentialFunction(Token base){
    this->base = base;
    left = nullptr;
    right = nullptr;
    operation = no_op;
    str_label="log(";
}
Token ExponentialFunction::get_base(){
    return base;
}

template <typename Function1> Function1 ExponentialFunction::solve(){
    return AbstractFunction(this, LogarithmicFunction(Token(base), Token("e")), multiplication);
}




ConstantFunction::ConstantFunction(Token c){
    this->c = c;
    left = nullptr;
    right = nullptr;
    operation = no_op;
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
    operation = no_op;
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
    return AbstractFunction(ConstantFunction(Token("1")), AbstractFunction(LogarithmicFunction(base, Token("e")), PolynomialFunction(value, Token("1")), multiplication), division);
}







PolynomialFunction::PolynomialFunction(Token base, Token exponent){
    this->exponent = exponent;
    this->base = base;
    left = nullptr;
    right = nullptr;
    operation = no_op;
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
    return AbstractFunction(ConstantFunction(c), PolynomialFunction(base, Token(new_exponent)), multiplication);
}















\







