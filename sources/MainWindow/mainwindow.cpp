#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Equations/polynomial.hpp"
#include "functionPreprocessing.hpp"
#include "ImageRecognition/imagePrediction.hpp"
#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <iostream>
#include <QDebug>
#include <QFont>
#include <QWidget>
#include <QList>
#include <QString>
#include <QScrollArea>
#include <QShortcut>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


//MANUALLY INPUT EQUATION BUTTON

    QFont input_font("Arial", 20);

    QShortcut* enter = new QShortcut(QKeySequence("Return"), this);

    equation_input = new QLineEdit(this);
    equation_input-> setPlaceholderText("example: x^3 - 2x^2 - x + 2 = 0");
    equation_input->setFont(input_font);

    confirm = new QPushButton(this);
    confirm->setText("Confirm");
    confirm->setFont(input_font);
    confirm->setStyleSheet("background-color: rgb(216, 242, 196)");



//UPLOAD FILE BUTTON

    upload_file = new QPushButton(this);
    upload_file->setText("Upload file");
    upload_file->setFont(input_font);


//RESULT



//LAYOUT

    main_layout = new QVBoxLayout(this); //main layout of page, then layouts defined descending vertically

    top_layout = new QVBoxLayout(this);
    top_layout->addWidget(title_group());
    top_layout->addWidget(manual_input_group());
    top_layout->addWidget(upload_group());

    /*
    steps_layout = new QVBoxLayout(this);
    results_layout = new QHBoxLayout(this);
    //Setting scrollable box for steps
    QWidget *subwindow = new QWidget();
    subwindow ->setLayout(steps_layout);
    QScrollArea *scrollarea = new QScrollArea(this);
    scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollarea->setWidgetResizable( true );
    scrollarea->setWidget(subwindow);
    main_layout->addWidget(scrollarea);
    main_layout->addLayout(results_layout);
    */
    QWidget *subwindow = new QWidget();
    QScrollArea *scrollarea = new QScrollArea(this);
    scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollarea->setWidgetResizable( true );
    scrollarea->setWidget(subwindow);

    main_layout->addLayout(top_layout);
    main_layout->addWidget(scrollarea);
    QWidget *window = new QWidget();
    window->setLayout(main_layout);
    setCentralWidget(window); //setting layout for main window






//FUNCTIONS

    connect(upload_file, &QAbstractButton::clicked, this, &MainWindow::find_file);

    connect(confirm, &QAbstractButton::clicked, this, &MainWindow::enter_equation);

    connect(enter, &QShortcut::activated, this, &MainWindow::enter_equation);
        
    connect(info, &QAbstractButton::clicked, this, &MainWindow::display_info);

}


//GROUPS FOR TOP LAYOUT

QGroupBox *MainWindow::title_group(){

    QGroupBox *title_group = new QGroupBox();

    QLabel* window_title = new QLabel;

    window_title->setText("Welcome to the Handwritten Math Solver");
    window_title->setAlignment(Qt::AlignHCenter);
    window_title->setStyleSheet("border:none");
    QFont window_title_font("Times New Roman", 40, QFont::Bold);
    window_title->setFont(window_title_font);

    QLabel* sub_title = new QLabel;
    sub_title->setText(" developed by students of BX22");
    sub_title->setStyleSheet("border:none");
    
    info = new QPushButton(this);
    info->setText("?");
    info->setFixedSize(30,30);
    QFont infofont("Arial", 20);
    info->setFont(infofont);
    info->setStyleSheet("border: 1px solid black; border-radius: 15px; border-style: outset; background-color: rgb(237, 237, 237)");

    QHBoxLayout *title_layout = new QHBoxLayout;
    title_layout->addWidget(window_title);
    title_layout->addWidget(sub_title);
    title_layout->addWidget(info);
    //title_layout->addStretch();
    title_group->setStyleSheet("background-color: white; border:1px solid grey");
    title_group->setAlignment(Qt::AlignCenter);
    title_group->setLayout(title_layout);

    return title_group;
}


