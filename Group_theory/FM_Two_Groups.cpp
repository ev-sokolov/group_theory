#include "FM_Two_Groups.h"
#include "SubGroup.h"
#include "FiniteSubGroup.h"

FM_Two_Groups::FM_Two_Groups(SubGroupIzomorphizm *_phi) : phi(_phi)
{

	_max_units_number = GetA()->GetMask().GetUnitsNumber(); 
	if (GetB()->GetMask().GetUnitsNumber() > _max_units_number)
		_max_units_number = GetB()->GetMask().GetUnitsNumber();

	_coding_units = 2;
	_freeproduct_mask.GenerateMask(0, _max_units_number + _coding_units);
	_extraction_factor_number_mask.GenerateMask(_max_units_number, _coding_units);
}

Mask FM_Two_Groups::GetMask() const
{
	return _freeproduct_mask;
}

unsigned int FM_Two_Groups::GetMaxUnitsNumber() const
{
	return _max_units_number;
}

unsigned int FM_Two_Groups::GetCodingUnits() const
{
	return _coding_units;
}

bool FM_Two_Groups::IsContain(const Symbol& input_value) const
{
	try
	{
		const ContainerGroup *result = GetGroupAddress(input_value);
		return result->IsContain(input_value);
	}
	catch (GP_Exception())
	{
		return false;
	};
}

Bitset FM_Two_Groups::GetGroupNumber(const Symbol& input_value) const
{
	ID result = input_value;

	result = result & (_extraction_factor_number_mask);
	result = result >> _max_units_number;

	if (result.GetValue() - 1 > 1)
		throw GP_Exception();
	//return result.GetValue();
	return (Bitset)result.GetValue();

	}

GroupElement FM_Two_Groups::StandartImageOf(const GroupElement& input_value) const
{
	Word buffer(input_value);
	Bitset group_id = 0;
	if (input_value.GetGroup() == GetA()) group_id = 1;
	else if (input_value.GetGroup() == GetB()) group_id = 2;
	else throw GP_Exception();

	for (auto i = buffer.begin(); i != buffer.end(); ++i)
	{
		ID temp = *i;
		temp = temp & (~(ID(Bitset(3)) << (this->GetMaxUnitsNumber())));
		temp = temp | (ID(group_id) << (this->GetMaxUnitsNumber()));
		*i = temp;
	}

	return GroupElement(buffer,this);

}
const ContainerGroup *FM_Two_Groups::GetA() const {
	return phi->GetIzomorphizmDomain()->GetGroup(); //возвращаем указатель на группу phi, от поля domain 
}
const ContainerGroup *FM_Two_Groups::GetB() const {
	return phi->GetIzomorphizmImage()->GetGroup();//возвращаем указатель на группу phi, от поля image 
}
const ContainerGroup *FM_Two_Groups::GroupIDtoGroupPointer(Bitset id) const {
	if (id == 1) return GetA(); //если id=1, то А
	if (id == 2) return GetB(); //если id=2, то B
	throw GP_Exception(); //иначе исключение
}
Bitset FM_Two_Groups::GroupPointertoGroupID(const ContainerGroup *p) const {
	if (p == GetA()) return 1; //если p=A возвращаем 1
	if (p == GetB()) return 2; //если p=B возвращаем 2
	throw GP_Exception(); //иначе исключение
}
const ContainerGroup *FM_Two_Groups::GetGroupAddress(const Symbol& input_value) const{
	if (GetGroupNumber(input_value) == 1) return GetA(); //если номер группы=1 возвращаем А
	if (GetGroupNumber(input_value) == 2) return GetB(); //если номер группы=2 возвращаем В
	throw GP_Exception(); //иначе исключение
}

const ContainerGroup *FM_Two_Groups::GetMultiplier(const GroupElement &input_value) const {
	return GetGroupAddress(*(input_value.begin())); //возвращаем адрес свободного множителя 
}

 GroupElement FM_Two_Groups::ListOfSyllablesToElement(const list<GroupElement> &l) const {
	GroupElement t= *(l.begin());//элемент t равный первому слогу
	for (list<GroupElement>::const_iterator iter = l.begin()++; iter != l.end(); ++iter) {
		t = t * *iter;//умножаем t на все элементы списка
	}
	return t;//получаем элемент
}

