#include "ContainerAbelianGroup.h"
#include <functional>

ContainerAbelianGroup::ContainerAbelianGroup(unsigned int gen_num, char elem_symbol) :
	_elem_symbol(elem_symbol), _gen_num(gen_num), _mask(ID(gen_num))
{
	_mask.GenerateMask(0, _mask.GetUnitsNumber());
}

bool ContainerAbelianGroup::WordIsEqualTo1(const GroupElement& input_value) const
{
	Word buffer = input_value;
	Word value = Sort(buffer);

	while (value.DeleteTrivials());

	return (value.size() == 0);
}

bool ContainerAbelianGroup::WordsAreConjugate(const GroupElement& left_value, const GroupElement& right_value) const
{
	return (WordsAreEqual(left_value, right_value));
}

Mask ContainerAbelianGroup::GetMask() const
{
	return _mask;
}

bool ContainerAbelianGroup::IsContain(const Symbol& input_value) const
{
	ID id = input_value & _mask;
	Bitset bs = id.GetValue() >> 1;
	return ((bs <= _gen_num) && (bs > 0));
}

BufferTex ContainerAbelianGroup::ConvertingWordToElementRecord(const GroupElement& input_value) const
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
		Buffer.index.push_back(((*it_w & _mask) >> 1).GetValue()); // (*it >> 1) & _alphabet_mask
		Buffer.power = *it_p;

		Result.push_back(Buffer);

		Buffer.index.clear();
	}

	return Result;
}

bool ContainerAbelianGroup::SymbolsCompare(const Symbol& left_vale, const Symbol& right_value) const
{
	Bitset left_id = left_vale.GetValue();
	Bitset right_id = right_value.GetValue();

	left_id = (left_id & _mask.GetValue()) >> 1;
	right_id = (right_id & _mask.GetValue()) >> 1;

	return left_id < right_id;
}

Word ContainerAbelianGroup::Sort(Word& input_value) const
{
	Word result = input_value;

	Word::iterator i = result.begin();

	while (i != result.end())
	{
		Word::iterator j = result.begin();
		
		while (j != result.end())
		{
			if (SymbolsCompare(*i, *j))
			{
				Symbol temp = *i;
				*i = *j;
				*j = temp;
			}
			++j;
		}
		++i;
	}

	return result;
}