#include "SubGroup.h"
#include "GroupElement.h"

SubGroup::SubGroup(const ContainerGroup* g): Group (g) {//абстрактный

}

const ContainerGroup *SubGroup::GetGroup() const {
	return Group;//возвращаем значение
}

bool SubGroup::IsContain(const GroupElement& input_value) const
{
	if (input_value.GetGroup() != Group) throw;//проверка на наличие в подгруппе
	return true;
}
