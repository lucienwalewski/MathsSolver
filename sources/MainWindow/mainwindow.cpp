#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Equations/polynomial.hpp"
#include "functionPreprocessing.hpp"
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



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

//TITLES

    title0 = new QLabel(this);
    title0->setText("Welcome to the Handwritten Math Solver");
    QFont f("Times New Roman", 20, QFont::Bold);
    title0->setFont(f);
    title0->setAlignment(Qt::AlignHCenter);

    title1 = new QLabel(this);
    title1->setText("developed by students of BX22");


//MANUALLY INPUT EQUATION BUTTON

    question = new QLabel(this);
    question->setText("Manually input your equation:");
    question->show();

    equation_input = new QLineEdit(this);
    equation_input-> setPlaceholderText("here");

    enter = new QPushButton(this);
    enter->setText("Confirm");


//UPLOAD FILE BUTTON

    info = new QLabel(this);
    info->setText("OR choose a picture of the equation you wish to solve:");

    upload_file = new QPushButton(this);
    upload_file->setText("Upload file");


//STEPS
/*
 label1 = new QLabel(this);
 label1->setText("Step 1:");
 step1 = new QTextEdit(this);
 step1->setText("first do this");
 gs1 = new QGroupBox(this);

 label2 = new QLabel(this);
 label2->setText("Step 2:");
 step2 = new QTextEdit(this);
 step2->setText("then do this");
 gs2 = new QGroupBox(this);

 label3 = new QLabel(this);
 label3->setText("Step 3:");
 step3 = new QTextEdit(this);
 step3->setText("then do this");
 gs3 = new QGroupBox(this);


//FINAL RESULT
 output = new QLabel(this);
 output->setText("The final result to your equation is:");
 result = new QLabel(this);
 result->setText("result");

*/




//LAYOUT

    main_layout = new QVBoxLayout(this);
    top_layout = new QVBoxLayout(this);
    steps_layout = new QVBoxLayout(this);
    results_layout = new QHBoxLayout(this);

    top_layout->addWidget(group_0());
    top_layout->addWidget(first_group());
    top_layout->addWidget(second_group());
    //top_layout->addStretch();



    QWidget *subwindow = new QWidget();
    subwindow ->setLayout(steps_layout);

    QScrollArea *scrollarea = new QScrollArea(this);
    scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollarea->setWidgetResizable( true );
    scrollarea->setWidget(subwindow);

    main_layout->addLayout(top_layout);
    main_layout->addWidget(scrollarea);
    main_layout->addLayout(results_layout);


    QWidget *window = new QWidget(); //setting layout
    window->setLayout(main_layout);
    setCentralWidget(window); //setting layout for main window




//FUNCTIONS

    connect(upload_file, &QAbstractButton::clicked, this, &MainWindow::find_file);

    connect(enter, &QAbstractButton::clicked, this, &MainWindow::enter_equation);



}

//DEFINITIONS FOR LAYOUT


QGroupBox *MainWindow::group_0(){

    QGroupBox *group0 = new QGroupBox();

    QHBoxLayout *title_layout = new QHBoxLayout;
    title_layout->addWidget(title0);
    title_layout->addWidget(title1);
    title_layout->addStretch();
    title_layout->setAlignment(Qt::AlignCenter);
    group0->setLayout(title_layout);

    return group0;
}


QGroupBox *MainWindow::first_group(){

    QGroupBox *group1 = new QGroupBox();

    QHBoxLayout *input_layout = new QHBoxLayout;
    input_layout->addWidget(question);
    input_layout->addWidget(equation_input);
    input_layout->addWidget(enter);
    input_layout->addStretch();
    group1->setLayout(input_layout);

    return group1;
}


QGroupBox *MainWindow::second_group(){

    QGroupBox *group2 = new QGroupBox();

    QHBoxLayout *upload_layout = new QHBoxLayout;
    upload_layout->addWidget(info);
    upload_layout->addWidget(upload_file);
    group2->setLayout(upload_layout);

    return group2;
}




QGroupBox *MainWindow::group_result(){

    QGroupBox *gr = new QGroupBox();
    //gr->setVisible(false);
    gr->setStyleSheet("background-color: rgb(216, 242, 196); border:none");

    //output->setVisible(true);
    //result->setVisible(true);

    QHBoxLayout *gr_layout = new QHBoxLayout;
    gr_layout->addWidget(output);
    gr_layout->addWidget(result);
    gr->setLayout(gr_layout);

    return gr;
}

//FUNCTION TO RETURN FILE PATH IN STRING FORMAT

void MainWindow::find_file(){

    QFileDialog dialog;
    dialog.setFileMode(QFileDialog:: AnyFile);
    dialog.exec();
    QStringList paths = dialog.selectedFiles();

    for (int i=0 ; i < paths.length() ; i++) //no need for several files to be uploaded, but iteration was only way I found to have the full path printed to the console
    {
         std::cout<<paths.at(i).toStdString().c_str()<<std::endl;
    }


}


//FUNCTION TO RETURN INPUTTED EQUATION IN STRING FORMAT

void MainWindow::enter_equation(){

    // Equation as input to function
    QString equation = equation_input->text();
    if (!equation.isEmpty()) {
        string f = equation.toStdString();
        vector<string> res = start_process(f);

        QList<int> arr;
        for (int j = 1; j<1000; j++){
            arr.append(j);
        }

        size_t k = 0;
        while (res[k] != "r"){
            QLabel* number_step = new QLabel;
            QString number = QString::number(arr[k]);
            QString s = "Step "+number;
            number_step->setText(s);

            QLabel* step = new QLabel;
            QString a = QString::fromStdString(res[k]);
            step->setText(a);

            QGroupBox* g = new QGroupBox;
            g->setStyleSheet("background-color: white; border:none");
            QHBoxLayout *g_layout = new QHBoxLayout;
            g_layout->addWidget(number_step);
            g_layout->addWidget(step);
            g->setLayout(g_layout);

            steps_layout->addWidget(g);

            k += 1;
        }

        QLabel* infosol = new QLabel;
        infosol->setText("The solution to your equation is");
        results_layout->addWidget(infosol);


        QGroupBox *gres = new QGroupBox();
        gres->setStyleSheet("background-color: rgb(216, 242, 196); border:none");

        QHBoxLayout *gres_layout = new QHBoxLayout;
        QVBoxLayout* sub_results = new QVBoxLayout;
        for (size_t i=k+1 ; i < (res.size()) ; i++){
            QLabel* part_res = new QLabel;
            QString r2 = QString::fromStdString(res[i]);
            part_res->setText(r2);
            sub_results->addWidget(part_res);
        gres_layout->addLayout(sub_results);
        gres->setLayout(gres_layout);
        results_layout->addWidget(gres);
        }







/*
        for (size_t k=0 ; k < (result.size()) ; k++){
            QLabel* number_step = new QLabel;
            QString s = "Step";
            s += k;
            number_step->setText(s);

            QLabel* step = new QLabel;
            step->setText(QString::fromStdString(result[k]));

            QGroupBox* g = new QGroupBox;
            g->setStyleSheet("background-color: white; border:none");
            QHBoxLayout *g_layout = new QHBoxLayout;
            g_layout->addWidget(number_step);
            g_layout->addWidget(step);
            g->setLayout(g_layout);

            main_layout->addWidget(g);
        }
*/
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}


//k = 0
//for i in res.step_solution()
    //stepk.settext(i)

