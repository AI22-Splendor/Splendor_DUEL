#ifndef MESSAGE_H
#define MESSAGE_H

#include <qstring.h>
#include <qcolor.h>
class Message
{
public:
	Message(const char* str, const char* color) : s(str), c(color) {};
	inline QString getString() { return s; };
	inline QColor getColor() { return c; };
	inline void operator=(Message m) { s = m.getString(); c = m.getColor(); }
private:
	QString s;
	QColor c;
};

#endif