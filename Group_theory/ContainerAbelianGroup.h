
#include <algorithm>
#include "ContainerGroup.h"
#include <iostream>


class ContainerAbelianGroup : public ContainerGroup
{
public:
	ContainerAbelianGroup(unsigned int gen_num, char elem_symbol);
	~ContainerAbelianGroup() {};

	// Алгоритмы решения проблем тождества и сопряженности
	bool WordIsEqualTo1(const GroupElement& input_value) const;                            // проверка слова на равенство с единицей
	bool WordsAreConjugate(const GroupElement& left_value, const GroupElement& right_value) const; // алгоритм решения проблемы сопряженности

	// Идентификация элементов
	Mask GetMask() const;
	bool IsContain(const Symbol& input_value) const;

	// Вывод данных
	BufferTex ConvertingWordToElementRecord(const GroupElement& input_value) const;

private:
	bool SymbolsCompare(const Symbol& left_vale, const Symbol& right_value) const;
	Word Sort(Word& input_value) const;
	
private:
	unsigned int _gen_num; // количество порождающих
	Mask _mask;

	// Вывод данных
	char _elem_symbol;
};