#include "derivatives.hpp"
#include "Tokenizer.hpp"
#include "Operators.hpp"

map<string, int> type_m = {{"~",1},{"^",2},{"/",3},{"*",4},{"-",5},{"+",6},{"(",7},{")",8},{"_",9}};

AbstractFunction::AbstractFunction(vector<Token> fun){
    type = 1;
    vect_label = fun;
    while ((int)fun.size() == 1 && (fun[0].get_type() == -4)){
        fun = simplify(fun[0].get_value(),'x');
        type = -4;
    }

    if ((int)fun.size() == 0){
        this->left = nullptr;
        this->right = nullptr;
        this->operation = Operator();
        str_label ="";
        leaf_mark = 9;
    }

    if((int)fun.size() == 1){
        this->left = nullptr;
        this->right = nullptr;
        this->operation = Operator();
        this->str_label = fun[0].get_value();
        leaf_mark = assign(fun[0]);
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

             left = new AbstractFunction(l);
             right = new AbstractFunction(r);

             str_label = left->get_str_label() + this->get_operation().get_value()+ right->get_str_label();
         }
    }
}

int assign(Token fun){
    switch (fun.get_type()){
        case -1: return 0;  break;
        case -2:
            if (fun.get_value() == "exp")
                return 1;
            else if (fun.get_value() == "ln")
                return 2;
            else if (fun.get_value() == "log")
                return 3;
            else if (fun.get_value() == "cos")
                return 4;
            else if (fun.get_value() == "sin")
                return 5;
            else if (fun.get_value() == "tan")
                return 6;
            else if (fun.get_value() == "sqrt")
                return 7;
            else
                return -1;
            break;
        case -3: return 8;
        default: return -1;
    }
}



AbstractFunction::AbstractFunction(AbstractFunction left, AbstractFunction right, Operator operation){
    this->left = &left;
    this->right = &right;
    this->operation = operation;
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

    string par_left = "";
    string par_right= "";

    if (type == -4){
        par_left = "(";
        par_right= ")";
    }

    if (operation.get_type() == -1){
        return par_left + get_str_label() + par_right;
    }
    else{
        string s1 = get_left().display();
        string s2 = get_right().display();
        if (operation.get_value() == "~")
            return par_left + s1  + s2 +par_right;

        else
            return par_left + s1  + operation.get_value() + s2 + par_right;
    }

    return "display() error!!";
}

// be careful when divion with 0
double AbstractFunction::get_value(double x, bool neg){
    cout << get_str_label() << " " << operation.get_type()<<" "<<leaf_mark<< "\n";
    switch (operation.get_type()) {
        case -1:  return get_leaf_value(x, leaf_mark, get_str_label()); break;
        case 1: return get_left().get_value(get_right().get_value(x, false), false); break;
        case 2: return pow(get_left().get_value(x, false), get_right().get_value(x, false)); break;
        case 3:{
            double a = get_right().get_value(x, false);
            if(a == 0){
                cout << "Division with zero!\n";
                return 1;
            }
            else
                return get_left().get_value(x, false)/a;
            break;
        }
        case 4: return get_left().get_value(x, false)*get_right().get_value(x, false); break;
        case 5:
            if (neg)
                return get_left().get_value(x, false+get_right().get_value(x, true));
            else
                return get_left().get_value(x, false)-get_right().get_value(x, true);
            break;
        case 6:
            return get_left().get_value(x, false)+get_right().get_value(x, false); break;

        default: return 0;
    }
}


double AbstractFunction::get_leaf_value(double x, int n, string val){
    switch (n) {
        case 0: return stod(val); break;
        case 1: return exp(x); break;
        case 2: return log(x); break;
        case 3: return log(x)/log(10); break;
        case 4: return cos(x); break;
        case 5: return sin(x); break;
        case 6: return tan(x); break;
        case 7: return sqrt(x); break;
        case 8: return x; break;
        default: return 0;
    }
}


