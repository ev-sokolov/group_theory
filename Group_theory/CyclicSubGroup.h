#ifndef CYCLICSUBGROUP_H
#define CYCLICSUBGROUP_H
#include "SubGroup.h"

typedef int ElementDegree;
const ElementDegree UndefinedDegree = 1 << (sizeof(ElementDegree) * 8 - 1); 
// ��� ����������� �������������� �������

class CyclicSubGroup : public SubGroup 
{
public:
	const ContainerGroup *Group; //����
	const GroupElement Element; //������ ����
public:
	CyclicSubGroup(const GroupElement &g);//�����������
	const GroupElement &GetGenerating() const; //����� ��������� ������������ �������
	bool IsContain(const GroupElement& input_value) const; //���������� �� ������� � ��������� ��� ���.
	virtual const ElementDegree GetPower(const GroupElement &_elem, ElementDegree MaxDegree = UndefinedDegree) const;//������� ������� � ������� ����� �������� Element
	virtual const GroupElement powerElement(ElementDegree p) const;//����� ��� ���������� ������ �������� � �������
	
};
#endif // CYCLICSUBGROUP_H
