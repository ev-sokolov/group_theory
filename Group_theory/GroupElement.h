#ifndef GROUPELEMENT_H
#define GROUPELEMENT_H
#include "Word.h"
#include <windows.h>
#include "ContainerGroup.h"
#include <exception>

class ContainerGroup;

class GroupElement : public Word {
	const ContainerGroup *Group; //����
public:
	GroupElement(const Word&, const ContainerGroup*);
	GroupElement operator*(const GroupElement &right_value) const;
	GroupElement GetInverse() const;
	const ContainerGroup *GetGroup() const //���������� ������, ������� ����������� �������.
	{
		return Group;
	};
	
};
class GP_Exception : public std::exception
{};
#endif // GROUPELEMENT_H