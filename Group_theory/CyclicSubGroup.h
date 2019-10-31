#ifndef CYCLICSUBGROUP_H
#define CYCLICSUBGROUP_H
#include "SubGroup.h"

typedef int ElementDegree;
const ElementDegree UndefinedDegree = 1 << (sizeof(ElementDegree) * 8 - 1); 
// для отображения неопределенной степени

class CyclicSubGroup : public SubGroup 
{
public:
	const ContainerGroup *Group; //поле
	const GroupElement Element; //порожд элем
public:
	CyclicSubGroup(const GroupElement &g);//конструктор
	const GroupElement &GetGenerating() const; //метод получения порождающего элемент
	bool IsContain(const GroupElement& input_value) const; //содержится ли элемент в подгруппе или нет.
	virtual const ElementDegree GetPower(const GroupElement &_elem, ElementDegree MaxDegree = UndefinedDegree) const;//находит степень в которую нужно возвести Element
	virtual const GroupElement powerElement(ElementDegree p) const;//метод для возведения порожд элемента в степень
	
};
#endif // CYCLICSUBGROUP_H
