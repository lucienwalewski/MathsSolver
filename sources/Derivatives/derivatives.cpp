#include "derivatives.hpp"

AbstractFunction::AbstractFunction(string fun){
    operation = none;
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
            Operation new_o = none;
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
    this->operation = none;
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

}


template <typename Function1, typename Function2> AbstractFunction AbstractFunction::add(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(function1.solve(), function2, multiplication), AbstractFunction(function2.solve(), function1, multiplication), addition);
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::subtract(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(AbstractFunction(function1.solve(), function2, multiplication), AbstractFunction(function1, function2.solve(),multiplication),subtraction), AbstractFunction(PolynomialFunction(2), function2, composition),division);
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::multiply(Function1 function1, Function2 function2){
    return AbstractFunction(function1.solve(), function2.solve(), addition);
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::divide(Function1 function1, Function2 function2){
    return AbstractFunction(function1.solve(), function2.solve(), subtraction);
};
template <typename Function1, typename Function2> AbstractFunction AbstractFunction::chain_rule(Function1 function1, Function2 function2){
    return AbstractFunction(AbstractFunction(function1.solve(), function2,composition), function2.solve(), multiplication);
};


SinFunction::SinFunction(){
    left = nullptr;
    right = nullptr;
    operation = none;
    str_label= "sin";
}
template <typename Function1> Function1 SinFunction::solve(){

    return CosFunction();

}




CosFunction::CosFunction(){
    left = nullptr;
    right = nullptr;
    operation = none;
    str_label= "cos";
}

template <typename Function1> Function1 CosFunction::solve(){
    return AbstractFunction(ConstantFunction(-1), SinFunction(), multiplication);
}






ExponentialFunction::ExponentialFunction(int base){
    this->base = base;
    left = nullptr;
    right = nullptr;
    operation = none;
    str_label="log(";
}
int ExponentialFunction::get_base(){
    return base;
}
template <typename Function1> Function1 ExponentialFunction::solve(){
    return AbstractFunction(this, LogarithmicFunction('e'), multiplication);
}




ConstantFunction::ConstantFunction(int c){
    this->c = c;
    left = nullptr;
    right = nullptr;
    operation = none;
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
    operation = none;
    str_label = "log";
}
int LogarithmicFunction::get_base(){
    return base;
}
template <typename Function1> Function1 LogarithmicFunction::solve(){
    int base = this->get_base();
    return AbstractFunction(ConstantFunction(1), AbstractFunction(ConstantFunction('ln(base)'), PolynomialFunction(1), multiplication), division);
}







PolynomialFunction::PolynomialFunction(int exponent){
    this->exponent = exponent;
    left = nullptr;
    right = nullptr;
    operation = none;
    str_label = "";
}
template <typename Function1> Function1 PolynomialFunction::solve(){
    int c = this->get_exponent();
    return AbstractFunction(ConstantFunction(c), PolynomialFunction(c-1), multiplication);
}















\







