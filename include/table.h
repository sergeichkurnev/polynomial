#pragma once
#include"nomials.h"
#include<vector>


template<typename T=poly>
class table
{
	vector<T> tabl;
	bool f;
public:
	table() { f = false; }
	void add(T P)
	{
		tabl.push_back(P);
	}
	void del(string K)
	{
		if (!tabl.empty())
		{
			auto it = tabl.begin();
			while (it != tabl.end())
			{
				if ((*it).GetName() == K)
				{
					tabl.erase(it);
					break;
				}
				it++;
			}
		}
	}
	T search(string K)
	{
		T TEMP;
		if (!tabl.empty())
		{
			for (int i = 0; i < tabl.size(); i++)
				if (tabl[i].GetName() == K)
					return tabl[i];
		}
		else
		{
			return TEMP;
			cout << "not found" << endl;
		}
		cout << "not found" << endl;
		return TEMP;
	}
	T operator[](int i){ return tabl[i]; }
	bool IsActual() { return f; }
	void MakeActual() { f = true; }
	void UnActual() { f = false; }
	void print()
	{
		for (int i = 0; i < tabl.size(); i++)
			cout << tabl[i] << endl;
	}
};