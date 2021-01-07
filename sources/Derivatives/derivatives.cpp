#include "derivatives.hpp"
#include "Tokenizer.hpp"
#include "Operators.hpp"


map<string, int> type_m = {{"~",1},{"^",2},{"/",3},{"*",4},{"-",5},{"+",6},{"(",7},{")",8},{"_",9}};


AbstractFunction::AbstractFunction(vector<Token> fun){
    end = false;
    type = 1;
    vect_label = fun;
    str_label = vect_to_str(fun);
    // parentheses(&fun);
    if ((int)fun.size() == 1 && (fun[0].get_type() == -4)){
        fun = simplify(fun[0].get_value(),'x');
        type = -4;
    }

    if((int)fun.size() == 1 && (fun[0].get_type() != -4)){
        this->left = nullptr;
        this->right = nullptr;
        this->operation = Operator();
        end = true;
        this->str_label = fun[0].get_value();
        this->type = fun[0].get_type();
        switch (type){
            case -1: leaf_mark = 0;  break;
            case -2:
                if (str_label == "exp")
                    leaf_mark = 1;
                else if (str_label == "ln")
                    leaf_mark = 2;
                else if (str_label == "log")
                    leaf_mark = 3;
                else if (str_label == "cos")
                    leaf_mark = 4;
                else if (str_label == "sin")
                    leaf_mark = 5;
                else if (str_label == "tan")
                    leaf_mark = 6;
                else if (str_label == "sqrt")
                    leaf_mark = 7;
                break;
            case -3: leaf_mark = 8;
        }
    }
    else{
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

             if ((int)l.size() == 1 && (l[0].get_type() != -4))
                 left = assign(l[0]);
             else
                 left =  new AbstractFunction(l);


             if ((int)r.size() == 1 && (r[0].get_type() != -4))
                 right = assign(r[0]);
             else
                 right = new AbstractFunction(r);

             str_label = left->get_str_label() + this->get_operation().get_value()+ right->get_str_label();
             //cout<< "Const: "<< str_label<< "\n";
         }
    }
}

AbstractFunction* assign(Token fun){
    switch (fun.get_type()) {
        case -1: return new NumAbstractFunction(fun); break;
        case -2:
            if (fun.get_value() == "exp")
                return new ExpAbstractFunction();
            else if (fun.get_value() == "ln")
                return new LnAbstractFunction();
            else if (fun.get_value() == "log")
                return new LogAbstractFunction(10);
            else if (fun.get_value() == "cos")
                return new CosAbstractFunction();
            else if (fun.get_value() == "sin")
                return new SinAbstractFunction();
            else if (fun.get_value() == "tan")
                return new TanAbstractFunction();
            else if (fun.get_value() == "sqrt")
                return new SqrtAbstractFunction();
            break;
        case -3: return new VarAbstractFunction(fun); break;
    }
}



AbstractFunction::AbstractFunction(AbstractFunction left, AbstractFunction right, Operator operation){
    this->left = &left;
    this->right = &right;
    end = false;
    this->operation = operation;
    this->str_label = "";

}

