#include "Gemmes.h"
#include <qstring.h>

ostream& operator<<(ostream& os, const EnumGemmes gem) {
	 switch (gem) {
	 case EnumGemmes::Vert:
		 os << "Ve"; break;
	 case EnumGemmes::Rouge:
		 os << "Ro"; break;
	 case EnumGemmes::Bleu:
		 os << "Bu"; break;
	 case EnumGemmes::Noir:
		 os << "No"; break;
	 case EnumGemmes::Blanc:
		 os << "Bc"; break;
	 case EnumGemmes::Or:
		 os << "Or"; break;
	 case EnumGemmes::Perle:
		 os << "Pe"; break;
	 case EnumGemmes::Vide:
		 os << "xx"; break;
	 }
	 return os;
}

const QString gemmesToQstr(const EnumGemmes g){
	switch (g) {
	case EnumGemmes::Blanc:
		return QString{ "blanc" };
	case EnumGemmes::Vert:
		return QString{ "vert" };
	case EnumGemmes::Bleu:
		return QString{ "bleu" };
	case EnumGemmes::Or:
		return QString{ "or" };
	case EnumGemmes::Perle:
		return QString{ "perle" };
	case EnumGemmes::Noir:
		return QString{ "noir" };
	case EnumGemmes::Rouge:
		return  QString{"rouge"};
	case EnumGemmes::Vide :
		return  QString{"vide"};
	default:
		return "err";
	}
}
