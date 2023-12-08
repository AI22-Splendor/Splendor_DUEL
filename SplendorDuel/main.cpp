#include "GameFactory.h"
#include "SplendorDuel.h"
#include <QtWidgets/QApplication>
#include "GameHandler.h"
#include "GemmesUI.h"
#include "Image.h"
#include "MenuUI.h"

int main(int argc, char *argv[])
{

    // Before is testing code
    QApplication a(argc, argv);
    MenuUI* menu = new MenuUI();
    menu->show();
    if (menu->exec() != MenuUI::Accepted)
        return 0;
    XmlReader::setLanguage(menu->getLanguage());
    SplendorDuel& game = GameFactory::buildNewSplendor(menu->IA(), menu->getP1name(), menu->getP2name());
    game.show();
    //game.start();
    return a.exec();
}