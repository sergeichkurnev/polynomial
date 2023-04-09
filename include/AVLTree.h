#pragma once
#include <iostream>
#include <vector>
#include "nomials.h"

using namespace std;

template <typename T=poly>
class AVLTree
{
private:
	struct node
	{
		T key;
		node* left;
		node* right;
		int height;
		node(const T& k) { key = k; left = right = nullptr; height = 1; }
		//~node() { delete left; delete right; }
	};

	node* root;

	bool f;

	int height(node* p)
	{
		return p ? p->height : 0;
	}

	int balance_factor(node* p)
	{
		return height(p->right) - height(p->left);
	}

	void restore_height(node* p)
	{
		p->height = (height(p->left) > height(p->right) ? height(p->left) : height(p->right)) + 1;
	}

	node* right_rotate(node* p)
	{
		node* temp = p->left;
		p->left = temp->right;
		temp->right = p;
		restore_height(p);
		restore_height(temp);
		return temp;
	}

	node* left_rotate(node* p)
	{
		node* temp = p->right;
		p->right = temp->left;
		temp->left = p;
		restore_height(p);
		restore_height(temp);
		return temp;
	}

	node* balance(node* p)
	{
		restore_height(p);

		if (balance_factor(p) == 2)
		{
			if (balance_factor(p->right) < 0)
				p->right = right_rotate(p->right);
			return left_rotate(p);
		}
		if (balance_factor(p) == -2)
		{
			if (balance_factor(p->left) > 0)
				p->left = left_rotate(p->left);
			return right_rotate(p);
		}
		return p;

	}

	node* insert(node* p,T k) 
	{
		if (!p)
		{
			p = new node(k);
			return p;
		}
		if (k < p->key)
			p->left = insert(p->left, k);
		else
			p->right = insert(p->right, k);
		return balance(p);
	}

	node* find_min(node* p)  
	{
		return p->left ? find_min(p->left) : p;
	}

	node* remove_min(node* p) 
	{
		if (p->left == nullptr)
			return p->right;
		p->left = remove_min(p->left);
		return balance(p);
	}

	node* remove(node* p, T k) 
	{
		if (!p) return 0;
		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else 
		{
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = find_min(r);
			min->right = remove_min(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	bool find(node* p, /*const*/ T& k)
	{
		if (p == nullptr)
			return false;
		else if (k == p->key)
			return true;
		if (k < p->key)
			find(p->left, k);
		else if (k > p->key)
			find(p->right, k);
		else
			return false;
	}

	void printTree(node* r, string indent, bool last)
	{
		if (r != nullptr)
		{
			cout << indent;
			if (last)
			{
				cout << "R----";
				indent += "   ";
			}
			else
			{
				cout << "L----";
				indent += "|  ";
			}
			cout << r->key << endl;
			printTree(r->left, indent, false);
			printTree(r->right, indent, true);
		}
	}

public:

	AVLTree()
	{
		f = 0;
		root = nullptr;
	}

	AVLTree(const vector<T>& values)
	{
		f = false;
		for (size_t i = 0; i < values.size(); i++)
			insert(values[i]);
	}

	~AVLTree()
	{
		delete root;
	}

	void insert(T x)
	{
		root = insert(root, x);
	}
	void add(T x)
	{
		insert(x);
	}

	void remove(const T& x)
	{
		remove(root, x);
	}

	void printTree()
	{
		printTree(root,"", true);
	}
	
	bool search(/*const*/ T& x)
	{
		return find(root, x);
	}
};