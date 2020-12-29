#include "derivatives.hpp"
#include "Tokenizer.hpp"
//#include "MainWindow/mainwindow.h"


#include <QApplication>
#include <QtTest>
#include <sstream>
#include <iostream>




map<string, int> type_m = {{"~",1},{"^",2},{"/",3},{"*",4},{"-",5},{"+",6},{"(",7},{")",8},{"_",9}};

AF::AF(vector<Token> fun){
    end = false;
    base_type = 1;
    vect_label = fun;
    str_label = vect_to_str(fun);
    cout << str_label << '\n';
    // parentheses(&fun);

    if (int(fun.size()) == 1 && (fun[0].is_super_token() == false)){
        end = true;
        assign(fun[0],leaf);
        left = nullptr;right = nullptr;



    }else{
     if (int(fun.size()) == 1 && fun[0].is_super_token()){
                fun = simplify(fun[0].get_value(),'x');
     }
    operation =  Operator();
    int counter = 0;
    vector<Token>::iterator j = fun.begin();
    for (vector<Token>::iterator i = fun.begin();i<fun.end();i++){
        if (i->get_type() > 0){
            int val = type_m[i->get_value()];
            //cout << val<< "  " << i-> get_value()<<'\n';
            if ( val == 7){counter += 1;}
            else if (val == 8){counter -= 1;}
            else if (val > type_m[operation.get_value()] and counter == 0){
                operation = Operator(i->get_value());
                j = i;
            }

        }


    }
    //cout << "string is " << str_label<<'\n';
    //cout << "Operation: " << operation.get_value()<< " and val "<<operation.get_type() << '\n';
    if (type_m[operation.get_value()] > 0){
        //cout << "Im here" << str_label<<'\n';
        vector<Token> l, r;
        for (vector<Token>::iterator i = fun.begin();i<fun.end();i++){
            if (i<j){
                l.push_back(*i);
            }
            else if (i>j){
                r.push_back(*i);

            }
        }
        //cout << "left: "<< vect_to_str(l)<<" O: "<<j->get_value() << ". right: " << vect_to_str(r)<<'\n';


        if (fun[0].is_super_token()){
            l = simplify(fun[0].get_value(),'x');
        }
        if (fun[2].is_super_token()){
            r = simplify(fun[2].get_value(),'x');
        }
        left = new AF(l);
        right = new AF(r);

        str_label = left->get_str_label() + this->get_operation().get_value()+ right->get_str_label();


    } else {
        //cout << "not a success" << str_label <<'\n';
    }
    //cout << "success!" << str_label <<'\n';
    }}

void assign(Token fun, SF &leaf){
    int val = fun.get_type();
    if (val == -1){
        leaf = Fnum(fun);
    } else if (val == -2){
        string function = fun.get_value();
        if (function == "exp"){
            leaf = Fexp(fun);
        }
        if (function == "ln"){
            leaf = Fln(fun);
        }
        if (function == "log"){
            leaf = Flog(fun);
        }
        if (function == "cos"){
            leaf = Fcos(fun);
        }
        if (function == "sin"){
            leaf = Fsin(fun);
        }
        if (function == "tan"){
            leaf = Ftan(fun);
        }
        if (function == "sqrt"){
            leaf = Fsqrt(fun);
        }
    }else if (val == -3){
        leaf = Fvar(fun);
    }else if (val == -4){
        leaf = Fcomp(fun);
    }

}


AF::AF(AF left, AF right, Operator operation){
    this->left = &left;
    this->right = &right;
    end = false;
    this->operation = operation;
    this->str_label = "";

}

