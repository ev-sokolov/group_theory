#include "InOut_put.h"

// Ввод данных
Word ConvertingTexToWord(TexString input_value)
{
	ListOfSymbols Result;

	BufferTex BT_buffer = input_value.ConvertToBufferTex();

	for (auto itr_buffer : BT_buffer)
	{
		for (int i = 0; i < abs(itr_buffer.power); i++)
		{ 
			if (itr_buffer.power < 0)
			{
				for (auto itr_index : itr_buffer.index)
					Result.emplace_back(Symbol(ID(itr_index * 2)).GetInverse());
			}
			else
			{ 
				for (auto itr_index : itr_buffer.index)
					Result.emplace_back(ID(itr_index * 2));
			}
		}
	}

	return Word(Result);
}

// Вывод данных
string ConvertingBufferTexToTex(const BufferTex& input_value)
{
	string Result = "";

	for (auto it_buffer : input_value)
	{
		// Символ
		Result += it_buffer.symbol;

		// Индекс 
		if (!it_buffer.index.empty())
		{
			Result += "_{";

			for (auto it_index = it_buffer.index.begin();;)
			{
				Result += to_string(*it_index);
				it_index++;

				if (it_index == it_buffer.index.end())
					break;
				else
					Result += ',';
			}

			Result += '}';
		}

		// Степень
		if (it_buffer.power != 1)
		{
			Result += "^{";
			Result += to_string(it_buffer.power);
			Result += "}";
		}
	}

	return Result;
}

list<int> ReducingSimilarTerms(Word& InputValue)
{
	list<int> powers;
	if (!InputValue.empty())
	{
		Word buffer = InputValue;

		auto i = InputValue.begin();

		powers.push_back(i->GetSign());
		Symbol buff = *i;

		++i;

		for (; i != InputValue.end();)
		{
			if ((buff >> 1) == (*i >> 1))
			{
				powers.back() += i->GetSign();
				i = InputValue.erase(i);
			}
			else
			{
				powers.push_back(i->GetSign());
				buff = *i;
				++i;
			}
		}
	}

	return powers;
}