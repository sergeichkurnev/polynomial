#pragma once

#include"nomials.h"

template<typename T = poly>
class chain_hash
{
	list<T> chain[256];
	bool f;
	int hash(string K)
	{
		return K[K.size() - 1];
	}
public:
	chain_hash()
	{
		f = false;
	}
	void add(T P)
	{
		chain[hash(P.GetName())].push_back(P);
	}
	bool search(T P)
	{
		for (auto it = chain[hash(P.GetName())].begin(); it != chain[hash(P.GetName())].end(); it++)
			if ((*it) == P)
				return true;
		cout << "not found" << endl;
		return false;
	}
	void del(T P)
	{
		for (auto it = chain[hash(P.GetName())].begin(); it != chain[hash(P.GetName())].end(); it++)
			if ((*it) == P)
			{
				chain[hash(P.GetName())].erase(it);
				return;
			}
	}
	bool IsActual() { return f; }
	void MakeActual() { f = true; }
	void UnActual() { f = false; }
};
