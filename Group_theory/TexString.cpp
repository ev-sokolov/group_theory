#include "TexString.h"

TexString::TexString(const string& InputString)
{
	_InputString = InputString;

	int pos = 0;
	int pos_begin = 0;
	int pos_end = 0;

	while (pos != string::npos)
	{
		pos_begin = pos;

		pos = _InputString.find_first_not_of("{}_^,-0123456789", pos_begin + 1);

		if (pos != string::npos)
			pos_end = pos - 1;
		else
			pos_end = _InputString.size() - 1; 

		_Syllables.emplace_back(pos_begin, pos_end);
	}
}

BufferTex TexString::ConvertToBufferTex()
{
	BufferTex Result;
	ElementRecord ER_Buffer;

	// Проверяем все слоги на корректность синтаксиса
	for (auto itr = _Syllables.begin(); itr != _Syllables.end(); ++itr)
		TexSyntaxCheker(itr);

	// Конвертируем TexString в ElementRecord
	for (auto itr = _Syllables.begin(); itr != _Syllables.end(); ++itr)
	{
		int pos = 0, temp = 0;
		
		// Символ
		ER_Buffer.symbol = _InputString[itr->_pos_begin];
		
		// Индекс
		if (itr->_pos_index_beign != -1)
		{
			pos = itr->_pos_index_beign + 1;
			temp = 0;
			
			while (pos < itr->_pos_index_end)
			{
				temp = Parser_Number(pos);
				ER_Buffer.index.emplace_back(stoi(_InputString.substr(pos, temp - pos)));
				pos = temp + 1;
			}
		}

		// Степень
		if (itr->_pos_power_begin == -1)
		{ 
			ER_Buffer.power = 1;
		}
		else
		{
			pos = itr->_pos_power_begin;

			if (_InputString[itr->_pos_power_begin] == '{')
				pos++;

			temp = Parser_Number(pos);
			ER_Buffer.power = stoi(_InputString.substr(pos, temp - pos));
		}

		Result.emplace_back(ER_Buffer);

		ER_Buffer.index.clear();
	}

	return Result;
}

bool TexString::TexSyntaxCheker(list<TexSyllable>::iterator itr_Syllable) 
{
	int pos = itr_Syllable->_pos_begin + 1;
	bool power_correct_flag = false;

	switch (_InputString[pos])
	{
	// Конец строки
	case '\0':
		return true;
		break;

	// Возможное начало индекса 
	case '_':
		itr_Syllable->_pos_index_beign = pos + 1;
		pos = Parser_Index(itr_Syllable->_pos_index_beign);
		itr_Syllable->_pos_index_end = pos;
		break;
	
	// Возможное начало степени
	case '^':
		itr_Syllable->_pos_power_begin = pos + 1;
		pos = Parser_Power(itr_Syllable->_pos_power_begin);
		itr_Syllable->_pos_power_end = pos;
		power_correct_flag = true; // На случай когда в записи два знака степени
		break;

	default:
		throw TexString_Exception(_InputString, pos, TexString_UnexpectedData);
		break;
	}

	pos++;

	if (pos <= itr_Syllable->_pos_end)
	{
		switch (_InputString[pos])
		{
		// Возможное начало степени
		case '^':
			// Проверяем была ли уже степень ранее
			if (power_correct_flag)
				throw TexString_Exception(_InputString, pos, TexString_UnexpectedData);

			itr_Syllable->_pos_power_begin = pos + 1;
			pos = Parser_Power(itr_Syllable->_pos_power_begin);
			itr_Syllable->_pos_power_end = pos;

			break;
		default:
			throw TexString_Exception(_InputString, pos, TexString_UnexpectedData);
			break;
		}

		if (pos < itr_Syllable->_pos_end)
			throw TexString_Exception(_InputString, pos, TexString_UnexpectedData);
	}

	return true;
}

int TexString::Parser_Index(int pos_begin) const
{
	if (_InputString[pos_begin] != '{')
		throw TexString_Exception(_InputString, pos_begin, Index_Brackets_Begin);

	int pos_end = pos_begin + 1;

	while (_InputString[pos_end] != '}')
	{
		if (_InputString[pos_end] == '-')
			throw TexString_Exception(_InputString, pos_end, Index_IncorrectData);

		if ('0' <= _InputString[pos_end] && _InputString[pos_end] <= '9')
			pos_end = Parser_Number(pos_end);
		else
			throw TexString_Exception(_InputString, pos_end, Index_UnexpectedData);

		if (_InputString[pos_end] == ',')
			pos_end++;
	}

	// Проверяем не пусты ли скобки
	if ((pos_end - pos_begin) == 1)
		throw TexString_Exception(_InputString, pos_end, Index_Brackets_End);

	return pos_end;
}

int TexString::Parser_Power(int pos_begin) const
{
	int pos = 0;

	if (!('0' <= _InputString[pos_begin] && _InputString[pos_begin] <= '9') 
		&& _InputString[pos_begin] != '-' && _InputString[pos_begin] != '{')
	{ 
		throw TexString_Exception(_InputString, pos_begin, Power_UnexpectedData);
	}

	switch (_InputString[pos_begin])
	{
	case '{':
		pos = Parser_Number(pos_begin + 1);

		if (_InputString[pos] != '}')
			throw TexString_Exception (_InputString, pos, Power_Brackets_End);

		if ((pos - pos_begin) == 1)
			throw TexString_Exception(_InputString, pos, Power_Brackets_Empty);
		break;
	
	default:
		pos = Parser_Number(pos_begin);
		break;
	}

	return pos;
}

int TexString::Parser_Number(int pos_begin) const
{
	int digit_count = 0; // Количество цифр в числе, для проверки выхода числа за допустимые границы   
	int pos = pos_begin;

	if (_InputString[pos_begin] == '-') // Знак перед числом 
		pos++;

	while ('0' <= _InputString[pos] && _InputString[pos] <= '9')
	{
		pos++;
		digit_count++;
	}

	if (digit_count > 10)
		throw TexString_Exception(_InputString, pos, Number_OutOfLimits);

	return pos;
}
