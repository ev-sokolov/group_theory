#include "SubGroupIzomorphizm.h"

SubGroupIzomorphizm::SubGroupIzomorphizm(const SubGroup *_domain, const SubGroup *_image)
	: domain(_domain), image(_image) {
	if(!(_domain->GetGroup())) throw GP_Exception(); //���� �� ����� ���������, �� ����������
	if(!(_image->GetGroup())) throw GP_Exception(); //���� �� ����� ���������, �� ����������
}
const SubGroup *SubGroupIzomorphizm::GetIzomorphizmDomain() const {
	return domain; //������������ ��������
}

const SubGroup *SubGroupIzomorphizm::GetIzomorphizmImage() const {
	return image; //������������ ��������
}
GroupElement SubGroupIzomorphizm::ImageOf(const GroupElement &elem) const {
	if (elem.GetGroup() != domain->GetGroup()) throw GP_Exception(); 
	//���� ������ ���������� �� ��������� ������� �����������, �� ����������
	return elem; 
}
GroupElement SubGroupIzomorphizm::preImageOf(const GroupElement &elem) const {
	if (elem.GetGroup() != image->GetGroup()) throw GP_Exception();
	//���� ������ ���������� �� ��������� ������� �����������, �� ����������
	return elem; 
}

