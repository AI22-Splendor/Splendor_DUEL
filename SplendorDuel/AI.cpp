#include "AI.h"
#include "CardUI.h"
#include "SplendorDuel.h"
#include "GameHandler.h"
#include "PrivilegeHandler.h"
#include "Rules.h"
void AI::play() {
    if (isplaying)
        return;
    isplaying = true;
    SplendorDuel::getInstance().board->remplir.hover = true;
    SplendorDuel::getInstance().board->remplir.mousePressEvent(nullptr);
    SplendorDuel::getInstance().board->remplir.hover = false;

    //LES PRIVILEGES
    while (SingletonPrivilegeHandler::getInstance()->playerHasPrivilege(*this)) {
        SplendorDuel::getInstance().privilege->tab[1][0]->mousePressEvent(nullptr);
    }

    //LES NOBLES
    for (int i = 0; i < 2; i++) {
        if (SplendorDuel::getInstance().personnage->cards[i]!=nullptr && !SplendorDuel::getInstance().personnage->cards[i]->cardList.isEmpty()) {
            if (Rules::canBuyNoble(*SplendorDuel::getInstance().personnage->cards[i]->cardList[0] ,*this)){
                QList<EnumAction> c = SplendorDuel::getInstance().personnage->cards[i]->cardList[0]->getEffect();
                SplendorDuel::getInstance().personnage->clickCard(i, 0, SplendorDuel::getInstance().personnage->cards[i]->cardList[0]);
            }
        }
    }

    doAction(SingletonGameHandler::getInstance().action);

    //Achats Cartes reserver:
    for (int i = 0; i < 3; i++) {
        if (SplendorDuel::getInstance().ptab[1]->points->card[i]!=nullptr && !SplendorDuel::getInstance().ptab[1]->points->card[i]->isVide()) {
            if (this->canBuyCard(*SplendorDuel::getInstance().ptab[1]->points->card[i]->cardList.at(0))) {
                isplaying = false;

                QList<EnumAction> ac = SplendorDuel::getInstance().ptab[1]->points->card[i]->cardList.at(0)->getEffect();
                SplendorDuel::getInstance().ptab[1]->points->clickCard(i, 0, SplendorDuel::getInstance().ptab[1]->points->card[i]->cardList.at(0));
                doAction(ac);
                return;
            }
        }
    }
    //achat de cartes
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 + i; j++) {
            if (!SplendorDuel::getInstance().cards->cards[i][j]->cardList.isEmpty()) {
                Card* c = SplendorDuel::getInstance().cards->cards[i][j]->cardList[0];
                if (this->canBuyCard(*c)) {
                    isplaying = false;

                    SplendorDuel::getInstance().cards->clickCard(j, (i), c);
                    doAction(c->getEffect());
                    return;
                }
            }
        }
    }

    //sinon : reserve une carte
    if (this->nbCarteReserver < 3 && SingletonGameHandler::getInstance().board->hasGemOfType(EnumGemmes::Or)) {
        bool worked = false;
        for (int i = 2; i >= 0; i--) {
            for (int j = 0; j < 3 + i; j++) {
                if (!SplendorDuel::getInstance().cards->cards[i][j]->cardList.isEmpty()) {
                    worked = true;
                    SplendorDuel::getInstance().cards->clickDCard(j, i, SplendorDuel::getInstance().cards->cards[(i)][j]->cardList[0]);
                    break;
                }
            }
            if (worked)
                break;
        }
        if (worked) {
            //on cherhce le 1or du plateau
            for (int i = 0; i < Board::BOARD_SIDE; i++) {
                for (int j = 0; j < Board::BOARD_SIDE; j++) {
                    if (SingletonGameHandler::getInstance().board->connaitreGemmes(i * 5 + j) == EnumGemmes::Or) {
                        isplaying = false;

                        SplendorDuel::getInstance().board->board.hoverGemmes(i * 5 + j, true);
                        SplendorDuel::getInstance().board->board.clickGemmes(EnumGemmes::Or);
                        SplendorDuel::getInstance().board->board.hoverGemmes(i * 5 + j, false);
                        doAction(SingletonGameHandler::getInstance().action);
                        return;
                    }
                }
            }
        }
    }

    //ON PIOCHE
    SplendorDuel::getInstance().board->board.nbGemmes = 3;
    for (int k = 0; k < 3; k++) {
        for (int v = 0; v < 4; v++) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    SplendorDuel::getInstance().board->board.hoverGemmes(i * 5 + j, true);
                    if (Rules::isPossibleTakeGems(*SingletonGameHandler::getInstance().board, SplendorDuel::getInstance().board->board.posSelect, SingletonGameHandler::getInstance().action, EnumGemmes::Vide) != EnumAction::IMPOSSIBLE) {
                        isplaying = false;
                        SplendorDuel::getInstance().board->board.clickGemmes(EnumGemmes::Vide);
                        doAction(SingletonGameHandler::getInstance().action);
                        return;
                    }
                    SplendorDuel::getInstance().board->board.hoverGemmes(i * 5 + j, false);
                }
            }
            SplendorDuel::getInstance().board->board.changeDirection();
        }
        SplendorDuel::getInstance().board->board.scroll(-1);
    }
}

