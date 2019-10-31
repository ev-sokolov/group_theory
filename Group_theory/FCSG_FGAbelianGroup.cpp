#include "FCSG_FGAbelianGroup.h"
FCSG_FGAbelianGroup::FCSG_FGAbelianGroup(const GroupElement &g)
: SubGroup(g.GetGroup()), CyclicSubGroup(g), FiniteCyclicSubGroup(g), FG_AbelianGroupCSG(g) {} //конструктор