#include "Board.h"
#include "MyException.h"

#include <iostream>
using namespace std;

void Board::remplirBoard(const Bag& bag) const {
	iterator it = this->getIterator();
	while (it.hasNext()) {
		Gemmes* gem = it.getNext();
		*gem = bag.piocherGemme();
		cout << *gem << endl;
	}
}

Gemmes& Board::prendreGemme(const int pos) const {
	if (pos < BOARD_SIZE) {
		Gemmes& gem = gems[pos];
		gems[pos] = Gemmes::Vide;
		return gem;
	}
	char* error = new char[35];
	sprintf(error, "No gem at this position : %d", pos);
	throw new MyException(error);
}

Gemmes* Board::iterator::getNext() {
	cout << "next : " << nextIdx;
	cout << "(" << steps << ")";
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