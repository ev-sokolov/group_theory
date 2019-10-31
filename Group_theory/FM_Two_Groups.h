#ifndef FM_TWO_GROUPS_H
#define FM_TWO_GROUPS_H
#include "SubGroupIzomorphizm.h"
#include "FiniteSubGroup.h"

class FM_Two_Groups : public ContainerGroup
{
	SubGroupIzomorphizm *phi; //���� 
public:
	FM_Two_Groups(SubGroupIzomorphizm *_phi);//�����������
	
	list<GroupElement> ReducedFormOf(const GroupElement& input_word) const; // ���������� ����� � ������������ �����
	list<GroupElement> CyclicallyReducedFormOf(const GroupElement& input_word) const;//���������� ����� � ���������� �������������
	bool WordIsEqualTo1(const GroupElement&) const; //�������� CI
	bool WordsAreConjugate(const GroupElement&, const GroupElement&) const; //�������� CII

	Mask GetMask() const;//��������� ����� ��������
	bool IsContain(const Symbol& input_value) const; // ��������� ������ input_value �� �������������� ������ 
	GroupElement StandartImageOf(const GroupElement& input_value) const; // ����������������� ����� input_value, ��� �������� ���������� ������������

	const ContainerGroup *GetA() const; //���������  A
	const ContainerGroup *GetB() const; //���������  B
	
	const ContainerGroup *GetGroupAddress(const Symbol& input_value) const;  //��������� ������ ���������� ��������� �� � ������ (id)
	GroupElement ListOfSyllablesToElement(const list<GroupElement> &l) const;  //��������� ������ ������ � ������� 
	list<GroupElement> ListOfSyllablesOf(const GroupElement& input_value) const;  //��������� ������� � ������������ ������
	BufferTex FM_Two_Groups::ConvertingWordToElementRecord(const GroupElement& input_value) const;

protected:
	// ������������� ���������
	Bitset GetGroupNumber(const Symbol& input_value) const; // ���������� ����� ������ ������� ����������� input_value
	unsigned int GetMaxUnitsNumber() const;
	unsigned int GetCodingUnits() const;

private:
	const ContainerGroup *GroupIDtoGroupPointer(Bitset id) const;//��������� ������ ���������� ��������� �� ��� id 
	Bitset GroupPointertoGroupID(const ContainerGroup *p) const; //��������� ����� ���������� ��������� ���������� id
	const ContainerGroup *GetMultiplier(const GroupElement &input_value) const;
	// ������������� ���������
	Mask _freeproduct_mask;              // ����� ���������� ������������
	Mask _extraction_factor_number_mask; // ����� ��� ���������� id ������
	unsigned int _max_units_number;		 // ������������ ���������� ������ �� ����� ��������� 
	unsigned int _coding_units;          // ���������� ������, ������ ��� ����������� ���������� ���������� ������������ 
};

#endif // FM_TWO_GROUPS_H
