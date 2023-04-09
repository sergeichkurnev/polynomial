#pragma once

#include "nomials.h"
#include <vector>
#include<stdlib.h>

template<typename T = poly>
class ordered_table
{
	vector<T> tabl;
	bool f;
	int binsearch(string K, int first, int last)
	{
		if (tabl[(first + last) / 2].GetName() == K)
			return (first + last) / 2;
		else if (tabl[(first + last) / 2].GetName() > K)
			binsearch(K, first, (first + last) / 2);
		else if (tabl[(first + last) / 2].GetName() < K)
			binsearch(K, (first + last) / 2, last);
		return -1;
	}
public:
	ordered_table() { f = false; }
	void add(T P)
	{
		tabl.push_back(P);
	}
	void del(string K)
	{
		if (!tabl.empty())
		{
			for (int i = binsearch(K, 0, tabl.size() - 1); i < tabl.size(); i++)
				if (tabl[i].GetName() == K)
				{
					for (int j = i; j < tabl.size() - 1; j++)
						tabl[j] = tabl[j + 1];
				}
			tabl.pop_back();
		}
	}
	T search(string K)
	{
		T TEMP;
		if (!tabl.empty())
		{
			return tabl[binsearch(K, 0, tabl.size() - 1)];
		}
		else
		{
			return TEMP;
			cout << "not found" << endl;
		}
		cout << "not found" << endl;
		return TEMP;
	}
	T operator[](int i) { return tabl[i]; }
	bool IsActual() { return f; }
	void MakeActual() { f = true; }
	void UnActual() { f = false; }
	void print()
	{
		for (int i = 0; i < tabl.size(); i++)
			cout << tabl[i] << endl;
	}
};