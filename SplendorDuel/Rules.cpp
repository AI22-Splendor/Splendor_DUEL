#include "Rules.h"

Action Rules::isPossibleTakeGems(const Board b, const int* posTab, Action action) {
	if (action == Action::MAIN_ACTION) {
		int nb = 0;
		//GEmmes pas vide et pas d'or et compte le nombre de perle
		for (int i = 0; i < 3; i++) {
			if (!b.positionPasVide(posTab[i]) || b.connaitreGemmes(posTab[i]) == Gemmes::Or)
				return Action::IMPOSSIBLE;
			if (b.connaitreGemmes(posTab[i]) == Gemmes::Perle)
				nb++;
		}
		//Si 3 gemmes pareils
		if (b.connaitreGemmes(posTab[0]) == b.connaitreGemmes(posTab[1]) && b.connaitreGemmes(posTab[1]) == b.connaitreGemmes(posTab[2]))
			return Action::ADD_PRIVILEGE;
		//si 2 perle piocher
		if (nb >= 2)
			return Action::ADD_PRIVILEGE;
	}
	//on peut et pas d'action spéciale
	return action;
}