AF::AF(int type, string str){
    this->left = nullptr;
    this->right = nullptr;
    this->operation = Operator();
    end = true;
    this->base_type = type;
    this->str_label = str;
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

string vect_to_str(vector<Token> fun){
    string sfun = "";
    for (int i = 0; i< int(fun.size());i++){
        sfun += fun[i].get_value();
        if (i != int(fun.size())-1){
            sfun += " ";
        }
    }
    return sfun;
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


string AF::display(){
    if (this->left == nullptr and this->right == nullptr){
        return get_str_label();
    }else{
        return "(" +get_left().display() + " " + operation.get_value() + " " + get_right().display() + ")";
    }
}


int AF::get_base_type(){
    return base_type;
}
void AF::set_base_type(int type){
    this->base_type = type;
}




LeafFunc::LeafFunc(string func){
    str_label = func;
}
string LeafFunc::get_str_label(){
    return str_label;
}
int LeafFunc::get_base_type(){
    return base_type;
}


VarF::VarF(string var):LeafFunc(var){
    str_label= var;
    base_type = 1;
}
AF VarF::to_AF(){
    return AF(1, str_label);
}
AF VarF::solve(){
    return ConsF("1").to_AF();
}



ConsF::ConsF(string cons):LeafFunc(cons){
    str_label= cons;
    base_type = 2;
}
AF ConsF::to_AF(){
    return AF(2, str_label);
}
AF ConsF::solve(){
    return ConsF("0").to_AF();
}




NumF::NumF(string c):LeafFunc(c){
    str_label= c;
    base_type = 3;
}
AF NumF::to_AF(){
    return AF(3, str_label);
}
AF NumF::solve(){
    return AF();
}




ExpF::ExpF():LeafFunc(){
    str_label= "exp";
    base_type = 4;
}
AF ExpF::to_AF(){
    return AF(4, str_label);
}
AF ExpF::solve(){
    return ExpF().to_AF();
}





LogaF::LogaF():LeafFunc(){
    str_label= "log_a";
    base_type = 5;
}
AF LogaF::to_AF(){
    return AF(5, str_label);
}

AF LogaF::solve(){
    AF l = ConsF("ln(a)").to_AF();
    AF r = VarF("x").to_AF();
    AF step = AF(l, r, Operator("*"));
    AF c = ConsF("1").to_AF();
    return AF(c, step, Operator("/"));

}




CosF::CosF():LeafFunc(){
    str_label= "cos";
    base_type = 6;
}
AF CosF::to_AF(){
    return AF(6, str_label);
}
AF CosF::solve(){
    AF l = ConsF("-1").to_AF();
    AF r = SinF().to_AF();
    return AF(l, r, Operator("*"));

}




SinF::SinF():LeafFunc(){
    str_label= "sin";
    base_type = 7;
}
AF SinF::to_AF(){
    return AF(7, str_label);
}
AF SinF::solve(){
    return CosF().to_AF();
}


TanF::TanF():LeafFunc(){
    str_label= "tan";
    base_type = 8;
}
AF TanF::to_AF(){
    return AF(8, str_label);
}
AF TanF::solve(){
    AF l = ConsF("1").to_AF();
    AF temp_l = CosF().to_AF();
    AF temp_r = VarF("x").to_AF();
    AF r = AF(temp_l, temp_r, Operator("^"));
    return AF(l, r, Operator("/"));
}



LnF::LnF():LeafFunc(){
    str_label= "ln";
    base_type = 9;
}
AF LnF::to_AF(){
    return AF(9, str_label);
}

AF LnF::solve(){
    AF l = ConsF("1").to_AF();
    AF r = VarF("x").to_AF();
    return AF(l, r, Operator("/"));
}



SqrtF::SqrtF():LeafFunc(){
    str_label= "ln";
    base_type = 10;
}
AF SqrtF::to_AF(){
    return AF(10, str_label);
}

AF SqrtF::solve(){
    AF l = ConsF("1/2").to_AF();
    AF temp_l = VarF("x").to_AF();
    AF temp_r = ConsF("-1/2").to_AF();
    AF r = AF(temp_l, temp_r, Operator("^"));
    return AF(l, r, Operator("*"));
}



SubF::SubF(string func):LeafFunc(func){
    str_label = func;
    base_type = 11;
}
AF SubF::to_AF(){
    return AF(simplify(str_label, 'x'));
}




// AF Exp::solve(){
//     if(base.get_value() == "e"){
//         return Exp(base, value).to_AF();
//     }
//     AF r = Loga(Token(base), Token("e")).to_AF();
//     return AF(to_AF(), r, Operator("*"));
// }




AF derive(AF Func){
    cout << "Current depth is: " <<Func.get_str_label() << '\n';
    if (Func.get_end() == false){

        int val = type_m[Func.get_operation().get_value()];
        if(val == 6){
            // addition
            return AF(derive(Func.get_left()), derive(Func.get_right()), Operator("+"));

        }
        if(val == 5){
            // subtraction
            return AF(derive(Func.get_left()), derive(Func.get_right()), Operator("-"));
        }
        if(val == 4){
            // multiplication
            AF l= AF(derive(Func.get_left()), Func.get_right(), Operator("*"));
            AF r = AF(derive(Func.get_right()), Func.get_left(), Operator("*"));
            return AF(l, r, Operator("+"));

        }
        if(val == 3){
            // division
            AF l1= AF(derive(Func.get_left()), Func.get_right(), Operator("*"));
            AF r2 = AF(Func.get_left(), derive(Func.get_right()), Operator("*"));
            AF l2 = AF(VarF("x").to_AF(), ConsF("2").to_AF(), Operator("^"));
            return AF(AF(l1, r2, Operator("-")), AF(l2, Func.get_right(), Operator("~")), Operator("/"));
        }
        if(val == 2){
            // power
            // do difference exp vs polynomial
            // assuming no x in exponent
            AF left = AF(derive(Func.get_left()),Func.get_right(),Operator("*"));
            AF exponent = AF(Func.get_right(),AF({Num("1")}),Operator("-"));
            AF right = AF(Func.get_left(),exponent,Operator("^"));
            return  AF(left,right,Operator("*"));

        }
        if(val == 1){
            // composition
            AF l = AF(derive(Func.get_left()), Func.get_right(), Operator("~"));
            return AF(l , derive(Func.get_right()), Operator("*"));
        }
        else {
            cout << "couldn't find the right path"<<'\n';return AF();
        }

    }
    else {
        cout << "currently at the leaf: "<<Func.get_str_label()<<'\n';
        //SF leaf = Func.get_leaf();
        //return sf_derivatives(leaf);
        if(Func.get_base_type() == 1){
            VarF v = VarF(Func.get_str_label());
            return v.solve();
        }
        if(Func.get_base_type() == 2){
            ConsF c = ConsF(Func.get_str_label());
            return c.solve();
        }
        if(Func.get_base_type() == 3){
            // num ??
            return AF();
        }
        if(Func.get_base_type() == 4){
            ExpF e = ExpF();
            return e.solve();
        }
        if(Func.get_base_type() == 5){
            LogaF l = LogaF();
            return l.solve();
        }
        if(Func.get_base_type() == 6){
            CosF  c = CosF();
            return c.solve();
        }
        if(Func.get_base_type() == 7){
            SinF  s = SinF();
            return s.solve();
        }
        if(Func.get_base_type() == 8){
            TanF  t = TanF();
            return t.solve();
        }
        if(Func.get_base_type() == 9){
            LnF l = LnF();
            return l.solve();
        }
        if(Func.get_base_type() == 10){
            SqrtF  s = SqrtF();
            return s.solve();
        }
        if(Func.get_base_type() == 11){
            return derive(AF(simplify(Func.get_str_label(), 'x')));
        }
        return AF();
    }

//map<string, int> type_m = {{"~",1},{"^",2},{"/",3},{"*",4},{"-",5},{"+",6},{"(",7},{")",8},{"_",9}};
}



AF sf_derivatives(SF &leaf){
    if (leaf.get_type() == 1){
        return AF({Num("1")});
    }else if (leaf.get_type() == 2 || leaf.get_type() == 3){
        return AF({Num("0")});
    }else{
        cout <<leaf.get_type()<< "wtf"<<'\n';return AF();/*else if (leaf.get_type() == 4){
        return AF({Function("exp")});
    }else if (leaf.get_type() == 5){
        return AF({Function("")});
    }*/}
}






