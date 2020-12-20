#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "inputbox.h"
#include <QFileDialog>
#include <QGroupBox>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void find_file();
    void enter_equation();

private:
    Ui::MainWindow *ui;
    QLabel *title0;
    QLabel *title1;
    QGroupBox *group_0();
    QGroupBox *first_group();
    QGroupBox *second_group();
    QLabel* info;
    QPushButton* upload_file;
    QPushButton* enter;
//InputBox input_box;
    QLabel * question;
    QLineEdit * equation_input;
    QFileDialog * input_file;
};
#endif // MAINWINDOW_H
