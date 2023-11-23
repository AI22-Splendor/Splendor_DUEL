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
    QWidget* w = new QWidget();
    QGridLayout* grid = new QGridLayout(w);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setSpacing(0);

    board = new BoardUI(w);
    GameHandler::Instanciate(bag, b, drawPiles);
    board->setGemmes(b);
    //on y ajoute tous les composant
    
    grid->addWidget(board, 1, 1);
    setCentralWidget(w);
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
