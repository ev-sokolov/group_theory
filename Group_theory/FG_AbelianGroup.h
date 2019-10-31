#ifndef FG_ABELIANGROUP_H
#define FG_ABELIANGROUP_H
#include "ContainerGroup.h"
#include <vector>

class FG_AbelianGroup : public ContainerGroup //����� ��� ������� ������ ��
{
public:
	typedef vector<int> FG_AbelianGroupElement; 
private:
	FG_AbelianGroupElement _order; //���� ��� ������� ��������
public:
	FG_AbelianGroup(FG_AbelianGroupElement order, char elem_symbol);//�����������
	FG_AbelianGroupElement GetOrders() const; //����� ��� ��������� ��������
	FG_AbelianGroupElement ToFG_AbelianGroupElement(const GroupElement &elem) const; 
	//��������� GE � FG_AbelianGroupElement
	bool WordIsEqualTo1(const GroupElement& input_value) const; // �������� ����� �� ��������� � ��������
	bool WordsAreConjugate(const GroupElement& left_value, const GroupElement& right_value) const; // �������� ������� �������� �������������
	Mask GetMask() const;
	bool IsContain(const Symbol& input_value) const;
	BufferTex ConvertingWordToElementRecord(const GroupElement& input_value) const;

private:
	Mask _mask;
	// ����� ������
	char _elem_symbol;
};
#endif // FG_ABELIANGROUP_H
