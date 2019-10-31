#include "GroupElement.h"

GroupElement::GroupElement(const Word& w, const ContainerGroup* g) :Word(w), Group(g) {
		for (const_iterator iter = w.begin(); iter != w.end(); ++iter) {
			if (!(g->IsContain(*iter))) GP_Exception();

		}
		
}

GroupElement GroupElement::operator*(const GroupElement &right_value) const 
{
	if (this->Group != right_value.Group) throw;
	GroupElement buffer = *this;
	for (auto it : right_value)
		buffer.emplace_back(it);

	return buffer;
}

GroupElement GroupElement::GetInverse() const
{
	GroupElement inverse_word(Word(), this->Group);

	for (auto it_word : *this)
	inverse_word.emplace_front(it_word.GetInverse());

	return inverse_word;
}
