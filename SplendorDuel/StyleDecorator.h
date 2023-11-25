#pragma once
#include <qstring.h>
class StyleDecorator
{
private:
	QString type;
	QString value;
	StyleDecorator* suivant;
public:
	StyleDecorator(const QString type, const QString value) : suivant(nullptr), type(type), value(value) {};
	void ajouter(const QString type, const QString value);
	void retirer(const QString type, const QString value);
	const QString text() const;
};

