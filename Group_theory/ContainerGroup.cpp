#include "ContainerGroup.h"

bool ContainerGroup::WordsAreEqual(const GroupElement& left_value, const GroupElement& right_value) const
{
	return WordIsEqualTo1(left_value*right_value.GetInverse());
}