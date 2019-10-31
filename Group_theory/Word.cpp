#include "Word.h"

Word::Word(ListOfSymbols input_value) : ListOfSymbols(input_value) {};

bool Word::operator==(const Word& right_value) const
{
	if (this->size() != right_value.size())
	{
		return false;
	}
	else
	{
		auto it_LeftWord = this->begin();

		for (auto it_RightWord : right_value)
		{
			if (*it_LeftWord != it_RightWord)
				return false;

			++it_LeftWord;
		}
	}

	return true;
}

bool Word::operator!=(const Word& right_value) const
{
	return (!(*this == right_value));
}



Word Word::GetSubWord(const_iterator subword_begin, const_iterator subword_end) const
{
	Word subword;

	for (const_iterator it = subword_begin; it != subword_end; ++it)
		subword.emplace_back(*it);

	subword.emplace_back(*subword_end);

	return subword;
}


Word::iterator Word::DeleteSubWord(iterator SubWordBegin, iterator SubWordEnd)
{
	this->erase(SubWordBegin, SubWordEnd) ; // Метод erase удаляет элементы от SubWordBegin, до SubWordEnd не включая его.
	return (this->erase(SubWordEnd)); // Удалаяем элемент на который указывает итератор SubWordBegin и возвращаем итератор указывающий на слеующий элемент списка.
}

bool Word::DeleteTrivials()
{
	// Проверяем не пустое ли слово
	if (this->empty())
		return false;

	bool was_changed = false;

	auto it_word = this->begin();
	auto buffer = it_word;
	
	++it_word;
	
	for (; it_word != this->end();)
	{
		if (it_word->IsInverseTo(*buffer))
		{
			it_word = this->DeleteSubWord(buffer, it_word);

			was_changed = true;

			if (it_word == this->end())
				break;
		}

		buffer = it_word;
		++it_word;
	}

	return was_changed;
}