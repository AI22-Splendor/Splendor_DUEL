#include "SplendorDuel.h"

#include "BoardUI.h"

#include "GameHandler.h"
#include <qgridlayout.h>
#include <iostream>
#include <qevent.h>
#include "PlayerGemsUI.h"


using namespace std;
SplendorDuel* SplendorDuel::instance = nullptr;

SplendorDuel::SplendorDuel(Bag& bag, Board& b, DrawPile** drawPiles):
    QMainWindow(nullptr)
{
    setWindowTitle("SplendorDuel");
    //on instance notre GameHandler
    GameHandler::Instanciate(bag, b, drawPiles);

    //mise en page avec le widget main
    QWidget* main = new QWidget(this);
    QVBoxLayout* vl=new QVBoxLayout(main);
    main->setLayout(vl);

    this->ptab = new PlayersUI*[2]();
    for (int i = 0; i < 2; i++) {
        ptab[i] = new PlayersUI(this, i + 1);
    }
    this->board = new CompleteBoardUI(this, b);
    
    QWidget* w = new QWidget(main);

    vl->addWidget(ptab[0], 2, Qt::AlignBottom);
    vl->addWidget(board, 10, Qt::AlignCenter);
    vl->addWidget(ptab[1], 2, Qt::AlignBottom);

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
