#ifndef FG_ABELIANGROUPCSG_H
#define FG_ABELIANGROUPCSG_H
#include "CyclicSubGroup.h"
#include "FG_AbelianGroup.h"

class FG_AbelianGroupCSG  : virtual public CyclicSubGroup
{

public:
	FG_AbelianGroupCSG(const GroupElement &g);//�����������
	const ElementDegree GetPower(const GroupElement &_elem, ElementDegree MaxDegree = UndefinedDegree) const;//������� ������� � ������� ����� �������� Element
};
#endif // FG_ABELIANGROUPCSG_H