#ifndef SYMBOL_H
#define SYMBOL_H

#include "ID.h"

class Symbol : public ID
{
public:
	Symbol(const ID& id = ID(0));
	~Symbol() {};

	int GetSign() const;

	ID GetInverse() const;                             // возвращает символ обратный к this
	bool IsInverseTo(const Symbol& input_value) const; // проверяет является ли input_value обратным к this 
};

#endif // SYMBOL_H