QGroupBox *MainWindow::manual_input_group(){

    QGroupBox *manual_input_group = new QGroupBox();


    QFont input_font("Arial", 20);

    QLabel* user_prompt1 = new QLabel(this);
    user_prompt1->setText("Manually input your equation:");
    user_prompt1->setFont(input_font);

    QHBoxLayout *input_layout = new QHBoxLayout;
    input_layout->addWidget(user_prompt1);
    input_layout->addWidget(equation_input);
    input_layout->addWidget(confirm);
    //input_layout->addStretch();
    manual_input_group->setLayout(input_layout);

    return manual_input_group;
}


QGroupBox *MainWindow::upload_group(){

    QGroupBox *upload_group = new QGroupBox();

    QFont input_font("Arial", 20);

    QLabel* info = new QLabel(this);
    info->setText("OR choose a picture of the equation you wish to solve:");
    info->setFont(input_font);

    QHBoxLayout *upload_layout = new QHBoxLayout;
    upload_layout->addWidget(info);
    upload_layout->addWidget(upload_file);
    upload_group->setLayout(upload_layout);

    return upload_group;
}



QWidget *MainWindow::steps_layoutf(vector<string> res){

    QVBoxLayout* steps_layout = new QVBoxLayout;
    QFont stepfont("Arial", 18);
    QList<int> arr;
    for (int j = 1; j<1000; j++){
        arr.append(j);
    } // creating list for number of step

    size_t k = 0;

    while (res[k] != "r"){

        QLabel* number_step = new QLabel;
        QString number = QString::number(arr[k]);
        QString s = "Step "+number+":";
        number_step->setText(s);
        number_step->setFont(stepfont);

        QLabel* step = new QLabel;
        QString a = QString::fromStdString(res[k]);
        step->setText(a);
        step->setFont(stepfont);

        QGroupBox* g = new QGroupBox;
        g->setStyleSheet("background-color: white; border:none");
        QHBoxLayout *g_layout = new QHBoxLayout;
        g_layout->addWidget(number_step, 1);
        g_layout->addWidget(step, 4);
        g->setLayout(g_layout);

        steps_layout->addWidget(g);

        k += 1;
    }

    //Setting scrollable box for steps
    QWidget *subwindow = new QWidget();
    subwindow ->setLayout(steps_layout);
    QScrollArea *scrollarea = new QScrollArea(this);
    scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollarea->setWidgetResizable( true );
    scrollarea->setWidget(subwindow);

    return scrollarea;
}


QGroupBox *MainWindow::results_layoutf(vector<string> res){

    QGroupBox* results = new QGroupBox;
    QVBoxLayout* final_result_layout = new QVBoxLayout;
    QFont f2("Arial", 20);

    size_t k = 0;
    while (res[k] != "r"){
        k += 1;
    }

    size_t i = k+1;
    while (i < (res.size())){

        if (QString::fromStdString(res[i]) == ":"){
            i += 1; //skipping ':'

            QHBoxLayout* sub_results = new QHBoxLayout;

            while (res[i] != "n" && i < res.size()){
                QLabel* sub_res = new QLabel;
                sub_res -> setText(QString::fromStdString(res[i]));
                sub_res -> setFont(f2);
                sub_res -> setStyleSheet("border: none; font-weight: bold");
                sub_results->addWidget(sub_res);

                i += 1;
            }
            final_result_layout->addLayout(sub_results);
            i += 1; // skipping 'n'
        }
        if (i < res.size()){
            QLabel* part_res = new QLabel;
            part_res->setText(QString::fromStdString(res[i]));
            part_res->setFont(f2);
            part_res->setStyleSheet("border: none; text-decoration: underline");
            final_result_layout->addWidget(part_res);
        }
        i += 1;
    }
    results->setLayout(final_result_layout);
    results->setStyleSheet("background-color: rgb(216, 242, 196); border:1px solid grey");
    return results;
}

