#pragma once
typedef double db;
typedef unsigned int ui;

#include <locale.h>
#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <math.h>

using namespace std;

class mono
{
	int GetiNumber(string expr, int* i)//преобразование строки в число int, начиная с номера pos
	{
		string num = "";
		for (int j = *i; j < expr.length(); j++, (*i)++)
			if (isdigit(expr[j]))
				num += expr[j];
			else
				break;
		(*i)--;
		return stoi(num);

	}
	double GetdNumber(string expr, int* i)//преобразование строки в число double, начиная с номера pos
	{
		string num = "";
		for (int j = *i; j < expr.length(); j++, (*i)++)
			if (isdigit(expr[j]))
				num += expr[j];
			else if (expr[j] == '.')
				num += expr[j];
			else
			{
				break;
			}
		(*i)--;
		return stod(num);
	}
	ui degx,degy,degz;
	db k;
public:
	bool fx, fy, fz;
	db& koef()
	{
		return k;
	}
	ui& stx()
	{
		return degx;
	}
	ui& sty()
	{
		return degy;
	}
	ui& stz()
	{
		return degz;
	}
	mono operator+(mono M)
	{
		mono tmp;
		if ((M.degx == degx) && (M.degy == degy) && (M.degz == degz))
		{
			tmp = M;
			tmp.k += k;
		}
		return tmp;
	}
	mono operator-(mono M)
	{
		mono tmp;
		if ((M.degx == degx) && (M.degy == degy) && (M.degz == degz))
		{
			tmp = M;
			tmp.k -= k;
		}
		return tmp;
	}
	bool operator==(mono M)
	{
		return(stx() == M.stx() && sty() == M.sty() && stz() == M.stz());
	}
	mono operator*(mono M)
	{
		mono tmp = M;
		tmp.k *= k;
		tmp.fx |= fx;
		tmp.fy |= fy;
		tmp.fz |= fz;
		tmp.degx += degx;
		tmp.degy += degy;
		tmp.degz += degz;
		return tmp;
	}
	db calc(db x1, db y1, db z1)
	{
		db res;
		res = k * pow(x1, degx) * pow(y1, degy) * pow(z1, degz);
		return res;
	}
	friend istream& operator>>(istream&, mono& );
	friend ostream& operator<<(ostream&, const mono&);
	mono GetMono(string tmp, int* i)
	{
		mono M;
		bool fx, fy, fz, f, fadd, fout;
		fx = fy = fz = f = fout = fadd = false;
		int len = tmp.length();
		for (int pos = *i; pos < len; pos++) //парсим слагаемое полинома (одно) хз, возможно нигде не используется
		{
			if (tmp[pos] == '-') // проверка числа на отрицательнось
			{
				if (f || fadd)
					fout = true;
				f = true;
				pos++;
			}
			if (tmp[pos] == '+')
			{
				if (fadd || f)
					fout = true;
				fadd = true;
			}
			if (fout)
				break;
			if (isdigit(tmp[pos]) && (!fx) && (!fy) && (!fz))
			{
				M.k = GetdNumber(tmp, &pos);
				if (f)
				{
					M.k *= (-1);
					pos++;
				}

			}



			if (tmp[pos] == 'x')
			{
				fx = true;
				if (pos < len - 1)
					pos++;
				else
				{
					M.degx = 1;
					break;
				}
				if (tmp[pos] == '^')
				{
					pos++;
					M.degx = GetiNumber(tmp, &pos);
					pos++;
				}
				else
				{
					M.degx = 1;
				}
			}


			if (tmp[pos] == 'y')
			{
				fy = true;
				if (pos < len - 1)
					pos++;
				else
				{
					M.degx = 1;
					break;
				}
				if (tmp[pos] == '^')
				{
					pos++;
					M.degy = GetiNumber(tmp, &pos);
					pos++;
				}
				else
				{
					M.degy = 1;
				}
			}


			if (tmp[pos] == 'z')
			{
				fz = true;
				if (pos < len - 1)
					pos++;
				else
				{
					M.degx = 1;
					break;
				}
				if (tmp[pos] == '^')
				{
					pos++;
					M.degz = GetiNumber(tmp, &pos);
					pos++;
				}
				else
				{
					M.degz = 1;
				}
			}
			if (M.k == 0 && (fx || fy || fz))
			{
				M.k = 1;
				if (f)
					M.k *= (-1);
			}


			M.fx = fx;
			M.fy = fy;
			M.fz = fz;
			*i = pos;
		}
		*this = M;
		return M;
	}
	mono() { fx = fy = fz = false; degx=degy=degz = 0; k = 0; } // по умолчанию это константа 0
};


