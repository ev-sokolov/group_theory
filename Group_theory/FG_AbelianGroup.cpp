#include "FG_AbelianGroup.h"
#include "ContainerAbelianGroup.h"
#include <functional>
#include <vector>

FG_AbelianGroup::FG_AbelianGroup(FG_AbelianGroupElement order, char elem_symbol) :
  _elem_symbol(elem_symbol), _order(order), _mask(ID(order.size()))
{
	_mask.GenerateMask(0, _mask.GetUnitsNumber()+1);
}//конструктор

bool FG_AbelianGroup::WordIsEqualTo1(const GroupElement& input_value) const
{
	if (input_value.GetGroup() != this) throw GP_Exception(); 
	//если элемент отличается от группы, то исключение
	const FG_AbelianGroup *gr = dynamic_cast<const FG_AbelianGroup*>(input_value.GetGroup());
	FG_AbelianGroup::FG_AbelianGroupElement u = gr->ToFG_AbelianGroupElement(input_value);
	for (unsigned int i = 0; i < _order.size(); i++) {
		if (u[i] != 0) return false;
	}
	return true;
}

FG_AbelianGroup::FG_AbelianGroupElement FG_AbelianGroup::GetOrders() const {
	return _order; //возвращаемое значение
}

bool FG_AbelianGroup::WordsAreConjugate(const GroupElement& left_value, const GroupElement& right_value) const
{
	return (WordsAreEqual(left_value, right_value));
}

Mask FG_AbelianGroup::GetMask() const
{
	return _mask;
}

bool FG_AbelianGroup::IsContain(const Symbol& input_value) const
{
	ID id = input_value & _mask;
	Bitset bs = id.GetValue() >> 1;
	return ((bs <= _order.size()) && (bs > 0));
}

BufferTex FG_AbelianGroup::ConvertingWordToElementRecord(const GroupElement& input_value) const
{
	BufferTex Result;
	ElementRecord Buffer;

	if (input_value.empty())
		return Result;

	GroupElement word = input_value;

	while (word.DeleteTrivials());
	list<int> powers = ReducingSimilarTerms(word);

	auto it_w = word.begin();
	auto it_p = powers.begin();

	for (; it_w != word.end(); ++it_w, ++it_p)
	{
		Buffer.symbol = this->_elem_symbol;
		Buffer.index.push_back(((*it_w & _mask) >> 1).GetValue()); 
		Buffer.power = *it_p;

		Result.push_back(Buffer);

		Buffer.index.clear();
	}

	return Result;
}

FG_AbelianGroup::FG_AbelianGroupElement FG_AbelianGroup::ToFG_AbelianGroupElement(const GroupElement &elem) const {
	FG_AbelianGroupElement v(_order.size()); //элемент(вектор) размера _order.size()
	for (unsigned int i = 0; i < _order.size(); i++) v[i] = 0; //присваиваем всем элементам v значение равное 0
	for (GroupElement::const_iterator iter = elem.begin(); iter != elem.end(); iter++) {
		Bitset index = ((*iter & _mask) >> 1).GetValue();
		if (iter->GetSign() == 1) { v[index]++; }
		else { v[index]--; }
		//throw GP_Exception();   //?
	}
	for (unsigned int i = 0; i < _order.size(); i++)
		if (_order[i] != 0) {
			if (v[i] < 0) v[i] += _order[i] * (-v[i] / _order[i] + 1);
			v[i] %= _order[i];
		}
	return v;
}