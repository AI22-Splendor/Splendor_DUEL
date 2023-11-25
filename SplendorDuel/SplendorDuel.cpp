#include "SplendorDuel.h"

#include "BoardUI.h"

#include "GameHandler.h"
#include <qgridlayout.h>
#include <iostream>
#include <qevent.h>
#include "PlayerGemsUI.h"
using namespace std;


SplendorDuel::SplendorDuel(Bag& bag, Board& b, DrawPile** drawPiles, Player& player1, Player& player2, QWidget *parent):
    QMainWindow(parent)
{
    setWindowTitle("SplendorDuel");
    GameHandler::Instanciate(bag, b, drawPiles, player1, player2);
    QWidget* main = new QWidget(this);
    QVBoxLayout* vl=new QVBoxLayout(main);
    main->setLayout(vl);

    ptab = new PlayersUI*[2]();
    for (int i = 0; i < 2; i++) {
        ptab[i] = new PlayersUI(this, i + 1);
    }
    this->board = new CompleteBoardUI(this, b);
    
    QWidget* w = new QWidget(main);

    vl->addWidget(ptab[0], Qt::AlignBottom);
    vl->addWidget(board, Qt::AlignCenter | Qt::AlignHCenter);
    vl->addWidget(ptab[1], Qt::AlignBottom);

    vl->setSpacing(0);
    vl->setContentsMargins(0, 0, 0, 0);

    vl->setStretch(0, 2);
    vl->setStretch(1, 10);
    vl->setStretch(2, 2);
    setCentralWidget(main);
    //setCentralWidget(board);
}

SplendorDuel::~SplendorDuel()
{
    delete board;
    delete[] ptab;
}

void SplendorDuel::start() {
    while (!GameHandler::getInstance().gameFinished()) {
        GameHandler::getInstance().nextAction();
    }
}

bool SplendorDuel::close(){
    QMainWindow::close();
    return true;
}

void SplendorDuel::keyPressEvent(QKeyEvent* e) { 
    if (e->key() == Qt::Key_N && e->type()==QEvent::KeyPress && e->isAutoRepeat()== false){
        board->changeDirection();
    }
};