bool AbstractFunction::is_polynomial(){
    //cout << get_str_label() << " " << operation.get_type()<<" "<<get_left().leaf_mark<<" " <<get_right().leaf_mark<< "\n";
    switch (operation.get_type()) {
        case -1:
            if (leaf_mark == 0 || leaf_mark == 8 || leaf_mark == 9)
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

string AbstractFunction::get_derivative(){
    switch (operation.get_type()) {
        case -1:
            return get_leaf_derivative(leaf_mark); break;
        // composition
        case 1:{
            string r1 = get_right().get_derivative();
            if (r1 == "0")
                return  "0";
            else if (r1 == "1"){
                if (get_left().leaf_mark == 3 || get_left().leaf_mark == 6 || get_left().leaf_mark == 7){
                    return get_left().get_derivative() + get_right().display() + ")";
                }
                else{
                    return get_left().get_derivative() + get_right().display();
                }
            }
            else{
                if (get_left().leaf_mark == 3 || get_left().leaf_mark == 6 || get_left().leaf_mark == 7){
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
            if(get_left().leaf_mark == 0)
                return mult_strings(mult_strings(display(), "ln(" + get_left().display() + ")"), get_right().get_derivative());

            // right is a num
            else if(get_right().leaf_mark == 0){
                string new_exp = Rational(get_right().get_value(0) - 1).get_string();
                string l2 = mult_strings(get_right().display(), pow_strings(get_left().display(), new_exp));
                string r2 = get_left().get_derivative() ;
                return mult_strings(l2, r2);
            }
            else
                return mult_strings(display(), AbstractFunction(simplify(get_right().display()+"*ln("+get_left().display() +")" , 'x')).get_derivative());

            break;
        }
        // division
        case 3:{
            if (get_right().get_operation().get_type() == -1 && get_right().leaf_mark == 0)
                return div_strings(get_left().get_derivative(), get_right().display());

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
        case 5: return sub_strings(get_left().get_derivative(), get_right().get_derivative()); break;
        // addition
        case 6: return add_strings(get_left().get_derivative(), get_right().get_derivative()); break;
        default: return "";
    }
}

string AbstractFunction::get_leaf_derivative(int n){
    switch (n) {
        case 0: return "0"; break;
        case 1: return "exp"; break;
        case 2: return "1/"; break;
        case 3: return "1/(ln(10)*"; break;
        case 4: return "-sin"; break;
        case 5: return "cos"; break;
        case 6: return "1/cos^2"; break;
        case 7: return "1/(2*sqrt"; break;
        case 8: return "1"; break;
        default: return "";
    }
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

string add_strings(string l, string r){
    l = del_exterior_parentheses(l);
    r = del_exterior_parentheses(r);
    if (l == "0")
        return r;

    if (r == "0")
        return l;

    return  l + "+" + r ;
}
string sub_strings(string l, string r){
    l = del_exterior_parentheses(l);
    r = del_exterior_parentheses(r);

    if (r == "0")
        return l;

    if (l == "0")
        return "-" + r;

    return l + '-' + r;
}

bool check_par(vector<Token> v){
    for (int i = 0; i < (int)v.size(); i++)
        if (v[i].get_type() >= 5)
            return false;

    return true;
}

string mult_strings(string l, string r){
    l = del_exterior_parentheses(l);
    r = del_exterior_parentheses(r);
    if (l == "0" || r =="0")
        return "0";

    else if (l == "1")
        return r;

    else if (r == "1")
        return l;


    bool left_side = check_par(simplify(l, 'x'));
    bool right_side = check_par(simplify(r, 'x'));


    if (left_side && right_side)
        return l + "*" + r;

    else if (left_side)
        return l + "*(" + r + ")";

    else if (right_side)
        return "(" + l + ")*" + r;

    return "(" + l + ")*(" + r + ")";
}
string div_strings(string l, string r){
    l = del_exterior_parentheses(l);
    r = del_exterior_parentheses(r);
    if (l == "0")
        return "0";

    else if (r == "0")
        return "division by 0 error";

    else if (r == "1")
        return l;

    bool left_side = check_par(simplify(l, 'x'));

    if (left_side)
        return l + "/" + r;

    return "(" + l + ")/"+r;
}

string pow_strings(string l, string r){
    l = del_exterior_parentheses(l);
    r = del_exterior_parentheses(r);
    if (l == "0")
        return "0";

    else if (l == "1")
        return "1";

    else if (r == "0")
        return "1";

    else if (r == "1")
        return l;

    int token_left = simplify(l, 'x').size();
    int token_right = simplify(r, 'x').size();
    if (token_left <= 1 and token_right <= 1)
        return l + "^" + r;

    if (token_left <= 1)
        return l + "^(" + r + ")";

    else if (token_right <= 1)
        return "(" + l + ")^" + r;

    return "(" + l + ")^(" + r + ")";
}


