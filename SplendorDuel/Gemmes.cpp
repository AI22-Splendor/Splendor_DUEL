#include "Gemmes.h"
#include <qstring.h>

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

const QString gemmesToQstr(const Gemmes& g){
	switch (g) {
	case Gemmes::Blanc:
		return QString{ "blanc" };
	case Gemmes::Vert:
		return QString{ "vert" };
	case Gemmes::Bleu:
		return QString{ "bleu" };
	case Gemmes::Or:
		return QString{ "or" };
	case Gemmes::Perle:
		return QString{ "perle" };
	case Gemmes::Noir:
		return QString{ "noir" };
	case Gemmes::Rouge:
		return  QString{"rouge"};
	case Gemmes::Vide :
		return  QString{"vide"};
	default:
		return "err";
	}
}
