#include "SplendorDuel.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    SplendorDuel w;
    QPushButton b("Quitter", &w);
    QObject::connect(&b, &QPushButton::clicked, &w, &SplendorDuel::close);
    
    w.show();
    return a.exec();
}