#ifndef SUBGROUP
#define SUBGROUP
#include "ContainerGroup.h"
#include "GroupElement.h"
#include "Word.h"
class SubGroup 
{
	const ContainerGroup *Group; //����
public: 
	
	SubGroup(const ContainerGroup*);//�����������
	const ContainerGroup *GetGroup() const;//���������� �������� ���� Group
	virtual bool IsContain(const GroupElement& input_value) const = 0;//���������� �� ������� � ��������� ��� ���.
	
};
#endif // SUBGROUP