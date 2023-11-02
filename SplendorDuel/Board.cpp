#include "Board.h"
#include "MyException.h"

#include <iostream>
using namespace std;

void Board::remplirBoard(const Bag& bag) const {
	iterator it = this->getIterator();
	while (it.hasNext()) {
		Gemmes* gem = it.getNext();
		if (*gem == Gemmes::Vide) {
			// Si il n'y a plus de gemmes dans le bag, alors la gemme retournée est nulle
			*gem = bag.piocherGemme();
		}
	}
}

Gemmes Board::prendreGemme(const int pos) const {
	if (pos < BOARD_SIZE) {
		Gemmes gem = gems[pos];
		gems[pos] = Gemmes::Vide;
		return gem;
	}
	char* error = new char[35];
	sprintf(error, "This position is out of the board: %d", pos);
	throw new MyException(error);
}

bool Board::positionPasVide(const int pos) const {
	if (pos < BOARD_SIZE) {
		return gems[pos] == Gemmes::Vide;
	}
	char* error = new char[35];
	sprintf(error, "This position is out of the board: %d", pos);
	throw new MyException(error);
}

Gemmes* Board::iterator::getNext() {
	stepsLeftBeforeTurn--;
	stepsTaken++;
	Gemmes* current = &(board.gems[nextIdx]);
	if (stepsLeftBeforeTurn == 0) {
		nextDirection++;
		stepsLeftBeforeTurn = steps;
		stepRepetitionLeft--;
		if (static_cast<Direction>(nextDirection) == Direction::Repeat) {
			nextDirection = Right;
		}
	}
	if (stepRepetitionLeft == 0) {
		steps++;
		stepRepetitionLeft = 2;
	}
	Direction direction = static_cast<Direction>(nextDirection);

	if (direction == Direction::Right) {
		nextIdx++;
	}
	else if (direction == Direction::Down) {
		nextIdx += Board::BOARD_SIDE;
	}
	else if (direction == Direction::Left) {
		nextIdx--;
	}
	else if (direction == Direction::Up) {
		nextIdx -= Board::BOARD_SIDE;
	}
	return current;
}


ostream& operator<<(ostream& os, const Board board) {
	for (int i = 0; i < Board::BOARD_SIDE; i++) {
		for (int j = 0; j < Board::BOARD_SIDE; j++) {
			os << "  " << board.gems[i * Board::BOARD_SIDE + j];
		}
		os << endl;
	}
	return os;
}