list<GroupElement> FM_Two_Groups::ListOfSyllablesOf(const GroupElement& input_value) const {
	if (input_value.GetGroup() != this) throw GP_Exception();//если группа не найдена, то исключение
		list<GroupElement> syliables; //создаем список

		if (input_value.size() == 0) 
			return syliables;

		auto word_iterator = input_value.begin(); 
		unsigned int current_group_id = this->GetGroupNumber(*word_iterator); 

		auto _begin = word_iterator;
		auto _end = word_iterator;

		++word_iterator;

		for (; word_iterator != input_value.end();)
		{
			unsigned int new_group_id = this->GetGroupNumber(*word_iterator);

			if (current_group_id == new_group_id)
			{
				++word_iterator;
			}
			else
			{
				_end = word_iterator;
				--_end;
				Word sub_word = input_value.GetSubWord(_begin, _end);
				GroupElement ge = StandartImageOf(GroupElement(sub_word, GroupIDtoGroupPointer(current_group_id)));
				syliables.emplace_back(ge);

				_begin = word_iterator;
				current_group_id = new_group_id;

				++word_iterator;
			}
		}
		_end = word_iterator;
		--_end;
		Word sub_word = input_value.GetSubWord(_begin, _end);
		GroupElement ge = StandartImageOf(GroupElement(sub_word, GroupIDtoGroupPointer(current_group_id)));
		syliables.emplace_back(ge);

		return syliables;
}

list<GroupElement> FM_Two_Groups::ReducedFormOf(const GroupElement& _elem) const { //алгоритм XI
	list<GroupElement> elem_syllables = ListOfSyllablesOf(_elem);// создаем список
	bool flag; //флажок
	do {
		if (elem_syllables.size() == 1) return elem_syllables; //если размер=1 возвращаем список
		flag = false;
		for (list<GroupElement>::iterator iter = elem_syllables.begin(); iter != elem_syllables.end(); ++iter) {
			const ContainerGroup *syllable_group = GetMultiplier(*iter); //создаем группу по её первому слогу
			GroupElement syllable_elem = GroupElement(*iter, syllable_group);
			if (syllable_group == GetA()) { //если A, то
				if (phi->GetIzomorphizmDomain()->IsContain(syllable_elem)) { //если указатель на группу phi от поля domain, то
					flag = true; // флаг в истину
					*iter = StandartImageOf(phi->ImageOf(syllable_elem)); //преобразовываем итератор
					list<GroupElement>::iterator itern = iter; itern++; // создаем новый итератор равный текущему итератору
					if (itern != elem_syllables.end()) { //если новый итератор указывает на конец списка, то
						*iter = *iter * *itern; //старый итератор умножаем на новый
						elem_syllables.erase(itern); //стираем новый итератор в списке 
//						itern = iter; //присваиваем новому итератору значение старого
					} 
					if (iter != elem_syllables.begin()) { // если итератор указывает на начало списка, то
						itern = iter; iter--; //шаг назад

						//предположительно берется iter == elem_syllables.begin()+1, далее мы берём iter--
						//через дебаг поступает странное значение itern

						//cout << "itern= " << /*itern->size() <<*/ endl;
						

						*iter = *iter * *itern; //старый итератор умножаем на новый
						elem_syllables.erase(itern); //стираем новый итератор в списке 
//						itern = iter; //присваиваем новому итератору значение старого
					}
				}
			}
			else if (syllable_group == GetB()) { //тоже самое для B
				if (phi->GetIzomorphizmImage()->IsContain(syllable_elem)) {
					flag = true;
					*iter = StandartImageOf(phi->preImageOf(syllable_elem));
					list<GroupElement>::iterator itern = iter; itern++;
					if (itern != elem_syllables.end()) {
						*iter = *iter * *itern;
						elem_syllables.erase(itern);
//						itern = iter;
					}
					if (iter != elem_syllables.begin()) {
						itern = iter; iter--;
						*iter = *iter * *itern;
						elem_syllables.erase(itern);
//						itern = iter;
					}
				}
			}
		}
	} while (flag == true);
	cout << "слово несократимо\n";
	
	return elem_syllables; //возвращаем получившийся список
}

