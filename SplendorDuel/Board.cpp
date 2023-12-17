#include "Board.h"
#include "MyException.h"

#include <iostream>
using namespace std;

void Board::remplirBoard(const Bag& bag) const {
	iterator it = this->getIterator();
	while (it.hasNext()) {
		EnumGemmes* gem = it.getNext();
		if (*gem == EnumGemmes::Vide) {
			// Si il n'y a plus de gemmes dans le bag, alors la gemme retournée est nulle
			*gem = bag.piocherGemme();
		}
	}
}

EnumGemmes Board::prendreGemme(const int pos) const {
	if (pos < BOARD_SIZE) {
		EnumGemmes gem = gems[pos];
		gems[pos] = EnumGemmes::Vide;
		return gem;
	}
	char* error = new char[35];
	sprintf(error, "This position is out of the board: %d", pos);
	throw new MyException(error);
}

bool Board::positionPasVide(const int pos) const {
	if (pos < BOARD_SIZE && pos>=0) {
		return gems[pos] != EnumGemmes::Vide;
	}
	char* error = new char[35];
	sprintf(error, "This position is out of the board: %d", pos);
	throw new MyException(error);
}

EnumGemmes const Board::connaitreGemmes(const int pos) const {
	if (pos < BOARD_SIZE) {
		return gems[pos];
	}
	char* error = new char[35];
	sprintf(error, "This position is out of the board: %d", pos);
	throw new MyException(error);
}

bool Board::hasGemOfType(EnumGemmes gem) const {
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (gems[i] == gem) return true;
	}
	return false;
}

EnumGemmes* Board::iterator::getNext() {
	stepsLeftBeforeTurn--;
	stepsTaken++;
	EnumGemmes* current = &(board.gems[nextIdx]);
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


void Board::putGem(const int pos, EnumGemmes gem) {
	if (pos < BOARD_SIZE && pos >= 0) {
		gems[pos] = gem;
		return;
	}
	char* error = new char[35];
	sprintf(error, "This position is out of the board: %d", pos);
	throw new MyException(error);
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