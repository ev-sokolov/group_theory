#include "CyclicSubGroup.h"

CyclicSubGroup::CyclicSubGroup(const GroupElement& g) : SubGroup(g.GetGroup()), Element(g) 
{} //�����������

const GroupElement &CyclicSubGroup::GetGenerating() const {
	return Element;//������������ ��������
}

bool CyclicSubGroup::IsContain(const GroupElement& input_value) const { 
	if (!SubGroup::IsContain(input_value)) return false; //���� �� ����������, �� ����
	if (GetPower(input_value) == UndefinedDegree) return false; //���� ������� ������������, �� ����
	else return true;//����� ������
}

const ElementDegree CyclicSubGroup::GetPower(const GroupElement &_elem, ElementDegree MaxDegree) const
{
	GroupElement ge(Word(), _elem.GetGroup());
	ElementDegree d = 0;
	GroupElement _elem1 = _elem.GetInverse();

	cout << 'A' << endl;
	cout << MaxDegree << endl;

if((!(GetGroup()->WordsAreEqual(ge, _elem))) && (!(GetGroup()->WordsAreEqual(ge, _elem1))) && (d != UndefinedDegree)){
	while ((!(GetGroup()->WordsAreEqual(ge, _elem))) && (!(GetGroup()->WordsAreEqual(ge, _elem1))) && (d != UndefinedDegree)) {
		ge = ge * Element;
		d--;
		if (d % 100 == 0) cout << d;
		if ((MaxDegree > 0) && (d*(-1) == MaxDegree)) return UndefinedDegree;
	}
}
else {
	if (GetGroup()->WordsAreEqual(ge, _elem)) { return d*(-1); }
	else { 
		return d; 
	}
	}
cout << 'B' << endl;
 throw GP_Exception();
	//����� ������� � ������� ����� �������� Element ����� �������� _elem
}

const GroupElement CyclicSubGroup::powerElement(ElementDegree p) const
{
	GroupElement ge(Word(), Element.GetGroup());
	ElementDegree d = 0;
	if (p < 0) {  
		p *= -1;
		while (d != p) {
			ge = ge * Element;
			d++;
		}
		return ge.GetInverse();
	}
	else {
		while (d != p) {
			ge = ge * Element;
			d++;
		}
		return ge;
	}
}//����� ��� ���������� ������ �������� � �������