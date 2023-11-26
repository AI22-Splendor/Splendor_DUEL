#include "CardEffectPlayAgain.h"
#include "GameHandler.h"


void CardEffectPlayAgain::executeEffect() {
	GameHandler::getInstance().replayTurn();
}