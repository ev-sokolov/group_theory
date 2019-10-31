#ifndef FINITECYCLICSUBGROUP
#define FINITECYCLICSUBGROUP
#include "FiniteSubGroup.h"
#include "CyclicSubGroup.h"
#include "GroupElement.h"

class FiniteCyclicSubGroup : public FiniteSubGroup, public CyclicSubGroup
{
public:
	FiniteCyclicSubGroup(const GroupElement& g);
	GroupElement FirstElem();
	bool NextElem(GroupElement &u);
};
#endif //FINITECYCLICSUBGROUP