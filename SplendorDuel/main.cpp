#include "GameFactory.h"
#include "SplendorDuel.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
 


    // Before is testing code
    QApplication a(argc, argv);
   
    SplendorDuel& w = GameFactory::buildNewSplendor();
    QPushButton b("Quitter", &w);
    QObject::connect(&b, &QPushButton::clicked, &w, &SplendorDuel::close);
    
    w.show();
    return a.exec();
}