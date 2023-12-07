#include "Rules.h"
#include "NobleHandler.h"

EnumAction Rules::isPossibleTakeGems(const Board b, const int* posTab, QList<EnumAction> action, EnumGemmes g) {
	if (action.size()==0 || (action.size()==1 && action.contains(EnumAction::REPLAY))) {
		int nbPerles = 0;
		//GEmmes pas vide et pas d'or et compte le nombre de perle
		for (int i = 0; i < 3; i++) {
			if (posTab[i] != -1) {
				if (!b.positionPasVide(posTab[i]) || b.connaitreGemmes(posTab[i]) == EnumGemmes::Or) {
					return EnumAction::IMPOSSIBLE;
				}
				if (b.connaitreGemmes(posTab[i]) == EnumGemmes::Perle) {
					nbPerles++;
				}
			}
		}
		//Si 3 gemmes pareils
		if ((posTab[1] != -1 && posTab[2] != -1) && (b.connaitreGemmes(posTab[0]) == b.connaitreGemmes(posTab[1])) && (b.connaitreGemmes(posTab[1]) == b.connaitreGemmes(posTab[2]))) {
			SingletonGameHandler::getInstance().addOtherPlayerPrivilege();
		}
		//si 2 perle piochées
		else if (nbPerles >= 2) {
			SingletonGameHandler::getInstance().addOtherPlayerPrivilege();
		}
		//on peut et pas d'action spéciale
		return EnumAction::MAIN_ACTION;
	}
	else if (action.contains(EnumAction::RESERV_CARD)) {
		if (posTab[0] != -1 && b.positionPasVide(posTab[0]) && b.connaitreGemmes(posTab[0]) == EnumGemmes::Or) {
			return EnumAction::RESERV_CARD;
		}
		else {
			return EnumAction::IMPOSSIBLE;
		}
	}
	else if (action.contains(EnumAction::PICK_GEMMES)) {
		if (posTab[0] != -1 && b.positionPasVide(posTab[0]) && b.connaitreGemmes(posTab[0]) == g) {
			return EnumAction::PICK_GEMMES;
		}
		return EnumAction::IMPOSSIBLE;
	}
	else if(action.contains(EnumAction::USE_PRIVILEGE)){
		if (posTab[0] != -1 && b.positionPasVide(posTab[0]) && b.connaitreGemmes(posTab[0])!=EnumGemmes::Or) {
			return EnumAction::USE_PRIVILEGE;
		}
		else {
			return EnumAction::IMPOSSIBLE;
		}
	}
	else {
		return EnumAction::IMPOSSIBLE;
	}
}

bool Rules::playerWon(const Player& player) {
	if (player.getPrestige() >= 20 || player.getNbCrowns() >= 10 || player.getHighestGemPrestigeCount()>=10 ) {
		cout << "Prestige : " << player.getPrestige() << " / Crowns : " << player.getNbCrowns() << " / Highest Gem Count : " << player.getHighestGemPrestigeCount() << endl;
		return true;
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
		if (c->getDiscountType() != EnumGemmes::Vide)
			return true;
	}
	return false;
}

bool Rules::canBuyNoble(const Card& noble, const Player& player) {
	return SingletonNobleHandler::getInstance()->playerCanBuyNoble(noble, player);
}