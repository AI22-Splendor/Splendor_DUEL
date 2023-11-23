#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SplendorDuel.h"
#include "BoardUI.h"
#include "GameHandler.h"

class SplendorDuel : public QMainWindow
{
    Q_OBJECT

public:
    SplendorDuel(Bag& bag, Board& board, DrawPile** drawPiles, QWidget* parent = nullptr);
    ~SplendorDuel();

    void keyPressEvent(QKeyEvent* e);
    void start();

    bool close();

private:
    BoardUI* board;
    Ui::SplendorDuelClass ui;
};