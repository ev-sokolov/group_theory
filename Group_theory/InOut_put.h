#ifndef INOUT_PUT
#define INOUT_PUT

#include <list>
#include <string>

#include "TexString.h"
#include "Word.h"

// ���� ������
Word ConvertingTexToWord(TexString input_value);

// ����� ������
string ConvertingBufferTexToTex(const BufferTex& input_value);
list<int> ReducingSimilarTerms(Word& InputValue);
#endif // INOUT_PUT