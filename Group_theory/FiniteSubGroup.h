#ifndef FINITESUBGROUP
#define FINITESUBGROUP
#include "SubGroup.h"
#include "GroupElement.h"

class FiniteSubGroup : virtual public SubGroup
{
public:
	FiniteSubGroup(const ContainerGroup*);
	virtual GroupElement FirstElem() const = 0; //����� ����������� ����� ��� ���������� ������� ��������
	virtual bool NextElem(GroupElement &u) const = 0; //����� ����������� ����� ��� ���������� ���������� ��������
};
#endif //FINITESUBGROUP
