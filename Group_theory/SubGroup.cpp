#include "SubGroup.h"
#include "GroupElement.h"

SubGroup::SubGroup(const ContainerGroup* g): Group (g) {//�����������

}

const ContainerGroup *SubGroup::GetGroup() const {
	return Group;//���������� ��������
}

bool SubGroup::IsContain(const GroupElement& input_value) const
{
	if (input_value.GetGroup() != Group) throw;//�������� �� ������� � ���������
	return true;
}