class poly
{
	list <mono> polynom;
	string name;
	int GetiNumber(string expr, int* i) const
	{
		string num = "";
		for (int j = *i; j < expr.length(); j++, (*i)++)
			if (isdigit(expr[j]))
				num += expr[j];
			else
				break;
		(*i)--;
		return stoi(num);

	}
	double GetdNumber(string expr, int* i)const 
	{
		string num = "";
		for (int j = *i; j < expr.length(); j++, (*i)++)
			if (isdigit(expr[j]))
				num += expr[j];
			else if (expr[j] == '.')
				num += expr[j];
			else
			{
				break;
			}
		(*i)--;
		return stod(num);
	}
	void ZeroDelete()
	{
		list<mono> TMP;
		for (auto it = polynom.begin(); it != polynom.end(); it++)
			if ((*it).koef() != 0)
				TMP.push_back(*it);
		polynom.clear();
		polynom = TMP;
	}
	void MakeSimular()
	{
		for (auto it = polynom.begin(); it != polynom.end(); it++)
		{
			bool f = false;
			for (auto jt = polynom.begin(); jt != polynom.end(); jt++)
			{
				if ((*it) == (*jt))
				{
					if (!f)
						f = true;
					else
					{
						(*it).koef() += (*jt).koef();
						(*jt).koef() = 0;
					}
				}
			}
		}
		ZeroDelete();
	}
public:
	list<mono>& GetValue() { return polynom; }
	string PToString() 
	{
		string out = "";  for (auto it = polynom.begin(); it != polynom.end(); it++)
		{
			if (out != "")
				if ((*it).koef() > 0)    
					out += '+';
			if ((*it).koef() != (int)(*it).koef()) 
				out += std::to_string((*it).koef()) + "x^" + to_string((*it).stx()) + "y^" + to_string((*it).sty()) + "z^" + to_string((*it).stz());
			else
				out += std::to_string((int)(*it).koef()) + "x^" + to_string((*it).stx()) + "y^" + to_string((*it).sty()) + "z^" + to_string((*it).stz());
		}  return out;
	}
	string& GetName()
	{
		return name;
	}
	poly()
	{
		name = "NONE";
	}
	void poly::GetPoly(string str)
	{
		bool f = true;
		string new_name = "";
		if (isdigit(str[0]))
		{
			f = false;
			new_name = "const";
		}
		str += '+';
		int len = str.length();
		mono M;
		bool f1, fz, fx, fy;
		f1 = fx = fz = fy = false;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '=')
			{
				f = false;
				i++;
			}
			if (f)
				new_name += str[i];
			else
			{
				if (str[i] == '-') // checking for -
				{

					f1 = true;
					i++;
				}
				if (isdigit(str[i]) && (!fx) && (!fy) && (!fz))
				{
					M.koef() = GetdNumber(str, &i);
					if (f1)
					{
						M.koef() *= (-1);
						i++;
					}
				}
				if (str[i] == 'x')
				{
					fx = true;
					if (i < len - 1)
						i++;
					else
					{
						M.stx() = 1;
						break;
					}
					if (str[i] == '^')
					{
						i++;
						M.stx() = GetiNumber(str, &i);
						i++;
					}
					else
					{
						M.stx() = 1;
					}
				}
				if (str[i] == 'y')
				{
					fy = true;
					if (i < len - 1)
						i++;
					else
					{
						M.sty() = 1;
						break;
					}
					if (str[i] == '^')
					{
						i++;
						M.sty() = GetiNumber(str, &i);
						i++;
					}
					else
					{
						M.sty() = 1;
					}
				}


				if (str[i] == 'z')
				{
					fz = true;
					if (i < len - 1)
						i++;
					else
					{
						M.stz() = 1;
						break;
					}
					if (str[i] == '^')
					{
						i++;
						M.stz() = GetiNumber(str, &i);
						i++;
					}
					else
					{
						M.stz() = 1;
					}
				}
				if (M.koef() == 0 && (fx || fy || fz))
				{
					M.koef() = 1;
					if (f1)
						M.koef() *= (-1);
				}
				if (str[i] == '+')
				{
					M.fx = fx;
					M.fy = fy;
					M.fz = fz;
					polynom.push_back(M);
					M.stx() = M.sty() = M.stz() = 0;
					M.fx = M.fy = M.fz = false;
					M.koef() = 0;
					f1 = fx = fz = fy = false;
				}
				if (str[i] == '-')
				{
					M.fx = fx;
					M.fy = fy;
					M.fz = fz;
					polynom.push_back(M);
					M.stx() = M.sty() = M.stz() = 0;
					M.fx = M.fy = M.fz = false;
					f1 = true;
					M.koef() = 0;
					fx = fz = fy = false;
				}
			}
		}
		name = new_name;
		this->MakeSimular();
	}
	poly poly::operator+(mono M)
	{
		poly tmp;
		tmp = *this;
		list<mono>::iterator it = tmp.polynom.begin();
		bool f = false;
		for (; it != tmp.polynom.end(); it++)
			if ((*it).stx() == M.stx() && (*it).sty() == M.sty() && (*it).stz() == M.stz())
			{
				f = true;
				(*it).koef() += M.koef();
			}
		if (!f)
			tmp.polynom.push_back(M);
		tmp.MakeSimular();
		return tmp;

	}
	bool operator==( poly P)
	{
		list<mono>::iterator it2 = P.polynom.begin();
		if (polynom.size() == P.polynom.size())
		{
			for (auto it = polynom.begin(); it != polynom.end(); it++, it2++)
				if ((*it).stx() != (*it2).stx() || (*it).sty() != (*it2).sty() || (*it).stz() != (*it2).stz() || (*it).koef() != (*it2).koef())
					return false;
		}
		else
			return false;
		return true;
	}
	poly operator-(mono M)
	{
		poly tmp;
		tmp = *this;
		list<mono>::iterator it = tmp.polynom.begin();
		bool f = false;
		for (; it != tmp.polynom.end(); it++)
			if ((*it).stx() == M.stx() && (*it).sty() == M.sty() && (*it).stz() == M.stz())
			{
				f = true;
				(*it).koef() -= M.koef();
			}
		if (!f)
		{
			M.koef() *= (-1);
			tmp.polynom.push_back(M);
		}
		tmp.MakeSimular();
		return tmp;
	}
	bool operator<(poly P)
	{
		return name < P.GetName();
	}
	bool operator>(poly P)
	{
		return name > P.GetName();
	}
	bool operator<(string K) { return name < K; }
	bool operator>(string K) { return name > K; }
	poly operator+(poly P)
	{
		poly tmp;
		tmp = *this;
		list<mono>::iterator it2 = P.polynom.begin();
		for (; it2 != P.polynom.end(); it2++)
			tmp = tmp + (*it2);
		tmp.MakeSimular();
		return tmp;
	}
	poly& operator=(poly P)
	{
		name = P.GetName();
		polynom = P.GetValue();
		return *this;
	}
	poly operator-(poly P)
	{
		poly tmp;
		tmp = *this;
		list<mono>::iterator it2 = P.polynom.begin();
		for (; it2 != P.polynom.end(); it2++)
			tmp = tmp - (*it2);
		for (it2 = tmp.polynom.begin(); it2 != tmp.polynom.end(); it2++)
			if ((*it2).koef() == 0)
				tmp.polynom.erase(it2);
		tmp.MakeSimular();
		return tmp;
	}
	poly operator*(poly P)
	{
		poly tmp;
		for (auto it = polynom.begin(); it != polynom.end(); it++)
			for (auto itP = P.polynom.begin(); itP != P.polynom.end(); itP++)
				tmp.polynom.push_back((*it)*(*itP));
		tmp.MakeSimular();
		return tmp;
	}
	poly operator*(db k)
	{
		poly tmp;
		tmp = *this;
		if (k == 0)
			tmp.polynom.clear();
		else
		{
			list<mono>::iterator it = tmp.polynom.begin();
			for (; it != polynom.end(); it++)
				(*it).koef() *= k;
		}
		return tmp;
	}
	db calc(db x1, db y1, db z1)
	{
		db res = 0;
		list<mono>::iterator it = polynom.begin();
		for (; it != polynom.end(); it++)
			res += (*it).calc(x1, y1, z1);
		return res;

	}
	friend istream& operator>>(istream&, poly& );
	friend ostream& operator<<(ostream&, const poly&);
};