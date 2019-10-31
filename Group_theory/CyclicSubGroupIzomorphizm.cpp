#include "CyclicSubGroupIzomorphizm.h"
CyclicSubGroupIzomorphizm::CyclicSubGroupIzomorphizm(const CyclicSubGroup *_domain, const CyclicSubGroup *_image)	
	: SubGroupIzomorphizm(_domain, _image)//конструктор
{}


GroupElement CyclicSubGroupIzomorphizm::ImageOf(const GroupElement &elem) const {
	if (elem.GetGroup() != GetIzomorphizmDomain()->GetGroup()) throw GP_Exception();
	//если группа отличается от подгруппы области определения, то исключение
	ElementDegree d = (dynamic_cast<const CyclicSubGroup*>(GetIzomorphizmDomain()))->GetPower(elem);
	if (d != UndefinedDegree)
		return (dynamic_cast<const CyclicSubGroup*>(GetIzomorphizmDomain()))->powerElement(d);
	else throw GP_Exception();
}

GroupElement CyclicSubGroupIzomorphizm::preImageOf(const GroupElement &elem) const {
	if (elem.GetGroup() != GetIzomorphizmImage()->GetGroup()) throw GP_Exception();
	//если группа отличается от подгруппы области определения, то исключение
	ElementDegree d = (dynamic_cast<const CyclicSubGroup*>(GetIzomorphizmImage()))->GetPower(elem);
	if (d != UndefinedDegree)
		return (dynamic_cast<const CyclicSubGroup*>(GetIzomorphizmImage()))->powerElement(d);
	else throw GP_Exception();
}

