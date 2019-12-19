#include "FM_Two_Groups.h"
#include "SubGroup.h"
#include "FiniteSubGroup.h"

FM_Two_Groups::FM_Two_Groups(SubGroupIzomorphizm *_phi) : phi(_phi)
{

	_max_units_number = GetA()->GetMask().GetUnitsNumber(); 
	if (GetB()->GetMask().GetUnitsNumber() > _max_units_number)
		_max_units_number = GetB()->GetMask().GetUnitsNumber();

	_coding_units = 2;
	_freeproduct_mask.GenerateMask(0, _max_units_number + _coding_units);
	_extraction_factor_number_mask.GenerateMask(_max_units_number, _coding_units);
}

Mask FM_Two_Groups::GetMask() const
{
	return _freeproduct_mask;
}

unsigned int FM_Two_Groups::GetMaxUnitsNumber() const
{
	return _max_units_number;
}

unsigned int FM_Two_Groups::GetCodingUnits() const
{
	return _coding_units;
}

bool FM_Two_Groups::IsContain(const Symbol& input_value) const
{
	try
	{
		const ContainerGroup *result = GetGroupAddress(input_value);
		return result->IsContain(input_value);
	}
	catch (GP_Exception())
	{
		return false;
	};
}

Bitset FM_Two_Groups::GetGroupNumber(const Symbol& input_value) const
{
	ID result = input_value;

	result = result & (_extraction_factor_number_mask);
	result = result >> _max_units_number;

	if (result.GetValue() - 1 > 1)
		throw GP_Exception();
	//return result.GetValue();
	return (Bitset)result.GetValue();

	}

GroupElement FM_Two_Groups::StandartImageOf(const GroupElement& input_value) const
{
	Word buffer(input_value);
	Bitset group_id = 0;
	if (input_value.GetGroup() == GetA()) group_id = 1;
	else if (input_value.GetGroup() == GetB()) group_id = 2;
	else throw GP_Exception();

	for (auto i = buffer.begin(); i != buffer.end(); ++i)
	{
		ID temp = *i;
		temp = temp & (~(ID(Bitset(3)) << (this->GetMaxUnitsNumber())));
		temp = temp | (ID(group_id) << (this->GetMaxUnitsNumber()));
		*i = temp;
	}

	return GroupElement(buffer,this);

}
const ContainerGroup *FM_Two_Groups::GetA() const {
	return phi->GetIzomorphizmDomain()->GetGroup(); //���������� ��������� �� ������ phi, �� ���� domain 
}
const ContainerGroup *FM_Two_Groups::GetB() const {
	return phi->GetIzomorphizmImage()->GetGroup();//���������� ��������� �� ������ phi, �� ���� image 
}
const ContainerGroup *FM_Two_Groups::GroupIDtoGroupPointer(Bitset id) const {
	if (id == 1) return GetA(); //���� id=1, �� �
	if (id == 2) return GetB(); //���� id=2, �� B
	throw GP_Exception(); //����� ����������
}
Bitset FM_Two_Groups::GroupPointertoGroupID(const ContainerGroup *p) const {
	if (p == GetA()) return 1; //���� p=A ���������� 1
	if (p == GetB()) return 2; //���� p=B ���������� 2
	throw GP_Exception(); //����� ����������
}
const ContainerGroup *FM_Two_Groups::GetGroupAddress(const Symbol& input_value) const{
	if (GetGroupNumber(input_value) == 1) return GetA(); //���� ����� ������=1 ���������� �
	if (GetGroupNumber(input_value) == 2) return GetB(); //���� ����� ������=2 ���������� �
	throw GP_Exception(); //����� ����������
}

const ContainerGroup *FM_Two_Groups::GetMultiplier(const GroupElement &input_value) const {
	return GetGroupAddress(*(input_value.begin())); //���������� ����� ���������� ��������� 
}

 GroupElement FM_Two_Groups::ListOfSyllablesToElement(const list<GroupElement> &l) const {
	GroupElement t= *(l.begin());//������� t ������ ������� �����
	for (list<GroupElement>::const_iterator iter = l.begin()++; iter != l.end(); ++iter) {
		t = t * *iter;//�������� t �� ��� �������� ������
	}
	return t;//�������� �������
}

