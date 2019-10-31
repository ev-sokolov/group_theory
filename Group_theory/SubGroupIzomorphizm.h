#ifndef SUBGROUPIZOMORPHIZM
#define SUBGROUPIZOMORPHIZM
#include "SubGroup.h"

class SubGroupIzomorphizm
{
	const SubGroup *domain;  //���� domain
	const SubGroup *image;  //���� image
public:
	SubGroupIzomorphizm(const SubGroup *_domain, const SubGroup *_image); //�����������
	const SubGroup *GetIzomorphizmDomain() const; //���������� ���� domain
	const SubGroup *GetIzomorphizmImage() const; //���������� ���� image
	virtual GroupElement ImageOf(const GroupElement &elem) const = 0;   //���������� ������ ��������
	virtual GroupElement preImageOf(const GroupElement &elem) const = 0; //���������� ��������� ��������
};
#endif // SUBGROUPIZOMORPHIZM
