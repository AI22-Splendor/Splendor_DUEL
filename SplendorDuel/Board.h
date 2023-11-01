#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Gemmes.h"
#include "Bag.h"

using namespace std;

/**
* Handles the board of the game
*/
class Board {
public: 
	Board() {
		gems = new Gemmes[BOARD_SIZE];
		for (int i = 0; i < BOARD_SIZE; i++) {
			gems[i] = Gemmes::Vide;
		}
	}

	void remplirBoard(const Bag& bag) const;
	Gemmes& prendreGemme(const int pos) const;

private:
	static const unsigned int BOARD_SIDE = 5;
	static const unsigned int BOARD_SIZE = BOARD_SIDE * BOARD_SIDE;
	Gemmes* gems;

	class iterator {
	public:
		iterator(const Board& board): board(board) {
			// We get the index of the center of the board
			nextIdx = BOARD_SIZE % 2 == 0 ? BOARD_SIZE / 2 : (BOARD_SIZE - 1) / 2;
		}
		bool hasNext() const {
			return stepsTaken < BOARD_SIZE;
		}
		Gemmes* getNext();

	private :
		enum Direction { Right, Down, Left, Up, Repeat };
		int nextDirection = Up;
		size_t nextIdx;
		int steps = 1;
		int stepRepetitionLeft = 2;
		int stepsLeftBeforeTurn = 1;
		int stepsTaken = 0;
		const Board& board;
	};

	friend class Board::iterator;
	friend ostream& operator<<(ostream& os, const Board board);

	iterator getIterator() const { return iterator(*this); }
};

ostream& operator<<(ostream& os, const Board board);

#endif