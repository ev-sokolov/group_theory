#include "Mask.h"

Mask::Mask(const unsigned int& units_number)
{
	GenerateMask(0, units_number);
}

Mask::Mask(const ID& id) : ID(id)
{
	_units_number = 0;

	ID temp = *this;

	while (temp != ID(0))
	{
		temp = temp & ~(ID(1) << _units_number);
		_units_number++;
	}
};

unsigned int Mask::GetUnitsNumber()
{
	return _units_number;
}

void Mask::GenerateMask(unsigned int first_bit, unsigned int count)
{
	ID temp = *this;
	
	for (unsigned int i = first_bit; i < (first_bit + count); i++)
		temp = temp | (ID(1) << i);
	
	*this = temp;

	_units_number = count;
}