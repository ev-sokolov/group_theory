#include "FiniteCyclicSubGroup.h"

FiniteCyclicSubGroup::FiniteCyclicSubGroup(const GroupElement& g) : SubGroup(g.GetGroup()), FiniteSubGroup(g.GetGroup()), CyclicSubGroup(g) {
	//if (dynamic_cast<const FiniteCyclicSubGroup*>(g.GetGroup()) == 0) throw GP_Exception();
}//конструктор

GroupElement FiniteCyclicSubGroup::FirstElem() const {
	return GetGenerating();//возвращаемое значение
}

bool FiniteCyclicSubGroup::NextElem(GroupElement &u) const {
	u = u * GetGenerating();
	if (u.GetGroup()->WordIsEqualTo1(u)) return false;
	else return true;
}