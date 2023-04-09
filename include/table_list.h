#pragma once

#include"nomials.h"

template<typename T=poly>
class table_list
{
	list<T> L;
	bool f;
public:
	table_list() { f = false; }
	void add(T P){ L.push_back(P); }
	void del(string K)
	{
		auto it = L.begin();
		while (it != L.end())
		{
			if ((*it).GetName() == K)
			{
				L.erase(it);
				break;
			}
			it++;
		}
	}
	T search(string K)
	{
		T P;
		for (auto it = L.begin(); it != L.end(); it++)
			if ((*it).GetName() == K)
				return *it;
		cout << "not found" << endl;
		return P;
	}
	bool IsActual() { return f; }
	void MakeActual() { f = true; }
	void UnActual() { f = false; }
	void print()
	{
		for (auto it= L.begin(); it != L.end(); it++)
			cout << (*it) << endl;
	}
};