void AI::doAction(QList<EnumAction> ac) {
    bool worked = false;
    for (EnumAction a : ac) {
        switch (a)
        {
        case PICK_GEMMES:
            for (int i = 0; i < Board::BOARD_SIDE; i++) {
                for (int j = 0; j < Board::BOARD_SIDE; j++) {
                    if (SingletonGameHandler::getInstance().board->connaitreGemmes(i * 5 + j) == SingletonGameHandler::getInstance().typeToPick) {
                        SplendorDuel::getInstance().board->board.hoverGemmes(i * 5 + j, true);
                        SplendorDuel::getInstance().board->board.clickGemmes(EnumGemmes::Or);
                        SplendorDuel::getInstance().board->board.hoverGemmes(i * 5 + j, false);
                        worked = true;
                        break;
                    }
                }
                if (worked)
                    break;
            }
            break;
        case STEAL_GEMMES:
            for (int i = 0; i < NB_GEMMES_PAIEMENTS; i++) {
                if (SingletonGameHandler::getInstance().player1->gems[i] > 0) {
                    SplendorDuel::getInstance().ptab[0]->pgems->clickGemmes(static_cast<EnumGemmes>(i));
                    break;
                }
            }
            break;
        case ASSIGN_CARD:
            for (int i = 0; i < 5; i++) {
                if (!SplendorDuel::getInstance().ptab[1]->pcard->cards[i]->cardList.isEmpty()) {
                    SplendorDuel::getInstance().ptab[1]->pcard->clickCard(i, 0, SplendorDuel::getInstance().ptab[1]->pcard->cards[i]->cardList[0]);
                    break;
                }
            }
            break;
        case SUPP_GEMS:
            while (this->getNBGemmes() > 10) {
                for (int i = 0; i < NB_GEMMES_PAS_VIDE; i++) {
                    if (this->gems[i] > 0) {
                        SplendorDuel::getInstance().ptab[0]->pgems->clickGemmes(static_cast<EnumGemmes>(i));
                        break;
                    }
                }
            }
        case USE_PRIVILEGE:
            for (int i = 0; i < Board::BOARD_SIDE; i++) {
                for (int j = 0; j < Board::BOARD_SIDE; j++) {
                    if (SingletonGameHandler::getInstance().board->connaitreGemmes(i * 5 + j) != EnumGemmes::Or && SingletonGameHandler::getInstance().board->connaitreGemmes(i * 5 + j) != EnumGemmes::Vide) {
                        SplendorDuel::getInstance().board->board.hoverGemmes(i * 5 + j, true);
                        SplendorDuel::getInstance().board->board.clickGemmes(EnumGemmes::Or);
                        SplendorDuel::getInstance().board->board.hoverGemmes(i * 5 + j, false);
                        worked = true;
                        break;
                    }
                }
                if (worked)
                    break;
            }
        }
    }
    return;
}