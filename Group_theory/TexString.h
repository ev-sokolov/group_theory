#ifndef TEXSTRING_H
#define TEXSTRING_H

#include <string>
#include <list>
#include <iostream>

#include "TexString_Exception.h"

using namespace std;

typedef char SymbolType;

struct ElementRecord
{
	SymbolType symbol;
	list<int> index;
	int power;
};

typedef list<ElementRecord> BufferTex;

class TexString
{
protected:
	struct TexSyllable
	{
		int _pos_begin;		  // начало слога 
		int _pos_end;		  // конец слога
		int _pos_index_beign; // начало индекса
		int _pos_index_end;   // конец индекса
		int _pos_power_begin; // начало степени
		int _pos_power_end;   // конец степени

		TexSyllable(int pos_begin = -1, int pos_end = -1, 
					int pos_index_beign = -1, int pos_index_end = -1, 
					int pos_power_begin = -1, int pos_power_end = -1) :
			_pos_begin(pos_begin), _pos_end(pos_end), 
			_pos_index_beign(pos_index_beign), _pos_index_end(pos_index_end), 
			_pos_power_begin(pos_power_begin), _pos_power_end(pos_power_end)
		{}
	};

public:
	TexString(const string& InputString);
	~TexString() {};

	BufferTex ConvertToBufferTex();
	
protected:
	bool TexSyntaxCheker(list<TexSyllable>::iterator itr_Syllable);

	int Parser_Index(int pos_begin) const;
	int Parser_Power(int pos_begin) const;
	int Parser_Number(int pos_begin) const;

private:
	list<TexSyllable> _Syllables;
	string _InputString;
};
#endif

