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
    //LES PRIVILEGES
    while (SingletonPrivilegeHandler::getInstance()->playerHasPrivilege(*this)) {
        //ON remplis le tableau si besoin
        SplendorDuel::getInstance().board->remplir.hover = true;
        SplendorDuel::getInstance().board->remplir.mousePressEvent(nullptr);
        SplendorDuel::getInstance().board->remplir.hover = false;

        SplendorDuel::getInstance().privilege->tab[1][0]->mousePressEvent(nullptr);
        doAction(SingletonGameHandler::getInstance().action);
    }

    //LES NOBLES
    for (int i = 0; i < 2; i++) {
        if (SplendorDuel::getInstance().personnage->cards[i]!=nullptr && !SplendorDuel::getInstance().personnage->cards[i]->cardList.isEmpty()) {
            if (Rules::canBuyNoble(*SplendorDuel::getInstance().personnage->cards[i]->cardList[0] ,*this)){
                SplendorDuel::getInstance().personnage->clickCard(i, 0, SplendorDuel::getInstance().personnage->cards[i]->cardList[0]);
            }
        }
    }

    //ON remplis le tableau si besoin
    SplendorDuel::getInstance().board->remplir.hover = true;
    SplendorDuel::getInstance().board->remplir.mousePressEvent(nullptr);
    SplendorDuel::getInstance().board->remplir.hover = false;

    //on se retire toues les actions de plus
    doAction(SingletonGameHandler::getInstance().action);

    //Achats Cartes reserver:
    for (int i = 0; i < 3; i++) {
        if (SplendorDuel::getInstance().ptab[1]->points->card[i]!=nullptr && !SplendorDuel::getInstance().ptab[1]->points->card[i]->isVide()) {
            if (this->canBuyCard(*SplendorDuel::getInstance().ptab[1]->points->card[i]->cardList.at(0))) {
                QList<EnumAction> ac = SplendorDuel::getInstance().ptab[1]->points->card[i]->cardList.at(0)->getEffect();
                SplendorDuel::getInstance().ptab[1]->points->clickCard(i, 0, SplendorDuel::getInstance().ptab[1]->points->card[i]->cardList.at(0));
                doAction(ac);
                return;
            }
        }
    }

    //achat de cartes
    int i = 2;
    for (vector<Card*> c1: SingletonGameHandler::getInstance().displayedCards) {
        int j = 0;
        for (Card* c2: c1) {
            if (c2!=nullptr && this->canBuyCard(*c2)) {
                SplendorDuel::getInstance().cards->clickCard(j, (i), SplendorDuel::getInstance().cards->cards[(i)][j]->cardList[0]);
                doAction(c2->getEffect());
                isplaying = false;
                return;
            }
            j++;
        }
        i--;
    }
    //sinon : reserve une carte
    if (this->nbCarteReserver < 3 && SingletonGameHandler::getInstance().board->hasGemOfType(EnumGemmes::Or)) {
        i = 2;
        bool worked = false;
        for (vector<Card*> c1 : SingletonGameHandler::getInstance().displayedCards) {
            int j = 0;
            for (Card* c2 : c1) {
                if (c2!= nullptr) {
                    worked = true;
                    SplendorDuel::getInstance().cards->clickDCard(j, i, SplendorDuel::getInstance().cards->cards[(i)][j]->cardList[0]);
                    break;
                }
                j++;
            }
            if (worked)break;
            i--;
        }
        //on cherhce le 1or du plateau
        for (int i = 0; i < Board::BOARD_SIDE; i++) {
            for (int j = 0; j < Board::BOARD_SIDE; j++) {
                if (SingletonGameHandler::getInstance().board->connaitreGemmes(i * 5 + j) == EnumGemmes::Or) {
                    SplendorDuel::getInstance().board->board.hoverGemmes(i * 5 + j, true);
                    SplendorDuel::getInstance().board->board.clickGemmes(EnumGemmes::Or);
                    SplendorDuel::getInstance().board->board.hoverGemmes(i * 5 + j, false);
                    isplaying = false;
                    return;
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
                        SplendorDuel::getInstance().board->board.clickGemmes(EnumGemmes::Vide);
                        isplaying = false;
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
    bool replay = false;
    bool worked = false;
    for (EnumAction a : ac) {
        switch (a)
        {
        case REPLAY:
            replay = true;
            break;
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
    isplaying = false;
    if (replay)
        play();
    return;
}