bool FM_Two_Groups::WordIsEqualTo1(const GroupElement &_elem) const {//CI
	list<GroupElement> elem_syllables = ReducedFormOf(_elem); //приводим к несократимой форме
	if (elem_syllables.size() > 1) return false; //если размер больше 1, то false
	else return GetMultiplier(*(elem_syllables.begin()))->WordIsEqualTo1(
		GroupElement(*(elem_syllables.begin()), GetMultiplier(*(elem_syllables.begin())))
		);
	//иначе возвращаем метод GetMultiplier от начала списка
}

list<GroupElement> FM_Two_Groups::CyclicallyReducedFormOf(const GroupElement& input_word) const {//XII
	list<GroupElement> w = ReducedFormOf(input_word);//приводим к несократимой форме
	do {
		if ((w.size() % 2 == 0) || (w.size() == 1)) {//если слово четно или равно 1
			cout << "Слово циклически приведено \n";
			return w;
		}
		else {
			list<GroupElement>::iterator iter = w.end();//итератор на конец слова
			iter--;//шаг назад
			*(w.begin()) = *(w.begin()) * *iter;//умножаем начало на последний слог
			w.erase(iter);//стираем последний слог
			if (GetMultiplier(*(w.begin()))->WordIsEqualTo1(*(w.begin())))
				w.erase(w.begin());//стираем начальный слог
		}
	} while (true);
}

bool FM_Two_Groups::WordsAreConjugate(const GroupElement &u, const GroupElement &v) const { //CII
	const FiniteSubGroup *H = dynamic_cast<const FiniteSubGroup*>(phi->GetIzomorphizmDomain()); //указатель на поле с подгруппой H
	const FiniteSubGroup *K = dynamic_cast<const FiniteSubGroup*>(phi->GetIzomorphizmImage()); //указатель на поле с подгруппой K
	if (H == 0 || K == 0) throw;//если подгруппы пустые, то исключение
	list<GroupElement> u1 = CyclicallyReducedFormOf(u); //приводим слова u и v к циклически несократимому виду
	list<GroupElement> v1 = CyclicallyReducedFormOf(v);
	for (unsigned int i = 0; i < v1.size(); i++) { //цикл по v1
		GroupElement h = H->FirstElem(); //указатель на первый элемент
		do {
			GroupElement h1 = StandartImageOf(h); //приводим слово к нормальному виду
			if (WordsAreEqual(h1.GetInverse()*ListOfSyllablesToElement(v1)*h1, ListOfSyllablesToElement(u1))) return true;
			//если слова равны, то возвращаем правду
		} while (H->NextElem(h));
		v1.emplace_back(*(v1.begin())); //создаем объект в конце 
		v1.erase(v1.begin()); //стираем начало
	}
	return false;
}

BufferTex FM_Two_Groups::ConvertingWordToElementRecord(const GroupElement& input_value) const
{
	BufferTex Result;
	BufferTex Temp;

	GroupElement BufferWord = input_value;
	while (BufferWord.DeleteTrivials());
	list<GroupElement> syllables_words = ListOfSyllablesOf(BufferWord);

	auto it = Result.end();

	for (auto it_syllable : syllables_words)
	{
		//Word Subword = BufferWord.GetSubWord(it_syllable._begin, it_syllable._end);
		Temp = it_syllable.GetGroup()->ConvertingWordToElementRecord(it_syllable);

		for (auto& it_temp : Temp)
			it_temp.index.push_back(GroupPointertoGroupID(GetMultiplier(it_syllable)));

		Result.splice(it, Temp);
		Temp.clear();
	}
	return Result;
}
