AbstractFunction::AbstractFunction(string our_function){

}

AbstractFunction::AbstractFunction(AbstractFunction left, AbstractFunction right, Operator operation){
    this-> left = left;
    this-> right = right;
    this-> operation = operation;
}

AbstractFunction::AbstractFunction(){
    this->left = NULL;
    this->right = NULL;
    this->operation = none;
}

AbstractFunction AbstractFunction:: get_left(){
    return left;
}

void AbstractFunction::set_left(AbstractFunction left){
    this->left = left
}

AbstractFunction AbstractFunction:: get_right(){
    return right;
}

void AbstractFunction::set_right(AbstractFunction right){
    this->right = right;
}

Operation AbstractFunction::get_operation(){
    return operation;
}

void AbstractFunction::set_operation(Operation operation){
    this->operation = operation;

}



AbstractFunction AbstractFunction::solve(){
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

AbstractFunction AbstractFunction::multiply(AbstractFunction function1, AbstractFunction function2){
    return AbstractFunction(AbstractFunction(function1.solve(), function2, multiplication), AbstractFunction(function2.solve(), function1, multiplication), addition);
}
AbstractFunction AbstractFunction::divide(AbstractFunction function1, AbstractFunction function2){
    return AbstractFunction(AbstractFunction(AbstractFunction(function1.solve(), function2, multiplication), AbstractFunction(function1, function2.solve(),multiplication),subtraction), AbstractFunction(PolynomialFunction(2), function2, composition),division);

}
AbstractFunction AbstractFunction::add(AbstractFunction function1, AbstractFunction function2){
    return AbstractFunction(function1.solve(), function2.solve(), addition);
}
AbstractFunction AbstractFunction::subtract(AbstractFunction function1, AbstractFunction function2){
    return AbstractFunction(function1.solve(), function2.solve(), subtraction);
}
AbstractFunction AbstractFunction::chain_rule(AbstractFunction function1, AbstractFunction function2){
    return AbstractFunction(AbstractFunction(function1.solve(), function2,composition), function2.solve(), multiplication);
}




SinFunction::SinFunction(){
    left = NULL;
    right = NULL;
    operation = none;
}
AbstractFunction SinFunction::solve(){

    return CosFunction();

}




CosFunction::CosFunction(){
    left = NULL;
    right = NULL;
    operation = none;
}
AbstractFunction CosFunction::solve(){
    return AbstractFunction(ConstantFunction(-1), SinFunction(), multiplication);
}





ExponentialFunction::ExponentialFunction(int base){
    this->base = base;
    left = NULL;
    right = NULL;
    operation = none;
}
int ExponentialFunction::get_base(){
    return base;
}
AbstractFunction ExponentialFunction::solve(){
    return AbstractFunction(this, LogarithmicFunction('e'), multiplication);
}




ConstantFunction::ConstantFunction(int c){
    this->c = c;
    left = NULL;
    right = NULL;
    operation = none;
}
int ConstantFunction::get_c(){
    return c;
}
AbstractFunction ConstantFunction::solve(){
    return AbstractFunction(0);

}





LogarithmicFunction::LogarithmicFunction(int base){
    this->base = base;
    left = NULL;
    right = NULL;
    operation = none;
}
int LogarithmicFunction::get_base(){
    return base;
}
AbstractFunction LogarithmicFunction::solve(){
    int base = this->get_base();
    return AbstractFunction(ConstantFunction(1), AbstractFunction(ConstantFunction('ln(base)'), PolynomialFunction(1), multiplication), division)
}







PolynomialFunction::PolynomialFunction(int exponent){
    this->exponent = exponent;
    left = NULL;
    right = NULL;
    operation = none;
}
AbstractFunction PolynomialFunction::solve(){
    int c = this->get_exponent();
    return AbstractFunction(ConstantFunction(c), PolynomialFunction(c-1), multiplication);
}
