#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SplendorDuel.h"
#include "GameHandler.h"
#include "GemmesContainerGUI.h"
#include "CompleteBoardUI.h"
#include "PlayersUI.h"
#include "Player.h"

class SplendorDuel : public QMainWindow
{
    Q_OBJECT

public:
    SplendorDuel(Bag& bag, Board& board, DrawPile** drawPiles, Player& player1, Player& player2, QWidget* parent = nullptr);
    ~SplendorDuel();

    void keyPressEvent(QKeyEvent* e);
    inline void addPlayerGems(const Gemmes g, const int p)const { 
        ptab[p]->gemsAdd(g); 
    }
    void start();
    bool close();

private:
    CompleteBoardUI* board;
    PlayersUI** ptab;
    Ui::SplendorDuelClass ui;
};