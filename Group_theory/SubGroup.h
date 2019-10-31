#ifndef SUBGROUP
#define SUBGROUP
#include "ContainerGroup.h"
#include "GroupElement.h"
#include "Word.h"
class SubGroup 
{
	const ContainerGroup *Group; //поле
public: 
	
	SubGroup(const ContainerGroup*);//конструктор
	const ContainerGroup *GetGroup() const;//возвращает значение поля Group
	virtual bool IsContain(const GroupElement& input_value) const = 0;//содержится ли элемент в подгруппе или нет.
	
};
#endif // SUBGROUP