void MainWindow::display_info(){
    QMessageBox *infobox = new QMessageBox;
    infobox->setText("How to use the Mathsolver");
    infobox->setInformativeText("! Please only use x as variable !\nUsual functions that can be used: exp(x), ln(x), log(x), sin(x), cos(x), tan(x), sqrt(x)\n\n"
    "To find the derivative of a function: (f(x))'\nexample: (x^2 + 5x + exp(x^3))'\n\n"
    "To get the value of the integral of a function: int{a}{b}{f(x)}\nexample: int{0}{1}{exp(x)}\nmeans integral from 2 to 5 of exp(x)\n\n"
    "To find the root at point a of a function f(x) = a\nexample: x^3 - 2x^2 - x + 2 = 0\n\n"
    "To solve a system of equations: sys{your system}\nexample: sys{2 ; 5 ;  2  = -38 | 3 ; -2; 4 = 17 | -6; 1; -7 = -12 }\n"
    "means solving the following system of equations:\n2x0 + 5x1 + 2x2 = -38\n3x0 - 5x1 + 4x2 = 17\n-6x0 + x1 - 7x2 = -12\n*each coefficient should be separated by ';' and a new equation is obtained by entering '|'\n\n"
    "To get the inverse of a matrix: inv{matrix}\nexample: inv{-5; 3; 1 | 4; -1; 5 | 2; -2; 3}\n*each coefficient should be separated by ';' and a new row is obtained by entering '|'\n\n"
    "To get the determinant of a matrix: det{matrix}\nexample: det{-5; 3; 1 | 4; -1; 5 | 2; -2; 3}\n*each coefficient should be separated by ';' and a new row is obtained by entering '|'\n\n"
    "To get the product of matrices: mult{matrix1}{matrix2}\nexample: mult{8; 2}{3 | 4}\n*each coefficient should be separated by ';' and a new row is obtained by entering '|'\n\n"
    "To divide two polynomials: (polynomial1) : (polynomial2)\nexample: (x^3 - 2x^2 - x + 2) : (x^2 - 1)\n\n"
    "To multiply two polynomials: (polynomial1) * (polynomial2)\nexample: (x^3 - 2x^2 - x + 2) * (x^2 - 1)\nmeans integral from 2 to 5 of exp(x)");
    infobox->setStyleSheet("QLabel{min-width: 700px; font-size: 14px}");
    infobox->exec();
}


//FUNCTION TO RETURN FILE PATH IN STRING FORMAT

void MainWindow::find_file(){

    QFileDialog dialog;
    dialog.setFileMode(QFileDialog:: AnyFile);
    dialog.exec();
    QStringList paths = dialog.selectedFiles();

    for (int i=0 ; i < paths.length() ; i++) //no need for several files to be uploaded, but iteration was only way I found to have the full path printed to the console
    {
         QString s = paths.at(i);
         string prediction = makePredictionQ(s);
         QString eq = QString::fromStdString(prediction);
         equation_input->setText(eq);
    }
}



//FUNCTION TO HAVE INPUTTED EQUATION AS STRING --> ALGORITHMS (start_process) --> DISPLAY STEPS AND RESULT

void MainWindow::enter_equation(){

    // Equation as input to function

    QString equation = equation_input->text();

    if (!equation.isEmpty()) {

        string f = equation.toStdString();
        vector<string> res = start_process(f);

        if (res[0] == "i"){
            QMessageBox *invalid = new QMessageBox;
            invalid->setText("Invalid input, please change the expression.");
            invalid->exec();
        }
        else {
            // Reinitializing window
            QLayoutItem *item;
            while ((item = main_layout->takeAt(1)) != 0){
                delete item->widget();
                delete item;
            }

            QHBoxLayout* final = new QHBoxLayout;
            final->addWidget(steps_layoutf(res), 4);
            final->addWidget(results_layoutf(res), 1, Qt::AlignHCenter);

            QGroupBox* ff = new QGroupBox;
            ff->setLayout(final);
            main_layout->addWidget(ff);
        }
    }
    else {
        equation_input-> setPlaceholderText("Please enter something here");
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
