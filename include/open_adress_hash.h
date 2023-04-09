#pragma once

#include"nomials.h"

template<typename T = poly>
class open_adress_hash
{
	T chain[256];
	bool f;
	int hash(string K)
	{
		return K[K.size() - 1];
	}
public:
	open_adress_hash()
	{
		T EMPTY;
		f = false; 
		for (int i = 0; i < 256; i++)
			chain[i] = EMPTY;
	}
	void add(T P)
	{
		for (int i = hash(P.GetName()); i < 256; i++)
			if (chain[i].GetValue().empty())
			{
				chain[i] = P;
				return;
			}
	}
	bool search(T P)
	{
		for (int i = hash(P.GetName()); i < 256; i++)
			if (chain[i] == P)
				return true;
		cout << "not found" << endl;
		return false;
	}
	void del(T P)
	{
		for (int i = hash(P.GetName()); i < 256; i++)
			if (chain[i] == P)
			{
				T P;
				chain[i] = P;
				return;
			}
		cout << "not found" << endl;
	}
	bool IsActual() { return f; }
	void MakeActual() { f = true; }
	void UnActual() { f = false; }
};