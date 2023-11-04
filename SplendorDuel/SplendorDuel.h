#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SplendorDuel.h"
#include <iostream>

#include "Bag.h"
#include "Board.h"
#include "DrawPile.h"

class SplendorDuel : public QMainWindow
{
    Q_OBJECT

public:
    SplendorDuel(Bag& bag, Board& board, DrawPile** drawPiles, QWidget* parent = nullptr);
    ~SplendorDuel();


    bool close();

private:
    Ui::SplendorDuelClass ui;
    Bag& bag;
    Board& board;
    DrawPile** drawPiles;
};