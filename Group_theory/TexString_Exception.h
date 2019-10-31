#ifndef TEXSTRING_EXCEPTION_H
#define TEXSTRING_EXCEPTION_H

#include <exception>
#include <iomanip>
#include <string>
#include <iostream>
#include <assert.h>
using namespace std;

enum TS_ExceptionCode {
	TexString_UnexpectedData = 1,

	Index_UnexpectedData = 100,
	Index_IncorrectData = 101,
	Index_Brackets_Empty = 102,
	Index_Brackets_Begin = 103,
	Index_Brackets_End = 104,

	Power_UnexpectedData = 200,
	Power_Brackets_Empty = 201,
	Power_Brackets_End = 202,
	
	Number_OutOfLimits = 300,
};

class TexString_Exception : public std::exception
{
public:
	TexString_Exception(const string& input_value, int pos, TS_ExceptionCode code);
	~TexString_Exception() {};

protected:
	void DisplayErrorMassage();

private:
	const string& _input_string;
	int _error_pos;
	TS_ExceptionCode _error_code;
};

#endif // TEXSTRING_EXCEPTION_H