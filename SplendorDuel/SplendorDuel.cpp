#include "SplendorDuel.h"

#include "BoardUI.h"

#include "GameHandler.h"

#include <iostream>
#include <qevent.h>
using namespace std;


SplendorDuel::SplendorDuel(Bag& bag, Board& b, DrawPile** drawPiles, QWidget *parent):
    QMainWindow(parent)
{
    
    setWindowTitle("SplendorDuel");
    board = new BoardUI(this);
    GameHandler::Instanciate(bag, b, drawPiles, board);
    board->setGemmes(b);
    
    
    setCentralWidget(board);
}

SplendorDuel::~SplendorDuel()
{
    
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
