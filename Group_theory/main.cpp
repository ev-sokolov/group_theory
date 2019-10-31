#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <clocale>
#include <iostream>
#include "Word.h"
#include "FG_AbelianGroup.h"
#include "FG_AbelianGroupCSG.h"
#include "FCSG_FGAbelianGroup.h"
#include "ContainerAbelianGroup.h"
#include "CyclicSubGroupIzomorphizm.h"
#include "FM_Two_Groups.h"
#include "GroupElement.h"

using namespace std;

void print_word(const Word &w) {
	for (Word::const_iterator iter = w.begin(); iter != w.end(); iter++)
		cout << iter->GetValue() << ' ';
	cout << endl;
}

int main()
{
	setlocale(LC_CTYPE, "rus");

	{

		FG_AbelianGroup::FG_AbelianGroupElement order(4);
		order[0] = 8;
		order[1] = 8;
		order[2] = 5;
		order[3] = 7;

		FG_AbelianGroup gr(order, 'a');

		string a1_input = "a_{1}^{3}a_{3}^{4}a_{2}^{2}a_{3}a_{1}^{-1}";
		cout << a1_input << endl;
		TexString a1_Tex_input(a1_input);
		Word a1_word = ConvertingTexToWord(a1_Tex_input);
		GroupElement a1_ge = GroupElement(a1_word, &gr);

		//SubGroup sg(a1_ge);
		CyclicSubGroup csg(a1_ge);
		FG_AbelianGroupCSG sgp(a1_ge);

		string a2_input = "a_{1}^{4}a_{3}^{4}a_{2}^{2}a_{3}a_{1}^{-3}";
		cout << a2_input << endl;
		TexString a2_Tex_input(a2_input);
		Word a2_word = ConvertingTexToWord(a2_Tex_input);
		GroupElement a2_ge = GroupElement(a2_word, &gr);

		string a3_input = "a_{1}^{4}a_{3}^{2}a_{2}^{2}a_{3}^{-2}a_{1}^{-4}a_{2}^{-2}";
		cout << a3_input << endl;
		TexString a3_Tex_input(a3_input);
		Word a3_word = ConvertingTexToWord(a3_Tex_input);
		GroupElement a3_ge = GroupElement(a3_word, &gr);

		//SubGroup sg2(a2_ge);
		CyclicSubGroup sg2(a2_ge);
		FG_AbelianGroupCSG sgp2(a2_ge);
		cout << endl;
		/*
			cout << "gr.WordsAreEqual(a1_ge, a1_ge): " << gr.WordsAreEqual(a1_ge, a1_ge) << endl;
			cout << "gr.WordsAreEqual(a1_ge, a2_ge): " << gr.WordsAreEqual(a1_ge, a2_ge) << endl;
			cout << endl;
			cout << "sg2.GetPower(a2_ge): " <<sg2.GetPower(a2_ge) << endl;
			cout << "sg2.IsContain(a2_ge): " <<sg2.IsContain(a2_ge) << endl;
			cout << endl;
			cout << "sg.GetPower(a1_ge): " <<sg.GetPower(a1_ge) << endl;
			cout << "sg.IsContain(a1_ge): " <<sg.IsContain(a1_ge) << endl;
			cout << endl;
			cout << "sg.GetPower(a2_ge): " << sg.GetPower(a2_ge) << endl;
			cout << "sg.IsContain(a2_ge): " << sg.IsContain(a2_ge) << endl;
			*/

		//cout<<"gr.WordIsEqualTo1(a1_ge): " << sg.WordIsEqualTo1(a1_ge) << endl;
		cout << "gr.WordIsEqualTo1(a2_ge): " << gr.WordIsEqualTo1(a2_ge) << endl;
		cout << "gr.WordIsEqualTo1(a3_ge): " << gr.WordIsEqualTo1(a3_ge) << endl;

	}

	// ====================================================================

	{

		FG_AbelianGroup::FG_AbelianGroupElement order1(4);
		order1[0] = 8;
		order1[1] = 8;
		order1[2] = 5;
		order1[3] = 7;

		FG_AbelianGroup gr1(order1, 'a');

		FG_AbelianGroup::FG_AbelianGroupElement order2(4);
		order2[0] = 8;
		order2[1] = 8;
		order2[2] = 5;
		order2[3] = 7;

		FG_AbelianGroup gr2(order2, 'b');

		string a1_input = "a_{1}^{3}a_{3}^{4}a_{2}^{2}a_{3}a_{1}^{-1}";
		cout << a1_input << endl;
		TexString a1_Tex_input(a1_input);
		Word a1_word = ConvertingTexToWord(a1_Tex_input);
		GroupElement a1_ge = GroupElement(a1_word, &gr1);

		FCSG_FGAbelianGroup sgp1(a1_ge);

		string a2_input = "b_{1}^{4}b_{3}^{4}b_{2}^{2}b_{3}b_{1}^{-3}";
		cout << a2_input << endl;
		TexString a2_Tex_input(a2_input);
		Word a2_word = ConvertingTexToWord(a2_Tex_input);
		GroupElement a2_ge = GroupElement(a2_word, &gr2);

		FCSG_FGAbelianGroup sgp2(a2_ge);

		cout << "gr.WordIsEqualTo1(a1_ge): " << gr1.WordIsEqualTo1(a1_ge) << endl;
		cout << "gr.WordIsEqualTo1(a2_ge): " << gr2.WordIsEqualTo1(a2_ge) << endl;

		CyclicSubGroupIzomorphizm iz(&sgp1, &sgp2);

		FM_Two_Groups fm(&iz);

		string a3_input = "a_{1}^{2}a_{3}^{4}a_{2}^{2}a_{3}a_{1}^{-1}";
		cout << a3_input << endl;
		TexString a3_Tex_input(a3_input);
		Word a3_word = ConvertingTexToWord(a3_Tex_input);
		GroupElement a3_ge = GroupElement(a3_word, &gr1);

		string a4_input = "b_{1}^{3}b_{3}^{4}b_{2}^{2}b_{3}b_{1}^{-3}";
		cout << a4_input << endl;
		TexString a4_Tex_input(a4_input);
		Word a4_word = ConvertingTexToWord(a4_Tex_input);
		GroupElement a4_ge = GroupElement(a4_word, &gr2);

		GroupElement a3_fmge = fm.StandartImageOf(a3_ge);
		GroupElement a4_fmge = fm.StandartImageOf(a4_ge);

		GroupElement a3a4_fmge = a3_fmge * a4_fmge;

		cout << fm.WordIsEqualTo1(a3a4_fmge) << endl;

	}

	cout << endl;
	system("pause");
	return 0;
	
}