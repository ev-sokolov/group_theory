#ifndef SYMBOL_H
#define SYMBOL_H

#include "ID.h"

class Symbol : public ID
{
public:
	Symbol(const ID& id = ID(0));
	~Symbol() {};

	int GetSign() const;

	ID GetInverse() const;                             // ���������� ������ �������� � this
	bool IsInverseTo(const Symbol& input_value) const; // ��������� �������� �� input_value �������� � this 
};

#endif // SYMBOL_H