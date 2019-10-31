#ifndef MASK_H
#define MASK_H

#include "ID.h"

class Mask : public ID
{
public:
	Mask(const unsigned int& units_number = 0);
	Mask(const ID& id);
	~Mask() {};

	unsigned int GetUnitsNumber(); // возвращает количество единиц в маске

	void GenerateMask(unsigned int first_bit, unsigned int count);	

private:
	unsigned int _units_number = 0;
};

#endif // MASK_H