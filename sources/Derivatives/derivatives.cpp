#include "derivatives.hpp"
#include "Tokenizer.hpp"
#include "Operators.hpp"

map<string, int> type_m = {{"~",1},{"^",2},{"/",3},{"*",4},{"-",5},{"+",6},{"(",7},{")",8},{"_",9}};

AbstractFunction::AbstractFunction(vector<Token> fun, char var){
    type = 1;
    vect_label = fun;
    this->var = var;
    while ((int)fun.size() == 1 && (fun[0].get_type() == -4)){
        fun = simplify(fun[0].get_value(), this->var);
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
        int j = 0;
        for (int i = 0; i < (int)fun.size(); i++)
         if (fun[i].get_type() > operation.get_type()){
                 operation = Operator(fun[i].get_value());
                 j = i;
         }

        if (operation.get_type() > 0){
            vector<Token> l, r;

            for (int i = 0; i < (int)fun.size(); i++){
             if(i < j)
                 l.push_back(fun[i]);
             else if (i > j)
                 r.push_back(fun[i]);
            }

            left = new AbstractFunction(l, var);
            right = new AbstractFunction(r, var);

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



AbstractFunction::AbstractFunction(AbstractFunction left, AbstractFunction right, Operator operation, char var){
    this->left = &left;
    this->right = &right;
    this->operation = operation;
    this->str_label = "";
    this->var = var;
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

double AbstractFunction:: operator()(const double &x){
    return get_value(x);
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
            return par_left + s1  + s2 + par_right;

        else
            return par_left + s1  + operation.get_value() + s2 + par_right;
    }

    return "display() error!!";
}



// be careful when divion with 0
double AbstractFunction::get_value(double x, bool neg){
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
                return get_left().get_value(x, false)+get_right().get_value(x, true);
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
        case 2:
            if (x > 0)
                return log(x);
            else{
                cout<< "Error\n";
                return -9999999;
            }
            break;
        case 3:
            if (x > 0)
                return log(x)/log(10);
            else{
                cout<< "Error\n";
                return -9999999;
            }
            break;
        case 4: return cos(x); break;
        case 5: return sin(x); break;
        case 6: return tan(x); break;
        case 7:
            if (x >= 0)
                return sqrt(x);
            else{
                cout<< "Error\n";
                return -9999999;
            }
            break;
        case 8: return x; break;
        default: return 0;
    }
}


bool AbstractFunction::is_polynomial(){
    switch (operation.get_type()) {
        case -1:
            if (leaf_mark == 0 || leaf_mark == 8 || leaf_mark == 9)
                return true;
            else
                return false;
            break;
        case 1: return false; break;
        case 2: return get_left().is_polynomial() && (get_right().leaf_mark == 0 && (is_int(get_right().get_value(0)))); break;
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
            if (leaf_mark == 0 || leaf_mark == 9){
                Rational c[1];
                c[0] = Rational((get_value(0)));
                return PolynomialRational(c, 0, var);
            }
            else{
                Rational c[2] = {};
                c[1] = Rational(1,1);
                    return PolynomialRational(c, 1, var);
            }
            break;
        }
        case 2: {
            int n = (int)get_right().get_value(0);
//            PolynomialRational P = get_left().get_polynomial();
//            PolynomialRational Q = P.copy();
//            for (int i = 1; i < n; i++)
//                Q = Q * P;

//            return Q;
//            break;
            Rational c[n+1];
            for (int i = 0; i <= n; i++)
                c[i] = Rational(0, 1);
            c[n] = Rational(1,1);
            return PolynomialRational(c, n, var);
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


bool is_int(double x){
    string s = to_str(x);
    bool dot = false;
    for (int i = 0; i < (int)s.size(); i++){
        if (s[i] == '.')
            dot = true;
        else if (dot && s[i] != '0')
            return false;
    }

    return true;
}




//----------------------------------------------------------------------------------------
// finding derivatives BELOW


bool check_par(vector<Token> v){
    for (int i = 0; i < (int)v.size(); i++)
        if (v[i].get_type() >= 5)
            return false;

    return true;
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

string arith_add_sub(string func,  char var){
    vector<Token> vt = simplify(func,var);
    std::cout<<vt.size()<<'\n';
    double starting_number;
    bool start_found = false;
    int start;
    bool pairs_exist = true;

    if (vt.size() == 1){
        return vt[0].get_value();
    }

    while(pairs_exist){
        pairs_exist = false;
        start_found = false;
        pairs_exist = false;
        for(std::size_t i=0; i<vt.size(); i = i+2){
            if(vt[i].get_type() == -1 && (i < vt.size()-1)){
                // found number / not last number



                //find number with minus or plus pair
                if (vt[i+1].get_type() == 5 || vt[i+1].get_type() == 6){

                    if (!start_found){
                        starting_number = stod(vt[i].get_value());
                        start = i;
                        start_found = true;
                    }
                    //minus
                    else if(vt[i-1].get_type() == 5){
                        double new_num = starting_number - stod(vt[i].get_value());
                        vt[start] = simplify(to_string(new_num), var)[0];
                        vt.erase(vt.begin()+i-1, vt.begin()+i+1);
                        pairs_exist = true;
                        break;
                    }
                    //add
                    else if(vt[i-1].get_type() == 6){
                        double new_num = starting_number + stod(vt[i].get_value());
                        vt[start] = simplify(to_string(new_num), var)[0];
                        vt.erase(vt.begin()+i-1, vt.begin()+i+1);
                        pairs_exist = true;
                        break;
                    }

                }
            }

            //number is last and start is found

            else if(vt[i].get_type() == -1 && start_found){
                //minus
                if(vt[i-1].get_type() == 5){
                    double new_num = starting_number - stod(vt[i].get_value());
                    vt[start] = simplify(to_string(new_num), var)[0];
                    vt.erase(vt.begin()+i-1, vt.begin()+i+1);
                    pairs_exist = true;
                    break;
                }
                //add
                else if(vt[i-1].get_type() == 6){

                    double new_num = starting_number + stod(vt[i].get_value());
                    vt[start] = simplify(to_string(new_num), var)[0];
                    vt.erase(vt.begin()+i-1, vt.begin()+i+1);
                    pairs_exist = true;
                    break;
                }
            }

            else if(vt[i].get_type() == -4){
                // super token
                vt[i] = SuperToken(arith_add_sub(vt[i].get_value(), var));
            }


        }
    }
    return vect_to_str(vt);
}

string arith_mult_div(string func, char var){
    vector<Token> vt = simplify(func,var);
    double starting_number;
    bool start_found = false;
    int start;
    bool pairs_exist = true;

    if (vt.size() == 1){
        return vt[0].get_value();
    }

    while(pairs_exist){
        pairs_exist = false;
        start_found = false;
        pairs_exist = false;
        for(std::size_t i=0; i<vt.size(); i = i+2){
            if (i != 0){
                if(vt[i-1].get_type() == 5 || vt[i-1].get_type() == 6){
                    start_found = false;
                }
            }
            if(vt[i].get_type() == -1 && (i < vt.size()-1)){
                // found number / not last number



                //find number with minus or plus pair
                if (vt[i+1].get_type() == 3 || vt[i+1].get_type() == 4){

                    if (!start_found){
                        starting_number = stod(vt[i].get_value());
                        start = i;
                        start_found = true;
                    }
                    //div
                    else if(vt[i-1].get_type() == 3){
                        double new_num = starting_number / stod(vt[i].get_value());
                        vt[start] = simplify(to_string(new_num), var)[0];
                        vt.erase(vt.begin()+i-1, vt.begin()+i+1);
                        pairs_exist = true;
                        break;
                    }
                    //mult
                    else if(vt[i-1].get_type() == 4){
                        double new_num = starting_number * stod(vt[i].get_value());
                        vt[start] = simplify(to_string(new_num), var)[0];
                        vt.erase(vt.begin()+i-1, vt.begin()+i+1);
                        pairs_exist = true;
                        break;
                    }

                }
            }

            //number is last and start is found

            else if(vt[i].get_type() == -1 && start_found){
                //div
                if(vt[i-1].get_type() == 3){
                    double new_num = starting_number / stod(vt[i].get_value());
                    vt[start] = simplify(to_string(new_num), var)[0];
                    vt.erase(vt.begin()+i-1, vt.begin()+i+1);
                    pairs_exist = true;
                    break;
                }
                //mult
                else if(vt[i-1].get_type() == 4){
                    double new_num = starting_number * stod(vt[i].get_value());
                    vt[start] = simplify(to_string(new_num), var)[0];
                    vt.erase(vt.begin()+i-1, vt.begin()+i+1);
                    pairs_exist = true;
                    break;
                }
            }

            else if(vt[i].get_type() == -4){
                // super token
                vt[i] = SuperToken(arith_mult_div(vt[i].get_value(), var));
            }
        }
    }
    return vect_to_str(vt);
}


string remove_mult_sign(string func, char var){
    vector<Token> vt = simplify(func,var);

    for(std::size_t i=0; i<vt.size(); ++i){
        if(vt[i].get_type() == -1 && (i<vt.size()-2)){
            // found number
            if(vt[i+1].get_type() == 4){
                //found mult
                if(vt[i+2].get_type() == -3){
                    //found variable
                    vt.erase(vt.begin()+i+1);
                }
            }
        }
        else if(vt[i].get_type() == -4){
            vt[i] = SuperToken(remove_mult_sign(vt[i].get_value(), var));
        }

    }
    return vect_to_str(vt);
}

string vect_to_str(vector<Token> vt){
    string final;
    for(std::size_t j=0; j<vt.size(); ++j){
        if(vt[j].get_type() == 1){
            final = final + "(" + vt[j+1].get_value() + ")";
            j++;
        }
        else if(vt[j].get_type() == -1){
            final = final + Rational(stod(vt[j].get_value())).get_string();
        }
        else if(vt[j].get_type() == -4){
            final = final + "(" + vt[j].get_value() +")";
        }
        else {
            final = final + vt[j].get_value();
        }

    }
    return final;
}


string AbstractFunction::get_leaf_derivative(int n){
    switch (n) {
        case 0: {
            return "0";
            break;
        }
        case 1: {
            return "exp";
            break;
        }
        case 2: {
            return "1/";
            break;
        }
        case 3: {
            return "1/(ln(10)*";
            break;
        }
        case 4: {
            return "-sin";
            break;
        }
        case 5: {
            return "cos";
            break;
        }
        case 6: {
            return "1/(cos";
            break;
        }
        case 7: {
            return "1/(2*sqrt";
            break;
        }
        case 8: {
            return "1";
            break;
        }
        default: return "";
    }
}

string AbstractFunction::get_derivative(vector<string> *step_by_step){
    switch (operation.get_type()) {
        case -1:
            return get_leaf_derivative(leaf_mark); break;
        // composition
        case 1:{

            string r1 = get_right().get_derivative(step_by_step);
            if (r1 == "0"){
                return  "0";
            }
            else if (r1 == "1"){
                //string sbs = "d/dx[" + get_left().display() +"]";
                //step_by_step.push_back(sbs);
                if (get_left().leaf_mark == 3 || get_left().leaf_mark == 7){
                    string res = get_left().get_derivative(step_by_step) + get_right().display() + ")";
                    string sbs = "d/dx[" + display() + "] = " + res;
                    (*step_by_step).push_back(sbs);
                    return res;
                }
                else if (get_left().leaf_mark == 6){
                    string res = get_left().get_derivative(step_by_step) + get_right().display() + ")^2";
                    string sbs = "d/dx[" + display() + "] = " + res;
                    (*step_by_step).push_back(sbs);
                    return res;
                }

                else {
                    string res = get_left().get_derivative(step_by_step) + get_right().display();
                    string sbs = "d/dx[" + display() + "] = " + res;
                    (*step_by_step).push_back(sbs);
                    return res;
                }
            }
            else{

                if (get_left().leaf_mark == 3 || get_left().leaf_mark == 7){
                    string left_str = get_left().get_derivative(step_by_step) + "(" + get_right().display() + "))";
                    string sbs = "Chain Rule with u = "+ get_right().display() +" => d/du[" + get_left().display() + "(u)] * d/dx[" + get_right().display() +"]";
                    (*step_by_step).push_back(sbs);
                    string res = mult_strings(left_str, r1);
                    return res;
                }
                if (get_left().leaf_mark == 6){
                    string left_str = get_left().get_derivative(step_by_step) + "(" + get_right().display() + "))^2";
                    string sbs = "Chain Rule with u = "+ get_right().display() +" => d/du[" + get_left().display() + "(u)] * d/dx[" + get_right().display() +"]";
                    (*step_by_step).push_back(sbs);
                    string res = mult_strings(left_str, r1);
                    return res;
                }
                else{
                    string left_str = get_left().get_derivative(step_by_step) + "(" + get_right().display() + ")";
                    string sbs = "Chain Rule with u = "+ get_right().display() +" => d/du[" + get_left().display() + "(u)] * d/dx[" + get_right().display() +"]";
                    (*step_by_step).push_back(sbs);
                    string res = mult_strings(left_str, r1);
                    return res;
                }
            }
            break;
        }
        // power
        case 2: {
            // left is a num
            if(get_left().leaf_mark == 0){
                string sbs2 = "Exponential rule => [" + mult_strings(display(), "ln(" + get_left().display() + ")") + "] * d/dx[" + get_right().display() + "]";
                (*step_by_step).push_back(sbs2);
                return mult_strings(mult_strings(display(), "ln(" + get_left().display() + ")"), get_right().get_derivative(step_by_step));
            }
            // right is a num
            else if(get_right().leaf_mark == 0){
                string new_exp = Rational(get_right().get_value(0) - 1).get_string();
                string l2 = mult_strings(get_right().display(), pow_strings(get_left().display(), new_exp));
                string r2 = get_left().get_derivative(step_by_step) ;
                string sbs2 = "";
                string res = mult_strings(l2, r2);
                if (r2 != "1"){
                    sbs2 = "Power x Chain rule with u = "+ get_left().display()+ " => d/du[u^" + get_right().display() + "] * d/dx[" + get_left().display() + "] = "+ res;
                }
                else
                    sbs2 = "Power rule => d/dx[" + display() + "] = " + res ;
                (*step_by_step).push_back(sbs2);
                return res;
            }
            else
                return mult_strings(display(), AbstractFunction(simplify(get_right().display()+"*ln("+get_left().display() +")" , 'x')).get_derivative(step_by_step));

            break;
        }
        // division
        case 3:{
            if (get_right().get_operation().get_type() == -1 && get_right().leaf_mark == 0)
                return div_strings(get_left().get_derivative(step_by_step), get_right().display());
            string l3 = mult_strings(get_left().get_derivative(step_by_step), get_right().display());
            string r3 = mult_strings(get_right().get_derivative(step_by_step), get_left().display());
            string tog = sub_strings(l3, r3);
            string denom = pow_strings(get_right().display(), "2");
            string res = div_strings(tog, denom);
            string sbs = "Division rule => [ d/dx[" + get_left().display() +"] * [" + get_right().display() + "] - ["+ get_left().display() +"] * d/dx["+ get_right().display() + "] ] / [" + get_right().display() + "]^2 = " + res;
            (*step_by_step).push_back(sbs);
            return res;
            break;
        }
        // multiplication
        case 4: {
            string l4 = mult_strings(get_left().get_derivative(step_by_step), get_right().display());
            string r4 = mult_strings(get_right().get_derivative(step_by_step), get_left().display());
            string res = add_strings(l4, r4);
            string sbs = "Multiplication rule => d/dx[" + get_left().display() +"] * [" + get_right().display() + "] + ["+ get_left().display() +"] * d/dx["+ get_right().display() + "] = " + res;
            (*step_by_step).push_back(sbs);
            return res;
            break;
        }
        // subtraction
        case 5: {
            string res = sub_strings(get_left().get_derivative(step_by_step), get_right().get_derivative(step_by_step));
            string sbs = "Subtraction rule => d/dx[" + get_left().display() + "] - d/dx["+ get_right().display() + "] = " + res;
            (*step_by_step).push_back(sbs);
            return res;
            break;

        }
        // addition
        case 6: {
            string res = add_strings(get_left().get_derivative(step_by_step), get_right().get_derivative(step_by_step));
            string sbs = "Addition rule => d/dx[" + get_left().display() + "] + d/dx["+ get_right().display() + "] = " + res;
            (*step_by_step).push_back(sbs);
            return res;
            break;
        }
        default: return "";
    }
}

vector<string> AbstractFunction::derive(){
    vector<string> step_by_step = {};
    std::cout<<"1.1"<<'\n';
    string derivative = get_derivative(&step_by_step);
    std::cout<<derivative<<'\n';
    derivative = arith_add_sub(derivative, var);
    std::cout<<"1.2"<<'\n';
    derivative = arith_mult_div(derivative, var);
    std::cout<<"1.3"<<'\n';
    derivative = remove_mult_sign(derivative, var);
    std::cout<<"1.4"<<'\n';
    derivative = delete_layers_pare(derivative);
    AbstractFunction af_derivative = AbstractFunction(simplify(derivative));
    if (af_derivative.is_polynomial()){
        derivative = af_derivative.get_polynomial().get_string();
    }
    step_by_step.push_back("r");
    step_by_step.push_back(derivative);
    for (int i=0; i < (int)step_by_step.size(); i++){
        step_by_step[i] = delete_layers_pare(step_by_step[i]);
    }
    return step_by_step;
}


