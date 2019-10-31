#ifndef CYCLICSUBGROUPIZOMORPHIZM_H
#define CYCLICSUBGROUPIZOMORPHIZM_H
#include "SubGroupIzomorphizm.h"
#include "CyclicSubGroup.h"
class CyclicSubGroupIzomorphizm : public SubGroupIzomorphizm
{

public:
	CyclicSubGroupIzomorphizm(const CyclicSubGroup *_domain, const CyclicSubGroup *_image); //конструктор
	GroupElement ImageOf(const GroupElement &elem) const;   //вычисление образа элемента
	GroupElement preImageOf(const GroupElement &elem) const; //вычисления прообраза элемента
};

#endif // CYCLICSUBGROUPIZOMORPHIZM_H