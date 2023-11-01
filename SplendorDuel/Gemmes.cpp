#include "Gemmes.h"

ostream& operator<<(ostream& os, const Gemmes& gem) {
	 switch (gem) {
	 case Gemmes::Vert:
		 os << "Ve"; break;
	 case Gemmes::Rouge:
		 os << "Ro"; break;
	 case Gemmes::Bleu:
		 os << "Bu"; break;
	 case Gemmes::Noir:
		 os << "No"; break;
	 case Gemmes::Blanc:
		 os << "Bc"; break;
	 case Gemmes::Or:
		 os << "Or"; break;
	 case Gemmes::Perle:
		 os << "Pe"; break;
	 case Gemmes::Vide:
		 os << "xx"; break;
	 }
	 return os;
}