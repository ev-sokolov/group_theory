
#ifndef CONTAINERGROUP_H
#define CONTAINERGROUP_H
#include <vector>

#include "Mask.h"
#include "Symbol.h"
#include "Word.h"
#include "GroupElement.h"
#include "InOut_put.h"
using namespace std;

class GroupElement;

class ContainerGroup
{
public:
	ContainerGroup() {};
	~ContainerGroup() {};

	// ��������� ������� ������� ��������� � �������������
	virtual bool WordIsEqualTo1(const GroupElement&) const = 0;                 // �������� ����� �� ��������� � ��������
	bool WordsAreEqual(const GroupElement&, const GroupElement&) const;					// �������� �� ���� �� ���������
	virtual bool WordsAreConjugate(const GroupElement&, const GroupElement&) const = 0; // �������� ���� �� �������������

	// ������������� ���������
	virtual Mask GetMask() const = 0;
	virtual bool IsContain(const Symbol&) const = 0;

	// ����� ������
	virtual BufferTex ConvertingWordToElementRecord(const GroupElement& input_value) const = 0;
};

#endif // CONTAINERGROUP_H