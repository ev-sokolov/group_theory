#ifndef FG_ABELIANGROUP_H
#define FG_ABELIANGROUP_H
#include "ContainerGroup.h"
#include <vector>

class FG_AbelianGroup : public ContainerGroup //класс для конечно порожд аг
{
public:
	typedef vector<int> FG_AbelianGroupElement; 
private:
	FG_AbelianGroupElement _order; //поле для вектора степеней
public:
	FG_AbelianGroup(FG_AbelianGroupElement order, char elem_symbol);//конструктор
	FG_AbelianGroupElement GetOrders() const; //метод для получения степеней
	FG_AbelianGroupElement ToFG_AbelianGroupElement(const GroupElement &elem) const; 
	//конвертер GE в FG_AbelianGroupElement
	bool WordIsEqualTo1(const GroupElement& input_value) const; // проверка слова на равенство с единицей
	bool WordsAreConjugate(const GroupElement& left_value, const GroupElement& right_value) const; // алгоритм решения проблемы сопряженности
	Mask GetMask() const;
	bool IsContain(const Symbol& input_value) const;
	BufferTex ConvertingWordToElementRecord(const GroupElement& input_value) const;

private:
	Mask _mask;
	// Вывод данных
	char _elem_symbol;
};
#endif // FG_ABELIANGROUP_H
