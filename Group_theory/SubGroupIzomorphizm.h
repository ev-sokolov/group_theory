#ifndef SUBGROUPIZOMORPHIZM
#define SUBGROUPIZOMORPHIZM
#include "SubGroup.h"

class SubGroupIzomorphizm
{
	const SubGroup *domain;  //поле domain
	const SubGroup *image;  //поле image
public:
	SubGroupIzomorphizm(const SubGroup *_domain, const SubGroup *_image); //конструктор
	const SubGroup *GetIzomorphizmDomain() const; //возвращает поле domain
	const SubGroup *GetIzomorphizmImage() const; //возвращает поле image
	virtual GroupElement ImageOf(const GroupElement &elem) const = 0;   //вычисление образа элемента
	virtual GroupElement preImageOf(const GroupElement &elem) const = 0; //вычисление прообраза элемента
};
#endif // SUBGROUPIZOMORPHIZM
