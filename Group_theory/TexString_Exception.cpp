#include "TexString_Exception.h"

TexString_Exception::TexString_Exception(const string & input_value, int pos, TS_ExceptionCode code): 
	_input_string(input_value), _error_pos(pos), _error_code(code)
{
	DisplayErrorMassage();
}

void TexString_Exception::DisplayErrorMassage()
{
	cout << "Syntax Error\n" 
		 << _input_string << endl
		 << setw(_error_pos + 1) << '^' << endl;

	cout << "Expected: ";

	switch (_error_code)
	{
	case TexString_UnexpectedData:
		cout << "Symbol or {}_^,-0123456789";
		break;
	
	case Index_UnexpectedData:
		cout << ",0123456789";
		break;
	case Index_IncorrectData:
		cout << "Null or posetiv number";
		break;
	case Index_Brackets_Empty:
		cout << ",0123456789";
		break;
	case Index_Brackets_Begin:
		cout << "{";
		break;
	case Index_Brackets_End:
		cout << "}";
		break;

	case Power_UnexpectedData:
		cout << "{}-0123456789";
		break;
	case Power_Brackets_Empty:
		cout << "-0123456789";
		break;
	case Power_Brackets_End:
		cout << "}";
		break;

	case Number_OutOfLimits:
		cout << "The number lying in the interval from " << INT_MIN << "to" << INT_MAX;
		break;
	
	default:
		assert("How did you get here?");
		break;
	}

	cout << endl;
	
	cout << "Got: " << _input_string[_error_pos] << endl;
}
