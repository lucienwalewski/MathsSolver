#include "mainwindow.h"
#include "ui_mainwindow.h"
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

 label1 = new QLabel(this);
 label1->setText("Step 1:");
 step1 = new QLabel(this);
 step1->setText("first do this");

 label2 = new QLabel(this);
 label2->setText("Step 2:");
 step2 = new QLabel(this);
 step2->setText("then do this");

 label3 = new QLabel(this);
 label3->setText("Step 3:");
 step3 = new QLabel(this);
 step3->setText("then do this");

 label1->setVisible(false);
 step1->setVisible(false);
 label2->setVisible(false);
 step2->setVisible(false);
 label3->setVisible(false);
 step3->setVisible(false);


//FINAL RESULT
 output = new QLabel(this);
 output->setText("The final result to your equation is:");
 result = new QLabel(this);
 result->setText("result");

 //output->setVisible(false);
 //result->setVisible(false);




//LAYOUT

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(group_0());
    main_layout->addWidget(first_group());
    main_layout->addWidget(second_group());
    main_layout->addWidget(group_step1());
    main_layout->addWidget(group_step2());
    main_layout->addWidget(group_step3());
    main_layout->addWidget(group_result());
    main_layout->addStretch();

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


QGroupBox *MainWindow::group_step1(){

    QGroupBox *gs1 = new QGroupBox();
    //gs1->setVisible(false);
    gs1->setStyleSheet("background-color: white; border:none");

    //label1->setVisible(true);
    //step1->setVisible(true);

    QHBoxLayout *gs1_layout = new QHBoxLayout;
    gs1_layout->addWidget(label1);
    gs1_layout->addWidget(step1);
    gs1->setLayout(gs1_layout);

    return gs1;
}

QGroupBox *MainWindow::group_step2(){

    QGroupBox *gs2 = new QGroupBox();
    //gs2->setVisible(false);
    gs2->setStyleSheet("background-color: white; border:none");

    //label2->setVisible(true);
    //step2->setVisible(true);

    QHBoxLayout *gs2_layout = new QHBoxLayout;
    gs2_layout->addWidget(label2);
    gs2_layout->addWidget(step2);
    gs2->setLayout(gs2_layout);

    return gs2;
}

QGroupBox *MainWindow::group_step3(){

    QGroupBox *gs3 = new QGroupBox();
    //gs3->setVisible(false);
    gs3->setStyleSheet("background-color: white; border:none");

    //label3->setVisible(true);
    //step3->setVisible(true);

    QHBoxLayout *gs3_layout = new QHBoxLayout;
    gs3_layout->addWidget(label3);
    gs3_layout->addWidget(step3);
    gs3->setLayout(gs3_layout);

    return gs3;
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

    QString equation = equation_input->text();

    if (!equation.isEmpty()) {
        //std::cout<<equation.toStdString()<<std::endl;
        string f = equation.toStdString();
        vector<string> reslut = start_process(f);
    } else {
        // do nothing
    }
    //if step1 != empty
    label1->setVisible(true);
    step1->setVisible(true);

    //if step2 != empty
    label2->setVisible(true);
    step2->setVisible(true);

    //if step3 != empty
    label3->setVisible(true);
    step3->setVisible(true);
}


// for k in (1,max_steps)
    //if step(k) not empty -> display step(k)
// display result

MainWindow::~MainWindow()
{
    delete ui;
}
