#include "Rules.h"
#include "NobleHandler.h"

Action Rules::isPossibleTakeGems(const Board b, const int* posTab, QList<Action> action, Gemmes g) {
	if (action.size()==0 || (action.size()==1 && action.contains(Action::REPLAY))) {
		int nbPerles = 0;
		//GEmmes pas vide et pas d'or et compte le nombre de perle
		for (int i = 0; i < 3; i++) {
			if (posTab[i] != -1) {
				if (!b.positionPasVide(posTab[i]) || b.connaitreGemmes(posTab[i]) == Gemmes::Or) {
					return Action::IMPOSSIBLE;
				}
				if (b.connaitreGemmes(posTab[i]) == Gemmes::Perle) {
					nbPerles++;
				}
			}
		}
		//Si 3 gemmes pareils
		if ((posTab[1] != -1 && posTab[2] != -1) && (b.connaitreGemmes(posTab[0]) == b.connaitreGemmes(posTab[1])) && (b.connaitreGemmes(posTab[1]) == b.connaitreGemmes(posTab[2]))) {
			GameHandler::getInstance().addCurrentPlayerPrivilege();
		}
		//si 2 perle piochées
		else if (nbPerles >= 2) {
			GameHandler::getInstance().addCurrentPlayerPrivilege();
		}
		//on peut et pas d'action spéciale
		return Action::MAIN_ACTION;
	}
	else if (action.contains(Action::RESERV_CARD)) {
		if (posTab[0] != -1 && b.positionPasVide(posTab[0]) && b.connaitreGemmes(posTab[0]) == Gemmes::Or) {
			return Action::RESERV_CARD;
		}
		else {
			return Action::IMPOSSIBLE;
		}
	}
	else if (action.contains(Action::PICK_GEMMES)) {
		if (posTab[0] != -1 && b.positionPasVide(posTab[0]) && b.connaitreGemmes(posTab[0]) == g) {
			return Action::PICK_GEMMES;
		}
		return Action::IMPOSSIBLE;
	}
	else if(action.contains(Action::USE_PRIVILEGE)){
		if (posTab[0] != -1 && b.positionPasVide(posTab[0]) && b.connaitreGemmes(posTab[0])!=Gemmes::Or) {
			return Action::USE_PRIVILEGE;
		}
		else {
			return Action::IMPOSSIBLE;
		}
	}
	else {
		return Action::IMPOSSIBLE;
	}
}

bool Rules::playerWon(const Player& player) {
	if (player.getPrestige() >= 20 || player.getNbCrowns() >= 10) {
		return true;
	}
	for (int i = 0; i < NB_GEMMES_PAIEMENTS; i++) {
		Gemmes gem = static_cast<Gemmes>(i);
		if (player.getPrestige(gem) >= 10) return true;
	}
	return false;
}

bool Rules::playerHaveToSuppGems(const Player& player) {
	if (player.getNBGemmes() > 10)
		return true;
	return false;
}

bool Rules::playerCanBuyCardAsign(const Player& player) {
	for (const Card* c:player.getCards()) {
		if (c->getDiscountType() != Gemmes::Vide)
			return true;
	}
	return false;
}

bool Rules::canBuyNoble(const Card& noble, const Player& player) {
	return NobleHandler::getInstance()->playerCanBuyNoble(noble, player);
}