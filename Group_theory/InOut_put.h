#ifndef INOUT_PUT
#define INOUT_PUT

#include <list>
#include <string>

#include "TexString.h"
#include "Word.h"

// Ввод данных
Word ConvertingTexToWord(TexString input_value);

// Вывод данных
string ConvertingBufferTexToTex(const BufferTex& input_value);
list<int> ReducingSimilarTerms(Word& InputValue);
#endif // INOUT_PUT