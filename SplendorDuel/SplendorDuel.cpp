#include "SplendorDuel.h"

#include "BoardUI.h"

#include "GameHandler.h"
#include <qgridlayout.h>
#include <iostream>
#include <qevent.h>
using namespace std;


SplendorDuel::SplendorDuel(Bag& bag, Board& b, DrawPile** drawPiles, QWidget *parent):
    QMainWindow(parent)
{
    setWindowTitle("SplendorDuel");
    GameHandler::Instanciate(bag, b, drawPiles);
    QWidget* main = new QWidget(this);
    QVBoxLayout* vl=new QVBoxLayout(main);
    main->setLayout(vl);

    
    this->board = new CompleteBoardUI(this, b);
    /*
    QWidget* w = new QWidget(main);

    vl->addWidget(new RemplirBoard(this), Qt::AlignCenter | Qt::AlignHCenter);
    vl->addWidget(board, Qt::AlignCenter | Qt::AlignHCenter);
    vl->addWidget(new RemplirBoard(this), Qt::AlignCenter | Qt::AlignHCenter);

    vl->setSpacing(0);
    vl->setContentsMargins(0, 0, 0, 0);

    vl->setStretch(0, 2);
    vl->setStretch(1, 10);
    vl->setStretch(2, 2);
    setCentralWidget(main);*/
    setCentralWidget(board);
}

SplendorDuel::~SplendorDuel()
{
    delete board;
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