AbstractFunction::AbstractFunction(int type, Token end_token){
    this->left = nullptr;
    this->right = nullptr;
    this->operation = Operator();
    end = true;
    this->type = type;
    this->end_token = end_token;
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


Operator AbstractFunction::get_operation(){
    return operation;
}

void AbstractFunction::set_operation(Operator operation){
    this->operation = operation;

}

string AbstractFunction::get_str_label(){
    return str_label;
}


string AbstractFunction::display(){

    if (this->left == nullptr && this->right == nullptr){
        return get_str_label();
    }
    else{
        string s1 = get_left().display();
        string s2 = get_right().display();
        if (operation.get_value() == "~"){
            return s1 + "(" + s2 + ")";
        }
        if (operation.get_value() == "+"){
            return add_strings(s1, s2);
        }
        if (operation.get_value() == "-"){
            return sub_strings(s1, s2);
        }
        if (operation.get_value() == "*"){
            return mult_strings(s1, s2);
        }
        if (operation.get_value() == "/"){
            return div_strings(s1, s2);
        }
        if (operation.get_value() == "^"){
            return pow_strings(s1, s2);
        }
        return "display() error!!";
    }
}

// be careful when divion with 0
double AbstractFunction::get_value(double x, bool neg, bool div){
    //cout << get_str_label() << " " << operation.get_type()<< "\n";
    switch (operation.get_type()) {
        case -1:  return get_leaf_value(x, leaf_mark, get_str_label()); break;
        case 1: return get_left().get_value(get_right().get_value(x, false, false), false, false); break;
        case 2: return pow(get_left().get_value(x, false, false), get_right().get_value(x, false, true)); break;
        case 3:{
            double a = get_right().get_value(x, false, true);
            if(a == 0){
                cout << "Division with zero!\n";
                return 1;
            }
            else
                return get_left().get_value(x, false, false)/a;
            break;
        }
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


double AbstractFunction::get_leaf_value(double x, int n, string val){
    switch (n) {
        case 0: return NumAbstractFunction(Num(val)).get_value(x); break;
        case 1: return ExpAbstractFunction().get_value(x); break;
        case 2: return LnAbstractFunction().get_value(x); break;
        case 3: return LogAbstractFunction(10).get_value(x); break;
        case 4: return CosAbstractFunction().get_value(x); break;
        case 5: return SinAbstractFunction().get_value(x); break;
        case 6: return TanAbstractFunction().get_value(x); break;
        case 7: return SqrtAbstractFunction().get_value(x); break;
        case 8: return VarAbstractFunction(Variable(val)).get_value(x); break;
        default: return 0;
    }
}


bool AbstractFunction::is_polynomial(){
    //cout << get_str_label() << " " << operation.get_type()<<" "<<get_left().leaf_mark<<" " <<get_right().leaf_mark<< "\n";
    switch (operation.get_type()) {
        case -1:
            if (leaf_mark == 0 || leaf_mark == 8)
                return true;
            else
                return false;
            break;
        case 1: return false; break;
        // later update needed for power, since power has to be int>=0
        case 2: return (get_left().leaf_mark == 8) && (get_right().leaf_mark == 0); break;
        case 3: return (get_left().leaf_mark == 0) && (get_right().leaf_mark == 0); break;
        case 4: return get_left().is_polynomial() && get_right().is_polynomial(); break;
        case 5: return get_left().is_polynomial() && get_right().is_polynomial(); break;
        case 6: return get_left().is_polynomial() && get_right().is_polynomial(); break;
        default: return false;
    }
}


PolynomialRational AbstractFunction::get_polynomial(bool neg){
    if (!is_polynomial())
        return PolynomialRational();

    switch (operation.get_type()) {
        case -1:{
            if (leaf_mark == 0){
                Rational c[1];
                c[0] = Rational((get_value(0)));
                return PolynomialRational(c, 0);
            }
            else{
                Rational c[2] = {};
                c[1] = Rational(1,1);
                return PolynomialRational(c, 1);
            }
            break;
        }
        case 2: {
            int n = (int)get_right().get_value(0);
            Rational c[n+1];
            for (int i = 0; i <= n; i++)
                c[i] = Rational(0, 1);
            c[n] = Rational(1,1);
            return PolynomialRational(c, n);
            break;
        }
        case 3: return get_left().get_polynomial()/get_right().get_polynomial(); break;
        case 4: return get_left().get_polynomial()*get_right().get_polynomial(); break;
        case 5:
            if (neg)
                return get_left().get_polynomial() + get_right().get_polynomial(true);
            else
                return get_left().get_polynomial() - get_right().get_polynomial(true);
            break;
        case 6: return get_left().get_polynomial() + get_right().get_polynomial(); break;
        default: return false;
    }

}

double AbstractFunction::regula_falsi(double a, double b){
    double c;
    for (int i=0; i < MAX_ITER; i++){
        c = (a*get_value(b) - b*get_value(a))/ (get_value(b) - get_value(a));

        if (abs(get_value(c))<=EPS)
            return c;
        else if (get_value(c)*get_value(a) < 0)
            b = c;
        else
            a = c;
    }
    return c;
}

vector<double> AbstractFunction::get_roots(double start, double end){
    vector<double> critical_points;
    vector<double> roots;
    double i = start;
    while (i <= end){
        if (abs(get_value(i)*get_value(i+0.1)) <= EPS){
            if (abs(get_value(i)) <= EPS)
                roots.push_back(i);
        }
        else if (get_value(i)*get_value(i+0.1) < 0)
            critical_points.push_back(i);

        i += 0.1;
    }

    for(int i = 0; i < (int)critical_points.size(); i++)
        roots.push_back(regula_falsi(i, i+0.1));

    return roots;
}

double AbstractFunction::get_integral_value(double a, double b){
    double DIV = (b-a)*1100;
    double h = (b-a)/DIV;
    double T=0;
    double x=a;

    T=0.5*get_value(x);
    for(int i=1; i<DIV; i++){
        x+=h;
        T+= get_value(x);
    }
    x+=h;
    T+=0.5*get_value(x);
    T*=h;

    return T;
}


ExpAbstractFunction::ExpAbstractFunction():AbstractFunction(){
  value = Function("exp");
  str_label = value.get_value();
  str_label = value.get_value();
  type = value.get_type();
  leaf_mark = 1;
}

string ExpAbstractFunction::get_derivative(){
    return "exp";
}

double ExpAbstractFunction::get_value(double x, bool neg, bool div){
    return exp(x);
}

LnAbstractFunction::LnAbstractFunction():AbstractFunction(){
    value = Function("ln");
    str_label = value.get_value();
    str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 2;
}

string LnAbstractFunction::get_derivative(){
    return "1/";
}

double LnAbstractFunction::get_value(double x, bool neg, bool div){
    return log(x);
}

LogAbstractFunction::LogAbstractFunction(double a):AbstractFunction(){
    value = Function("log");
    str_label = value.get_value();
    str_label = value.get_value();
    type = value.get_type();
    base = a;
    leaf_mark = 3;
}

double LogAbstractFunction::get_base(){
    return base;
}

string LogAbstractFunction::get_derivative(){
    return "1/(ln(10)*";
}

double LogAbstractFunction::get_value(double x, bool neg, bool div){
    return log(x)/log(base);
}

CosAbstractFunction::CosAbstractFunction():AbstractFunction(){
    value = Function("cos");
    str_label = value.get_value();
    str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 4;
}

string CosAbstractFunction::get_derivative(){
    return "-sin";
}

double CosAbstractFunction::get_value(double x, bool neg, bool div){
    return cos(x);
}

SinAbstractFunction::SinAbstractFunction():AbstractFunction(){
    value = Function("sin");
    str_label = value.get_value();
    str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 5;
}

string SinAbstractFunction::get_derivative(){
    return "cos";
}

double SinAbstractFunction::get_value(double x, bool neg, bool div){
    return sin(x);
}

TanAbstractFunction::TanAbstractFunction():AbstractFunction(){
    value = Function("tan");
    str_label = value.get_value();
    str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 6;
}

string TanAbstractFunction::get_derivative(){
    return "1/(cos^2";
}

double TanAbstractFunction::get_value(double x, bool neg, bool div){
    return tan(x);
}

SqrtAbstractFunction::SqrtAbstractFunction():AbstractFunction(){
    value = Function("sqrt");
    str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 7;
}

string SqrtAbstractFunction::get_derivative(){
    return "(-1/2)*(1/sqrt";
}

double SqrtAbstractFunction::get_value(double x, bool neg, bool div){
    return sqrt(x);
}

NumAbstractFunction::NumAbstractFunction(Token T):AbstractFunction() {
    value = T;
    str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 0;
}

string NumAbstractFunction::get_derivative(){
    return "0";
}

double NumAbstractFunction::get_value(double x, bool neg, bool div){
    return stod(value.get_value());
}

VarAbstractFunction::VarAbstractFunction(Token T):AbstractFunction() {
    value = T;
    str_label = value.get_value();
    type = value.get_type();
    leaf_mark = 8;
}

string VarAbstractFunction::get_derivative(){
    return "1";
}

double VarAbstractFunction::get_value(double x, bool neg, bool div){
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


string AbstractFunction::get_derivative(){
    switch (operation.get_type()) {
        case -1:
            return get_leaf_derivative(leaf_mark, display()); break;
        // composition
        case 1:{
            string r1 = get_right().get_derivative();
            if (r1 == "1"){
                if (get_left().leaf_mark == 3 or get_left().leaf_mark == 6 or get_left().leaf_mark ==7){
                    return get_left().get_derivative() + "(" + get_right().display() + "))";
                }
                else{
                    return get_left().get_derivative() + "(" + get_right().display() + ")";
                }


            }
            else{
                if (get_left().leaf_mark == 3 or get_left().leaf_mark == 6 or get_left().leaf_mark ==7){
                    return mult_strings(get_left().get_derivative() + "(" + get_right().display() + "))", r1);
                }
                else{
                    return mult_strings(get_left().get_derivative() + "(" + get_right().display() + ")", r1);
                }
            }
            break;
        }
        // power
        case 2: {
            // left is a num
            if(get_left().leaf_mark == 0){
                string t = mult_strings(display(), "ln(" + get_left().display() + ")");
                return mult_strings(t, get_right().get_derivative());
            }
            // right is a num
            if(get_right().leaf_mark == 0){
                string new_exp = to_string(stoi(get_right().display()) - 1);
                string l2 = mult_strings(get_right().display(), pow_strings(get_left().display(), new_exp));
                /*if (new_exp == "1"){
                    l2 = get_right().get_str_label() + "(" + get_left().get_str_label() + ")";
                }
                else{
                    l2 = get_right().get_str_label() + "(" + get_left().get_str_label() + ")^" + new_exp;
                }*/
                string r2 = get_left().get_derivative() ;
                return mult_strings(l2, r2);
                /*if (r2 != "1"){
                    return l2 + "*(" + r2 + ")";
                }
                else{
                    return l2;
                }*/
            }
            break;
        }
        // division
        case 3:{
            string l3 = mult_strings(get_left().get_derivative(), get_right().display());
            string r3 = mult_strings(get_right().get_derivative(), get_left().display());
            string tog = sub_strings(l3, r3);
            string denom = pow_strings(get_right().display(), "2");
            return div_strings(tog, denom);
        }

        // multiplication
        case 4: {
            string l4 = mult_strings(get_left().get_derivative(), get_right().display());
            string r4 = mult_strings(get_right().get_derivative(), get_left().display());
            return add_strings(l4, r4);
            break;
        }

        // subtraction
        case 5:{
            return sub_strings(get_left().get_derivative(), get_right().get_derivative());
            break;
        }
        // addition
        case 6:{
            return add_strings(get_left().get_derivative(), get_right().get_derivative());
            break;
        }
        default: return "";
    }
}

string add_strings(string l, string r){
    l = del_exterior_parentheses(l);
    r = del_exterior_parentheses(r);
    if (l == "0"){
        return r;
    }
    if (r == "0"){
        return l;
    }
    if (l.length() <= 1 and r.length() <= 1){
        return l + "+" + r;
    }
    if (l.length() <= 1){
        return l + "+(" + r + ")";
    }
    if (r.length() <= 1){
        return "(" + l + ")+" + r;
    }
    return "(" + l + ")+(" + r + ")";
}
string sub_strings(string l, string r){
    l = del_exterior_parentheses(l);
    r = del_exterior_parentheses(r);
    if (l == "0"){
        return "-" + r;
    }
    if (r == "0"){
        return l;
    }
    if (l.length() <= 1 and r.length() <= 1){
        return l + "-" + r;
    }
    if (l.length() <= 1){
        return l + "-(" + r + ")";
    }
    if (r.length() <= 1){
        return "(" + l + ")-" + r;
    }
    return "(" + l + ")-(" + r + ")";
}
string mult_strings(string l, string r){
    l = del_exterior_parentheses(l);
    r = del_exterior_parentheses(r);
    if (l == "0"){
        return "0";
    }
    if (r == "0"){
        return "0";
    }
    if (l == "1"){
        return r;
    }
    if (r == "1"){
        return l;
    }
    if (l.length() <= 1 and r.length() <= 1){
        return l + "*" + r;
    }
    if (l.length() <= 1){
        return l + "*(" + r + ")";
    }
    if (r.length() <= 1){
        return "(" + l + ")*" + r;
    }
    return "(" + l + ")*(" + r + ")";
}
string div_strings(string l, string r){
    l = del_exterior_parentheses(l);
    r = del_exterior_parentheses(r);
    if (l == "0"){
        return "0";
    }
    if (r == "0"){
        return "division by 0 error";
    }
    if (r == "1"){
        return l;
    }
    if (l.length() <= 1 and r.length() <= 1){
        return l + "/" + r;
    }
    if (l.length() <= 1){
        return l + "/(" + r + ")";
    }
    if (r.length() <= 1){
        return "(" + l + ")/" + r;
    }
    return "(" + l + ")/(" + r + ")";
}

string pow_strings(string l, string r){
    l = del_exterior_parentheses(l);
    r = del_exterior_parentheses(r);
    if (l == "0"){
        return "0";
    }
    if (l == "1"){
        return "1";
    }
    if (r == "0"){
        return "1";
    }
    if (r == "1"){
        return l;
    }
    if (l.length() <= 1 and r.length() <= 1){
        return l + "^" + r;
    }
    if (l.length() <= 1){
        return l + "^(" + r + ")";
    }
    if (r.length() <= 1){
        return "(" + l + ")^" + r;
    }
    return "(" + l + ")^(" + r + ")";
}


string AbstractFunction::get_leaf_derivative(int n, string val){
    switch (n) {
        case 0: return NumAbstractFunction(Num(val)).get_derivative(); break;
        case 1: return ExpAbstractFunction().get_derivative(); break;
        case 2: return LnAbstractFunction().get_derivative(); break;
        case 3: return LogAbstractFunction(10).get_derivative(); break;
        case 4: return CosAbstractFunction().get_derivative(); break;
        case 5: return SinAbstractFunction().get_derivative(); break;
        case 6: return TanAbstractFunction().get_derivative(); break;
        case 7: return SqrtAbstractFunction().get_derivative(); break;
        case 8: return VarAbstractFunction(Variable(val)).get_derivative(); break;
        default: return "";
    }
}
