#include "format.h"

bool isSubstanceChar(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        return true;
    }
    if (ch >= 'a' && ch <= 'z')
    {
        return true;
    }
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    if (ch == '(' || ch == ')')
    {
        return true;
    }
    if (ch == '[' || ch == ']')
    {
        return true;
    }
    return false;
}

bool tryInsertSubstance(string &name, vector<Substance> &ary)
{
    Substance sub = Substance(name);
    if (sub.getElements().empty())
    {
        return false;
    }
    ary.push_back(sub);
    return true;
}

// use simple DFA to parse input
// 0: receiving reactant
// 1: receiving resultant
string getInput(string &input, vector<Substance> &reactant, vector<Substance> &resultant)
{
    int state = 0;
    string curName = "";
    for (int i = 0; i < input.size(); i++)
    {
        char curCh = input[i];
        if (curCh == ' ' || curCh == '\t')
        {
            continue;
        }
        if (curCh == '+')
        {
            if (curName == "")
            {
                return "Empty substance before +";
            }
            if (state == 0)
            {
                if (!tryInsertSubstance(curName, reactant))
                {
                    return "Invalid reactant name: " + curName;
                }
            }
            else if (state == 1)
            {
                if (!tryInsertSubstance(curName, resultant))
                {
                    return "Invalid resultant name: " + curName;
                }
            }
            curName = "";
        }
        else if (curCh == '=')
        {
            if (state == 1)
            {
                return "Multiple =";
            }
            if (curName == "")
            {
                return "Empty substance before =";
            }
            if (!tryInsertSubstance(curName, reactant))
            {
                return "Invalid reactant name: " + curName;
            }
            curName = "";
            state = 1;
        }
        else if (isSubstanceChar(curCh))
        {
            curName += curCh;
        }
        else
        {
            return "Invalid character " + string(1, curCh);
        }
    }
    if (state == 0)
    {
        return "No =";
    }
    if (curName == "")
    {
        return "Empty substance at the end";
    }
    resultant.push_back(curName);
    return "";
}

string getOutput(vector<Substance> &reactant, vector<Substance> &resultant, vector<int> &reactCnt, vector<int> &resultCnt)
{
    string result = "";
	for (int i = 0; i < reactCnt.size(); i++)
	{
		if (i > 0)
		{
			result += " + ";
		}
		if (reactCnt[i] > 1)
		{
			result += to_string(reactCnt[i]);
		}
		result += reactant[i].getName();
	}
	result += " = ";
	for (int i = 0; i < resultCnt.size(); i++)
	{
		if (i > 0)
		{
			result += " + ";
		}
		if (resultCnt[i] > 1)
		{
			result += to_string(resultCnt[i]);
		}
		result += resultant[i].getName();
	}
    return result;
}
