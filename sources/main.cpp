#include "MainWindow/mainwindow.h"

using namespace std;

int main(int argc, char *argv[]){
  
    QApplication  a(argc, argv);

     MainWindow w;
     w.setWindowState(Qt::WindowMaximized);
     w.setWindowTitle("MathsSolver");
     w.show();


     return a.exec();
}
