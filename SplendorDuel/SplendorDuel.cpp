#include "SplendorDuel.h"

#include "BoardUI.h"

#include "GameHandler.h"
#include <qgridlayout.h>
#include <iostream>
#include <qevent.h>
#include "PlayerGemsUI.h"

using namespace std;
SplendorDuel* SplendorDuel::instance = nullptr;

SplendorDuel::SplendorDuel(Bag& bag, Board& b, DrawPile** drawPiles, Player p1, Player p2):
    QMainWindow(nullptr)
{
    setWindowTitle("SplendorDuel");
    //on instance notre GameHandler
    GameHandler::Instanciate(bag, b, drawPiles, p1, p2);

    //mise en page avec le widget main
    QWidget* main = new QWidget(this);
    QGridLayout* vl=new QGridLayout(main);
    main->setLayout(vl);

    this->ptab = new PlayersUI*[2]();
    ptab[0] = new PlayersUI(main, QString(p1.getName().c_str()), 1);
    ptab[1] = new PlayersUI(main, QString(p2.getName().c_str()), 2);

    this->board = new CompleteBoardUI(main, b);
    

    vl->addWidget(ptab[0],0, 0);
    vl->addWidget(board, 1, 0);
    vl->addWidget(ptab[1], 2, 0);

    vl->setColumnStretch(0, 1);
    vl->setRowStretch(1, 9);
    vl->setRowStretch(2, 3);
    vl->setRowStretch(0, 3);
    //on supprime les espace par défault
    vl->setSpacing(0);
    vl->setContentsMargins(0, 0, 0, 0);
    this->setCentralWidget(main);
}

SplendorDuel::~SplendorDuel()
{
    delete instance->board;
    delete[] instance->ptab;
    delete SplendorDuel::instance;
}

void SplendorDuel::start() {
    while (!GameHandler::getInstance().gameFinished()) {
        GameHandler::getInstance().nextAction();
    }
}

bool SplendorDuel::close(){
    instance->QMainWindow::close();
    return true;
}

void SplendorDuel::keyPressEvent(QKeyEvent* e) { 
    if (e->key() == Qt::Key_N && e->type()==QEvent::KeyPress && e->isAutoRepeat()== false){
        instance->board->changeDirection();
    }
};
