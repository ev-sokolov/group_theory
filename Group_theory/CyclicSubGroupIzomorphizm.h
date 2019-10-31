#ifndef CYCLICSUBGROUPIZOMORPHIZM_H
#define CYCLICSUBGROUPIZOMORPHIZM_H
#include "SubGroupIzomorphizm.h"
#include "CyclicSubGroup.h"
class CyclicSubGroupIzomorphizm : public SubGroupIzomorphizm
{

public:
	CyclicSubGroupIzomorphizm(const CyclicSubGroup *_domain, const CyclicSubGroup *_image); //�����������
	GroupElement ImageOf(const GroupElement &elem) const;   //���������� ������ ��������
	GroupElement preImageOf(const GroupElement &elem) const; //���������� ��������� ��������
};

#endif // CYCLICSUBGROUPIZOMORPHIZM_H