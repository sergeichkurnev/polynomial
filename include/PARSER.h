#pragma once
#include<map>
#include<stack>
#include"nomials.h"
#include"table.h"
#include"table_list.h"
#include"ordered_table.h"
#include"chain_hash.h"
#include"open_adress_hash.h"
#include"AVLTree.h"

template <typename T = table<poly>>
class EXPRESSION
{
    T TABL;
    string infix;
    string postfix;
    map<char, int>priority{ make_pair('(',0), make_pair('+',1), make_pair('-',1), make_pair('*',2), make_pair('/',2) };
    string GetStringNumber(string expr, int* i)
    {
        string num = "";
        for (int j = *i; j < expr.length(); j++, (*i)++)
            if (isdigit(expr[j]))
                num += expr[j];
            else
                break;
        (*i)--;
        return num;
    }
    double GetNumber(string expr, int* i)//преобразование строки в число, начиная с номера pos
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
    string GetName(string expr, int* i)
    {
        string num = "";
        for (int j = *i; j < expr.length(); j++, (*i)++)
            if (isalpha(expr[j]) || isdigit(expr[j]))
                num += expr[j];
            else
                break;
        (*i)--;
        return num;

    }
    string ToPostfix()
    {
        postfix = "";
        stack<char> Stack;
        char num;
        for (int pos = 0; pos < infix.length(); pos++)
        {
            num = infix[pos];
            if (isdigit(num) || isalpha(num))
            {
                if (isdigit(num))
                    postfix += GetStringNumber(infix, &pos);
                else
                    postfix += GetName(infix, &pos);
                postfix += ' ';
            }
            else if (num == '(')
                Stack.push(num);
            else if (num == ')')
            {
                while (!Stack.empty() > 0 && Stack.top() != '(')
                {
                    postfix += Stack.top();
                    Stack.pop();
                }
                Stack.pop();
            }
            else if (priority.find(num) != priority.end())
            {
                char op = num;
                while (!Stack.empty() > 0 && priority[Stack.top()] >= priority[op])
                {
                    postfix += Stack.top();
                    Stack.pop();
                }
                Stack.push(op);
            }


        }
        while (!Stack.empty())
        {
            postfix += Stack.top();
            Stack.pop();
        }
        return postfix;

    }
    poly math(poly s1, poly s2, char op)
    {
        switch (op)
        {
        case '+': return s1 + s2;
        case '-': return s1 - s2;
        case '*': return s1 * s2;
        case '/': cout << "impossible operation" << endl;
        }
    }

public:
    void  input(string s)
    {
        infix = s;
    }
    void convert()
    {
        ToPostfix();
    }
    EXPRESSION(string _infix) :infix(_infix)
    {
        ToPostfix();
    }
    string GetInfix() const
    {
        return infix;
    }
    string GetPostfix() const
    {
        return postfix;
    }
    poly calc(T TAB)
    {
        poly P;
        poly last;
        poly first;
        stack<poly> operands;
        char c;
        for (int i = 0; i < postfix.length(); i++)
        {
            c = postfix[i];
            if (isalpha(c))
                operands.push(TAB.search(GetName(postfix, &i)));
            else if (isdigit(c))
            {
                P.GetValue().clear();
                P.GetPoly(GetStringNumber(postfix, &i));
                operands.push(P);
            }
            else if (priority.find(c) != priority.end())
            {
                last = operands.top();
                operands.pop();
                first = operands.top();
                operands.pop();
                operands.push(math(first, last, c));
            }
        }
        poly x = operands.top();
        operands.pop();

        return x;

    }

};