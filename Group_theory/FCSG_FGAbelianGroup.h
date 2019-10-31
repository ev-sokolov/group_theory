#ifndef FCSG_FGABELIANGROUP_H
#define FCSG_FGABELIANGROUP_H
#include "FiniteCyclicSubGroup.h"
#include "FG_AbelianGroupCSG.h"

class FCSG_FGAbelianGroup : public FiniteCyclicSubGroup, public FG_AbelianGroupCSG
{
public:
	FCSG_FGAbelianGroup(const GroupElement &g);//конструктор
	
};
#endif // FCSG_FGABELIANGROUP_H