#include "GameFactory.h"
#include "SplendorDuel.h"
#include <QtWidgets/QApplication>
#include "GameHandler.h"
#include "GemmesUI.h"
#include "Image.h"

int main(int argc, char *argv[])
{

    // Before is testing code
    QApplication a(argc, argv);
   
    SplendorDuel& game = GameFactory::buildNewSplendor();
    game.show();
    // game.start();
    return a.exec();
}