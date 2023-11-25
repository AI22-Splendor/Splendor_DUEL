#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SplendorDuel.h"
#include "GameHandler.h"
#include "GemmesContainerGUI.h"
#include "CompleteBoardUI.h"
#include "PlayersUI.h"

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
    static inline void instanciate(Bag& bag, Board& board, DrawPile** drawPiles){
        if(SplendorDuel::instance == nullptr)
            SplendorDuel::instance = new SplendorDuel(bag, board, drawPiles);
    }

    static inline SplendorDuel& getInstance() { return *SplendorDuel::instance; };
    
    
    /// <summary>
    /// On ajoute au joueur une Gemmes
    /// </summary>
    /// <param name="g">la couleur de la gemme</param>
    /// <param name="p">sa position (de 0 à 6)</param>
    static inline void addPlayerGems(const Gemmes g, const int p){ 
        instance->ptab[p]->gemsAdd(g); 
    }

    /// <summary>
    /// lance le jeu
    /// </summary>
    static void start();

    /// <summary>
    /// ferme le jeu
    /// </summary>
    /// <returns></returns>
    static bool close();

private:
    //le singleton
    static SplendorDuel* instance;

    ~SplendorDuel();
    /// <summary>
    /// Constructeur
    /// </summary>
    /// <param name="bag">le sac du futur gameHandler</param>
    /// <param name="board">le board avec lequel initialiser notre UI et le GH</param>
    /// <param name="drawPiles">les carte avec lesquels initialisé notre UI et le GH</param>
    SplendorDuel(Bag& bag, Board& board, DrawPile** drawPiles);
    SplendorDuel(const SplendorDuel& s) = delete;

    void keyPressEvent(QKeyEvent* e);
    //notre board
    CompleteBoardUI* board;
    //nos joueurs
    PlayersUI** ptab;
    Ui::SplendorDuelClass ui;
};