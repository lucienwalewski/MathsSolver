#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

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

//1. Title
    QLabel *title0;
    QLabel *title1;
    QGroupBox *group_0();
//2. Manual input
    QLabel * question;
    QLineEdit * equation_input;
    QPushButton* enter;
    QGroupBox *first_group();
//3. Upload file
    QLabel* info;
    QPushButton* upload_file;
    QGroupBox *second_group();
//4. Steps
    QLabel* label1;
    QLabel* label2;
    QLabel* label3;
    QLabel* step1;
    QLabel* step2;
    QLabel* step3;
    QGroupBox *group_step1();
    QGroupBox *group_step2();
    QGroupBox *group_step3();
//5. Final Result
    QLabel* output;
    QLabel* result;
    QGroupBox *group_result();
//6. Main Layout
    QVBoxLayout* main_layout;
};
#endif // MAINWINDOW_H

