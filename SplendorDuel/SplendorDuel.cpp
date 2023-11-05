#include "SplendorDuel.h"

#include "GameHandler.h"

#include <iostream>
using namespace std;


SplendorDuel::SplendorDuel(Bag& bag, Board& board, DrawPile** drawPiles, QWidget *parent)
    : gameHandler(bag, board, drawPiles),
    QMainWindow(parent)
{ 

}

SplendorDuel::~SplendorDuel()
{
    
}

void SplendorDuel::start() {
    while (!gameHandler.gameFinished()) {
        gameHandler.nextAction();
    }
}

bool SplendorDuel::close(){
    QMainWindow::close();
    return true;
}