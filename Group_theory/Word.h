#ifndef WORD_H
#define WORD_H

#include "Symbol.h"
#include "Mask.h"
#include <list>

using std::list;


typedef list<Symbol> ListOfSymbols;

class Word : public ListOfSymbols
{
public:
	Word(ListOfSymbols input_value = ListOfSymbols());
	~Word() {};

	bool operator== (const Word& right_value) const;
	bool operator!= (const Word& right_value) const;
		
	Word GetSubWord(const_iterator subword_begin, const_iterator subword_end) const; // возвращает подслово из this начинающиеся с subword_begin и до subword_end включительно

	iterator DeleteSubWord(iterator subword_begin, iterator subword_end); // удаляет из this слово начинающиеся с subword_end и до subword_end включительно
	bool DeleteTrivials();                                                // удаляет из this все слова, тривиально равные единицы 
};

#endif // WORD_H