list<GroupElement> FM_Two_Groups::ListOfSyllablesOf(const GroupElement& input_value) const {
	if (input_value.GetGroup() != this) throw GP_Exception();//���� ������ �� �������, �� ����������
		list<GroupElement> syliables; //������� ������

		if (input_value.size() == 0) 
			return syliables;

		auto word_iterator = input_value.begin(); 
		unsigned int current_group_id = this->GetGroupNumber(*word_iterator); 

		auto _begin = word_iterator;
		auto _end = word_iterator;

		++word_iterator;

		for (; word_iterator != input_value.end();)
		{
			unsigned int new_group_id = this->GetGroupNumber(*word_iterator);

			if (current_group_id == new_group_id)
			{
				++word_iterator;
			}
			else
			{
				_end = word_iterator;
				--_end;
				Word sub_word = input_value.GetSubWord(_begin, _end);
				GroupElement ge = StandartImageOf(GroupElement(sub_word, GroupIDtoGroupPointer(current_group_id)));
				syliables.emplace_back(ge);

				_begin = word_iterator;
				current_group_id = new_group_id;

				++word_iterator;
			}
		}
		_end = word_iterator;
		--_end;
		Word sub_word = input_value.GetSubWord(_begin, _end);
		GroupElement ge = StandartImageOf(GroupElement(sub_word, GroupIDtoGroupPointer(current_group_id)));
		syliables.emplace_back(ge);

		return syliables;
}

list<GroupElement> FM_Two_Groups::ReducedFormOf(const GroupElement& _elem) const { //�������� XI
	list<GroupElement> elem_syllables = ListOfSyllablesOf(_elem);// ������� ������
	bool flag; //������
	do {
		if (elem_syllables.size() == 1) return elem_syllables; //���� ������=1 ���������� ������
		flag = false;
		for (list<GroupElement>::iterator iter = elem_syllables.begin(); iter != elem_syllables.end(); ++iter) {
			const ContainerGroup *syllable_group = GetMultiplier(*iter); //������� ������ �� � ������� �����
			GroupElement syllable_elem = GroupElement(*iter, syllable_group);
			if (syllable_group == GetA()) { //���� A, ��
				if (phi->GetIzomorphizmDomain()->IsContain(syllable_elem)) { //���� ��������� �� ������ phi �� ���� domain, ��
					flag = true; // ���� � ������
					*iter = StandartImageOf(phi->ImageOf(syllable_elem)); //��������������� ��������
					list<GroupElement>::iterator itern = iter; itern++; // ������� ����� �������� ������ �������� ���������
					if (itern != elem_syllables.end()) { //���� ����� �������� ��������� �� ����� ������, ��
						*iter = *iter * *itern; //������ �������� �������� �� �����
						elem_syllables.erase(itern); //������� ����� �������� � ������ 
//						itern = iter; //����������� ������ ��������� �������� �������
					} 
					if (iter != elem_syllables.begin()) { // ���� �������� ��������� �� ������ ������, ��
						itern = iter; iter--; //��� �����

						//���������������� ������� iter == elem_syllables.begin()+1, ����� �� ���� iter--
						//����� ����� ��������� �������� �������� itern

						//cout << "itern= " << /*itern->size() <<*/ endl;
						

						*iter = *iter * *itern; //������ �������� �������� �� �����
						elem_syllables.erase(itern); //������� ����� �������� � ������ 
//						itern = iter; //����������� ������ ��������� �������� �������
					}
				}
			}
			else if (syllable_group == GetB()) { //���� ����� ��� B
				if (phi->GetIzomorphizmImage()->IsContain(syllable_elem)) {
					flag = true;
					*iter = StandartImageOf(phi->preImageOf(syllable_elem));
					list<GroupElement>::iterator itern = iter; itern++;
					if (itern != elem_syllables.end()) {
						*iter = *iter * *itern;
						elem_syllables.erase(itern);
//						itern = iter;
					}
					if (iter != elem_syllables.begin()) {
						itern = iter; iter--;
						*iter = *iter * *itern;
						elem_syllables.erase(itern);
//						itern = iter;
					}
				}
			}
		}
	} while (flag == true);
	cout << "����� �����������\n";
	
	return elem_syllables; //���������� ������������ ������
}

