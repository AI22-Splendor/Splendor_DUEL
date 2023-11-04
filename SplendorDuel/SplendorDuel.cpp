#include "SplendorDuel.h"

#include "Bag.h"
#include "Board.h"

#include <iostream>
using namespace std;


SplendorDuel::SplendorDuel(Bag& bag, Board& board, DrawPile** drawPiles, QWidget *parent)
    : bag(bag), board(board), drawPiles(drawPiles),
    QMainWindow(parent)
{ 

}

SplendorDuel::~SplendorDuel()
{
    
}

bool SplendorDuel::close(){
    QMainWindow::close();
    return true;
}