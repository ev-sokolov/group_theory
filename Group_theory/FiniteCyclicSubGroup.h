#ifndef FINITECYCLICSUBGROUP
#define FINITECYCLICSUBGROUP
#include "FiniteSubGroup.h"
#include "CyclicSubGroup.h"
#include "GroupElement.h"

class FiniteCyclicSubGroup : public FiniteSubGroup, virtual public CyclicSubGroup
{
public:
	FiniteCyclicSubGroup(const GroupElement& g);
	GroupElement FirstElem() const;
	bool NextElem(GroupElement &u) const;
};
#endif //FINITECYCLICSUBGROUP