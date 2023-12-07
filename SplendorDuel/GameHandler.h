#pragma once

#include "BoardUI.h"
#include "Bag.h"
#include "Board.h"
#include "Action.h"
#include <qlist.h>
#include "DrawPile.h"
#include "Player.h"
#include <random>
#include "Message.h"

class SingletonGameHandler {
public:
	static SingletonGameHandler* Instanciate(Bag* bag, Board* board, DrawPile** drawPiles, Player* player1, Player* player2);
	static void destroy();
	static inline SingletonGameHandler& getInstance() { return *SingletonGameHandler::instance; }
	bool gameFinished();
	const Player& getWinner();
	void nextAction();
	bool isPlayer1Turn();
	bool suppPlayerGems(EnumGemmes g, int p);
	bool reservCard(const Card* c, const int position);
	int buyCard(Card* c,const int position);
	Card* asignCard(Card* c);
	bool usePrivilege();
	Card* getDisplayedCard(int rareter, int pos);
	void playerBuyReservCard(int pnum);
	bool buyNoble(const Card* noble);
	bool playPrivilege();
	int getPlayerNbPrivilege(int pnum);
	void addOtherPlayerPrivilege();
	EnumAction getLastAction();
	Message getActionMessage()const;
	/// <summary>
	/// Affiche la selection de Gemmes en cours
	/// le nombre dépend de l'action en cours
	/// </summary>
	/// <param name="pos">sa position</param>
	/// <param name="isHover">afficher ou ne pas afficher</param>
	const int gemmesToSelect();

	/// <summary>
	/// On prend les gemmes exitante si leurs positions existe
	/// </summary>
	/// <param name="posTab">tableau de 3 int</param>
	bool gemmesPick(const int* posTab);

	/// <summary>
	/// Remplir le Board Avec le sac
	/// </summary>
	const Board& remplirBoard();
private:
	static SingletonGameHandler* instance;

	SingletonGameHandler(Bag* bag, Board* board, DrawPile** drawPiles, Player* player1, Player* player2)
		: bag(bag), typeToPick(EnumGemmes::Vide), toAssign(nullptr), board(board), drawPiles(drawPiles), player1(player1), mainActionIsDone(false), player2(player2), action() {
		for (int i = 0; i < 3; i++) {
			displayedCards.push_back(*(new vector<Card*>()));
			for (int j = 0; j < 5 - i; j++) {
				displayedCards[i].push_back(drawPiles[i]->piocher()); 
			}
		}
	}
	SingletonGameHandler(const SingletonGameHandler&)=delete;
	
	void addAction(const Card* c);

	
	~SingletonGameHandler(){
		delete bag;
		delete board;
		for (int i = 0; i < 3; i++) delete drawPiles[i];
		delete[] drawPiles;
		delete player1;
		delete player2;
		delete toAssign;
		for (vector<vector<Card*>>::iterator it = displayedCards.begin(); it != displayedCards.end(); it++) {
			for (vector<Card*>::iterator it2 = it->begin(); it2 != it->end(); it2++) {
				delete (*it2);
			}
		}
	}

	bool mainActionIsDone;
	QList<EnumAction> action;
	bool player1Joue;
	Bag* bag;
	Board* board;
	DrawPile** drawPiles;
	vector<vector<Card*>> displayedCards;
	Card* toAssign;
	Player* player1;
	Player* player2;
	EnumGemmes typeToPick;

	friend class SingletonPrivilegeHandler;
	friend class SingletonNobleHandler;
};
