
#ifndef CONTAINERGROUP_H
#define CONTAINERGROUP_H
#include <vector>

#include "Mask.h"
#include "Symbol.h"
#include "Word.h"
#include "GroupElement.h"
#include "InOut_put.h"
using namespace std;

class GroupElement;

class ContainerGroup
{
public:
	ContainerGroup() {};
	~ContainerGroup() {};

	// Алгоритмы решения проблем тождества и сопряженности
	virtual bool WordIsEqualTo1(const GroupElement&) const = 0;                 // проверка слова на равенство с единицей
	bool WordsAreEqual(const GroupElement&, const GroupElement&) const;					// проверка на слов на равенство
	virtual bool WordsAreConjugate(const GroupElement&, const GroupElement&) const = 0; // проверка слов на сопряженность

	// Идентификация элементов
	virtual Mask GetMask() const = 0;
	virtual bool IsContain(const Symbol&) const = 0;

	// Вывод данных
	virtual BufferTex ConvertingWordToElementRecord(const GroupElement& input_value) const = 0;
};

#endif // CONTAINERGROUP_H