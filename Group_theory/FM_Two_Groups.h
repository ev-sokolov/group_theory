#ifndef FM_TWO_GROUPS_H
#define FM_TWO_GROUPS_H
#include "SubGroupIzomorphizm.h"
#include "FiniteSubGroup.h"

class FM_Two_Groups : public ContainerGroup
{
	SubGroupIzomorphizm *phi; //поле 
public:
	FM_Two_Groups(SubGroupIzomorphizm *_phi);//конструктор
	
	list<GroupElement> ReducedFormOf(const GroupElement& input_word) const; // приведение слова к несократимой форме
	list<GroupElement> CyclicallyReducedFormOf(const GroupElement& input_word) const;//приведение слова к циклически несократимому
	bool WordIsEqualTo1(const GroupElement&) const; //алгоритм CI
	bool WordsAreConjugate(const GroupElement&, const GroupElement&) const; //алгоритм CII

	Mask GetMask() const;//получение маски элемента
	bool IsContain(const Symbol& input_value) const; // проверяет символ input_value на принадлежность группе 
	GroupElement StandartImageOf(const GroupElement& input_value) const; // интерпретирование слова input_value, как элемента свободного произведения

	const ContainerGroup *GetA() const; //получение  A
	const ContainerGroup *GetB() const; //получение  B
	
	const ContainerGroup *GetGroupAddress(const Symbol& input_value) const;  //возващает адресс свободного множителя по её номеру (id)
	GroupElement ListOfSyllablesToElement(const list<GroupElement> &l) const;  //перевести список слогов в элемент 
	list<GroupElement> ListOfSyllablesOf(const GroupElement& input_value) const;  //перевести элемент в произведение слогов
	BufferTex FM_Two_Groups::ConvertingWordToElementRecord(const GroupElement& input_value) const;

protected:
	// Идентификация элементов
	Bitset GetGroupNumber(const Symbol& input_value) const; // возвращает номер группы которой принадлежит input_value
	unsigned int GetMaxUnitsNumber() const;
	unsigned int GetCodingUnits() const;

private:
	const ContainerGroup *GroupIDtoGroupPointer(Bitset id) const;//получение адреса свободного множителя по его id 
	Bitset GroupPointertoGroupID(const ContainerGroup *p) const; //принимает адрес свободного множителя возвращает id
	const ContainerGroup *GetMultiplier(const GroupElement &input_value) const;
	// Идентификация элементов
	Mask _freeproduct_mask;              // маска свободного произведения
	Mask _extraction_factor_number_mask; // маска для извлечения id группы
	unsigned int _max_units_number;		 // максимальное количество единиц из масок алфавитов 
	unsigned int _coding_units;          // количество единиц, нужных для кодирования множителей свободного произведения 
};

#endif // FM_TWO_GROUPS_H
