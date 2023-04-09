
#include "nomials.h"

istream& operator>>(istream& istr, mono& M) // ввод монома
{
	string inp;
    istr >> inp;
	int t = 0;
	M.GetMono(inp,&t);
	return istr;
}

ostream& operator<<(ostream& ostr, const mono& M) // вывод монома 
{
	if (M.k == 0)
		ostr << ' ' << 0;
	else
		ostr << ' ' << M.k;
	if (M.fx)
		ostr << "x^" << '(' << M.degx << ')';
	if (M.fy)
		ostr << "y^" << '(' << M.degy << ')';
	if (M.fz)
		ostr << "z^" << '(' << M.degz << ')';
	ostr << ' ';
	return ostr;
}



//---------------------------------------------------------------------

istream& operator>>(istream& istr, poly& P)
{
	string str;
	istr >> str;
	P.GetPoly(str);
	return istr;
}

ostream& operator<<(ostream& ostr, const poly& P)
{
	ostr << P.name << " =";
	for (auto it = P.polynom.cbegin(); it != P.polynom.cend(); it++)
	{
		ostr<< * it <<'+';
	}
	cout << '\b' <<' '<< endl;
	
	return ostr;
}

//----------------------------------------------------------