#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <iostream>
#include <QDebug>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

//TITLE

    title0 = new QLabel(this);
    title0->setText("Welcome to the Handwritten Math Solver");
    QFont f("Times New Roman", 20, QFont::Bold);
    title0->setFont(f);
    title0->setAlignment(Qt::AlignHCenter);

    title1 = new QLabel(this);
    title1->setText("developed by students of BX22");


//UPLOAD FILE BUTTON

    info = new QLabel(this);
    info->setText("OR choose a picture of the equation you wish to solve:");


    upload_file = new QPushButton(this);
    upload_file->setText("Upload file");


//MANUALLY INPUT EQUATION BUTTON

    question = new QLabel(this);
    question->setText("Manually input your equation:");
    question->show();

    equation_input = new QLineEdit(this);
    equation_input-> setPlaceholderText("here");

    enter = new QPushButton(this);
    enter->setText("Confirm");


//FUNCTIONS

    connect(upload_file, &QAbstractButton::clicked, this, &MainWindow::find_file);
    connect(enter, &QAbstractButton::clicked, this, &MainWindow::enter_equation);


//LAYOUT
    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addWidget(group_0());
    main_layout->addWidget(first_group());
    main_layout->addWidget(second_group());
    main_layout->addStretch();
    QWidget *window = new QWidget(); //setting layout
    window->setLayout(main_layout);
    setCentralWidget(window); //setting layout for main window
}


MainWindow::~MainWindow()
{
    delete ui;
}

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

void MainWindow::enter_equation(){
    QString equation = equation_input->text();
    if (!equation.isEmpty()) {
        std::cout<<equation.toStdString()<<std::endl;
    } else {
        // do nothing
    }
}

