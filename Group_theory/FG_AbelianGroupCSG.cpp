#include "FG_AbelianGroupCSG.h" 
FG_AbelianGroupCSG::FG_AbelianGroupCSG(const GroupElement &g) : SubGroup(g.GetGroup()), CyclicSubGroup(g)
{
	if (dynamic_cast<const FG_AbelianGroup*>(g.GetGroup()) == 0) throw GP_Exception(); 
}//если не имеет подгруппы, то исключение

const ElementDegree FG_AbelianGroupCSG::GetPower(const GroupElement &_elem, ElementDegree MaxDegree) const {
	if (_elem.GetGroup() != this->GetGroup()) throw GP_Exception();
	const FG_AbelianGroup *gr = dynamic_cast<const FG_AbelianGroup*>(_elem.GetGroup());
	FG_AbelianGroup::FG_AbelianGroupElement u = gr->ToFG_AbelianGroupElement(_elem);
	FG_AbelianGroup::FG_AbelianGroupElement v = gr->ToFG_AbelianGroupElement(GetGenerating());
	FG_AbelianGroup::FG_AbelianGroupElement order = (dynamic_cast<const FG_AbelianGroup*>(this->GetGroup()))->GetOrders();//?
	ElementDegree result = UndefinedDegree;
	for (unsigned int i = 0; i < order.size(); i++) {
		if (order[i] == 0) {
			if (v[i] == 0 && u[i] != 0) return UndefinedDegree;
			if (v[i] != 0 && u[i] != 0)
				if (u[i] % v[i] != 0) return UndefinedDegree;
				else
					if (result == UndefinedDegree) result = u[i] / v[i];
					else if (result != UndefinedDegree && result != (u[i] / v[i])) return UndefinedDegree;
			if (v[i] != 0 && u[i] == 0)
				if (result == UndefinedDegree) result = 0;
				else if (result != 0) return UndefinedDegree;
		}
	}
	if (result == UndefinedDegree) {
		ElementDegree d = 1;
		for (unsigned int i = 0; i < order.size(); i++) 
			if (order[i] != 0) d *= order[i];
		for (unsigned int p = 0; p < d; p++) {
			FG_AbelianGroup::FG_AbelianGroupElement vp;
			for (unsigned int i = 0; i < vp.size(); i++) {
				vp[i] = v[i] * p;
				if (order[i] != 0) vp[i] %= order[i];
			}
			bool res = true;
			for (unsigned int i = 0; i < vp.size(); i++)
				if (vp[i] != u[i]) res = false;
			if (res) return p;
		}
		//return CyclicSubGroup::GetPower(_elem, d);
	}
	for (unsigned int i = 0; i < order.size(); i++) {
		ElementDegree d = v[i] * result - u[i];
		d = d < 0 ? -d : d;
		if ((d % order[i]) != 0) return UndefinedDegree;
	}	
}
