#ifndef SPLENDORDUEL_H
#define SPLENDORDUEL_H

#include <QtWidgets/QMainWindow>
#include "ui_SplendorDuel.h"
#include <iostream>

#include "Bag.h"
#include "Board.h"

class SplendorDuel : public QMainWindow
{
    Q_OBJECT

public:
    SplendorDuel(Bag& bag, Board& board, QWidget* parent = nullptr);
    ~SplendorDuel();


    bool close();

private:
    Ui::SplendorDuelClass ui;
    Bag& bag;
    Board& board;
};

#endif