#include "Rules.h"

Action Rules::isPossibleTakeGems(const Board b, const int* posTab, Action action) {
	if (Action::SUPP_GEMS == action) {
		return Action::IMPOSSIBLE;
	}

	if (action == Action::MAIN_ACTION) {
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
			return Action::ADD_PRIVILEGE;
		}
		//si 2 perle piochées
		if (nbPerles >= 2) {
			return Action::ADD_PRIVILEGE;
		}
	}

	//on peut et pas d'action spéciale
	return action;
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