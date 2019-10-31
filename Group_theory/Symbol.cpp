#include "Symbol.h"

Symbol::Symbol(const ID& id) : ID(id) {};

int Symbol::GetSign() const
{
	if ((*this & ID(1)) == ID(0))
		return 1;
	else
		return -1;
}

ID Symbol::GetInverse() const
{
	return (*this ^ ID(1));
}

bool Symbol::IsInverseTo(const Symbol& input_value) const
{
	return (this->GetInverse() == input_value);
}