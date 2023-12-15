#pragma once

#include <iostream>
#include "AI.h"
#include "SplendorDuel.h"
#include "GameHandler.h"
#include <random>

using namespace std;

void AI::play(){
    //Achats Cartes
    CardUI*** cards = SplendorDuel::getInstance().boardcards->cards;
    Card* card;
    GemmesUI* g;
    bool isWorked;
    for (int i = 0; i < 3;i++) {
        for (int j = 0; j < (3 + i);j++) {
            card = cards[i][j]->cardList[0];
            if ((this->canBuyCard(*card))==true){
                SplendorDuel::getInstance().boardcards->clickCard(j,i,card);
                return;
            }
        }
    }

    //Recolter pieces
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int k=0; k<3; k++){
        cout<<k<<"\n";
        for (int j=0; j<3; j++){
            for (int i = 0; i < 10; i++) {
                std::uniform_int_distribution<> dis(0, 24);
                int pos = dis(gen);
                BoardUI* b = &SplendorDuel::getInstance().board->board;
                g = b->tabCase[pos/5][pos%5];
                isWorked=false;
                if (g->gem != EnumGemmes::Vide){
                    ((GemmesContainerGUI*)g->parentWidget())->hoverGemmes(pos,true);
                    isWorked=((GemmesContainerGUI*)g->parentWidget())->clickGemmes(g->gem);
                    ((GemmesContainerGUI*)g->parentWidget())->hoverGemmes(pos,false);
                    if (isWorked==true){
                        return;
                    }
                }
            }
            SplendorDuel::getInstance().board->changeDirection();
        }
        SplendorDuel::getInstance().board->changeNbGemmesTOSelect();
    }
    cout<<"Hello\n";
    SplendorDuel::getInstance().board->remplirBoard(SingletonGameHandler::getInstance().remplirBoard());
	SplendorDuel::refreshPrivilege();

    for (int i = 0; i < 25; i++) {
                BoardUI* b = &SplendorDuel::getInstance().board->board;
                g = b->tabCase[i/5][i%5];
                isWorked=false;
                if (g->gem != EnumGemmes::Vide){
                    ((GemmesContainerGUI*)g->parentWidget())->hoverGemmes(i,true);
                    isWorked=((GemmesContainerGUI*)g->parentWidget())->clickGemmes(g->gem);
                    ((GemmesContainerGUI*)g->parentWidget())->hoverGemmes(i,false);
                    if (isWorked==true){
                        return;
                    }
                }
    }
}