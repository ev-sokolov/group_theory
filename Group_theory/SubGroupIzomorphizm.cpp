#include "SubGroupIzomorphizm.h"

SubGroupIzomorphizm::SubGroupIzomorphizm(const SubGroup *_domain, const SubGroup *_image)
	: domain(_domain), image(_image) {
	if(!(_domain->GetGroup())) throw GP_Exception(); //если не имеет подгруппы, то исключение
	if(!(_image->GetGroup())) throw GP_Exception(); //если не имеет подгруппы, то исключение
}
const SubGroup *SubGroupIzomorphizm::GetIzomorphizmDomain() const {
	return domain; //возвращаемое значение
}

const SubGroup *SubGroupIzomorphizm::GetIzomorphizmImage() const {
	return image; //возвращаемое значение
}
GroupElement SubGroupIzomorphizm::ImageOf(const GroupElement &elem) const {
	if (elem.GetGroup() != domain->GetGroup()) throw GP_Exception(); 
	//если группа отличается от подгруппы области определения, то исключение
	return elem; 
}
GroupElement SubGroupIzomorphizm::preImageOf(const GroupElement &elem) const {
	if (elem.GetGroup() != image->GetGroup()) throw GP_Exception();
	//если группа отличается от подгруппы области определения, то исключение
	return elem; 
}

