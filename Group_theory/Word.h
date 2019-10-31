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
		
	Word GetSubWord(const_iterator subword_begin, const_iterator subword_end) const; // ���������� �������� �� this ������������ � subword_begin � �� subword_end ������������

	iterator DeleteSubWord(iterator subword_begin, iterator subword_end); // ������� �� this ����� ������������ � subword_end � �� subword_end ������������
	bool DeleteTrivials();                                                // ������� �� this ��� �����, ���������� ������ ������� 
};

#endif // WORD_H