bool FM_Two_Groups::WordIsEqualTo1(const GroupElement &_elem) const {//CI
	list<GroupElement> elem_syllables = ReducedFormOf(_elem); //�������� � ������������ �����
	if (elem_syllables.size() > 1) return false; //���� ������ ������ 1, �� false
	else return GetMultiplier(*(elem_syllables.begin()))->WordIsEqualTo1(
		GroupElement(*(elem_syllables.begin()), GetMultiplier(*(elem_syllables.begin())))
		);
	//����� ���������� ����� GetMultiplier �� ������ ������
}

list<GroupElement> FM_Two_Groups::CyclicallyReducedFormOf(const GroupElement& input_word) const {//XII
	list<GroupElement> w = ReducedFormOf(input_word);//�������� � ������������ �����
	do {
		if ((w.size() % 2 == 0) || (w.size() == 1)) {//���� ����� ����� ��� ����� 1
			cout << "����� ���������� ��������� \n";
			return w;
		}
		else {
			list<GroupElement>::iterator iter = w.end();//�������� �� ����� �����
			iter--;//��� �����
			*(w.begin()) = *(w.begin()) * *iter;//�������� ������ �� ��������� ����
			w.erase(iter);//������� ��������� ����
			if (GetMultiplier(*(w.begin()))->WordIsEqualTo1(*(w.begin())))
				w.erase(w.begin());//������� ��������� ����
		}
	} while (true);
}

bool FM_Two_Groups::WordsAreConjugate(const GroupElement &u, const GroupElement &v) const { //CII
	const FiniteSubGroup *H = dynamic_cast<const FiniteSubGroup*>(phi->GetIzomorphizmDomain()); //��������� �� ���� � ���������� H
	const FiniteSubGroup *K = dynamic_cast<const FiniteSubGroup*>(phi->GetIzomorphizmImage()); //��������� �� ���� � ���������� K
	if (H == 0 || K == 0) throw;//���� ��������� ������, �� ����������
	list<GroupElement> u1 = CyclicallyReducedFormOf(u); //�������� ����� u � v � ���������� ������������� ����
	list<GroupElement> v1 = CyclicallyReducedFormOf(v);
	for (unsigned int i = 0; i < v1.size(); i++) { //���� �� v1
		GroupElement h = H->FirstElem(); //��������� �� ������ �������
		do {
			GroupElement h1 = StandartImageOf(h); //�������� ����� � ����������� ����
			if (WordsAreEqual(h1.GetInverse()*ListOfSyllablesToElement(v1)*h1, ListOfSyllablesToElement(u1))) return true;
			//���� ����� �����, �� ���������� ������
		} while (H->NextElem(h));
		v1.emplace_back(*(v1.begin())); //������� ������ � ����� 
		v1.erase(v1.begin()); //������� ������
	}
	return false;
}

BufferTex FM_Two_Groups::ConvertingWordToElementRecord(const GroupElement& input_value) const
{
	BufferTex Result;
	BufferTex Temp;

	GroupElement BufferWord = input_value;
	while (BufferWord.DeleteTrivials());
	list<GroupElement> syllables_words = ListOfSyllablesOf(BufferWord);

	auto it = Result.end();

	for (auto it_syllable : syllables_words)
	{
		//Word Subword = BufferWord.GetSubWord(it_syllable._begin, it_syllable._end);
		Temp = it_syllable.GetGroup()->ConvertingWordToElementRecord(it_syllable);

		for (auto& it_temp : Temp)
			it_temp.index.push_back(GroupPointertoGroupID(GetMultiplier(it_syllable)));

		Result.splice(it, Temp);
		Temp.clear();
	}
	return Result;
}
