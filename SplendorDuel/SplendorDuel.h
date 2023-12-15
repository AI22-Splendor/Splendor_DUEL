#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SplendorDuel.h"
#include "GameHandler.h"
#include "GemmesContainerGUI.h"
#include "CompleteBoardUI.h"
#include "PlayersUI.h"
#include "PrivilegeBoardUI.h"
#include "Player.h"
<<<<<<< Updated upstream
=======
#include "AI.h"
#include "InformationMessageUI.h"
#include "BoardCard.h"
>>>>>>> Stashed changes

/// <summary>
/// Notre fenetre principale
/// un singleton car on en auras qu'une seule durant tpute l'execution de notre programme
/// </summary>
class SplendorDuel : public QMainWindow
{
    Q_OBJECT

public:
    /// <summary>
    /// instancie SplendorDuel
    /// </summary>
    /// <param name="bag">le sac</param>
    /// <param name="board">le board</param>
    /// <param name="drawPiles">les cartes</param>
    static inline void instanciate(Bag& bag, Board& board, DrawPile** drawPiles, Player* p1, Player* p2) {
        if (SplendorDuel::instance == nullptr) {
            SplendorDuel::instance = new SplendorDuel(bag, board, drawPiles, p1, p2);
            SplendorDuel::instance->changePtour();
            SplendorDuel::instance->privilege->refreshPrivilege();
        }
    }

    static inline SplendorDuel& getInstance() { return *SplendorDuel::instance; };
    
    /// <summary>
   /// On ajoute au joueur une Gemmes
   /// </summary>
   /// <param name="g">la couleur de la gemme</param>
   /// <param name="p">sa position (de 0 ï¿½ 6)</param>
    static inline void refreshPlayersGems(const int p) {
        instance->ptab[p]->setGemmes();
    }

    static void addPlayerCard(Card* c, int pturn);

    static void reservCard(Card* c, int pturn) {
        instance->ptab[pturn]->reservCard(c);
    }

    /// <summary>
    /// ferme le jeu
    /// </summary>
    /// <returns></returns>
    static bool close();

    static void refreshPrivilege() {
        instance->privilege->refreshPrivilege();
    }

    static void changePtour();

private:
    //le singleton
    static SplendorDuel* instance;

    ~SplendorDuel();

    /// <summary>
    /// Constructeur
    /// </summary>
    /// <param name="bag">le sac du futur gameHandler</param>
    /// <param name="board">le board avec lequel initialiser notre UI et le GH</param>
<<<<<<< Updated upstream
    /// <param name="drawPiles">les carte avec lesquels initialisé notre UI et le GH</param>
    SplendorDuel(Bag& bag, Board& board, DrawPile** drawPiles, Player* p1, Player* p2);
=======
    /// <param name="drawPiles">les carte avec lesquels initialisï¿½ notre UI et le GH</param>
    SplendorDuel(Bag* bag, Board* board, DrawPile** drawPiles, Player* p1, Player* p2);
>>>>>>> Stashed changes
    SplendorDuel(const SplendorDuel& s) = delete;

    void keyPressEvent(QKeyEvent* e);
    //notre board
    CompleteBoardUI* board;
    //nos joueurs
    PlayersUI** ptab;

    BoardCardUI* boardcards;

    //nos privilege
    PrivilegeBoardUI* privilege;
    Ui::SplendorDuelClass ui;
    
    friend class AI;
};