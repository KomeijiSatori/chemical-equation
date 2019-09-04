#include <set>

#include "helper.h"
#include "utils.h"
#include "substance.h"

SolveResult solve(vector<vector<Fraction> > &matrix, vector<int> &res)
{
    int m = matrix.size();
    if (m == 0) return SolveResult::NOANSWER;
    int n = matrix[0].size();
    if (n == 0) return SolveResult::NOANSWER;
    int row = 0;
    for (row = 0; row < m; row++)
    {
        // if has already been full ranked
		if (row >= n)
		{
			return SolveResult::NOANSWER;
		}
        // find the first row that matrix[i][row] is not 0
        int i;
        for (i = row; i < m; i++)
        {
            if (matrix[i][row].getNumerator() != 0)
            {
                break;
            }
        }
        // if all matrix[i][row] are 0
        if (i == m)
        {
            // check if all col is 0
            for (int j = row; j < n; j++)
            {
                // if other element in that row is not 0, means there is no answer
                if (matrix[row][j].getNumerator() != 0)
                {
                    return SolveResult::NOANSWER;
                }
            }
            // then means the rank is row
            break;
        }
        // if not the same row, swap it
        if (i != row)
        {
            swap(matrix[i], matrix[row]);
        }
        // set the current row's first non-zero element to be 1
        Fraction base = matrix[row][row];
        // set the row's other memebers
        for (int j = row; j < n; j++)
        {
            matrix[row][j] = matrix[row][j] / base;
        }
        // other rows minus the row
        for (i = row + 1; i < m; i++)
        {
            base = matrix[i][row] / matrix[row][row];
            for (int j = row; j < n; j++)
            {
                matrix[i][j] = matrix[i][j] - base * matrix[row][j];
            }
        }
    }
    // then judge the rank
    // if has no answer
    if (row >= n)
    {
        return SolveResult::NOANSWER;
    }
    // if has multiple answers
    else if (row <= n - 2)
    {
        return SolveResult::MULANSWER;
    }
    // then row is n - 1, means only one answer
    // now calc, assume the last element is 1
    vector<Fraction> tmpRes = vector<Fraction>(n, Fraction(0, 1));
    tmpRes[n - 1] = Fraction(1, 1);
    // now calc other rows
    for (int i = n - 2; i >= 0; i--)
    {
        Fraction curRes(0, 1);
        for (int j = i + 1; j < n; j++)
        {
            curRes = curRes - matrix[i][j] * tmpRes[j];
        }
        // if any answer is lower than zero, means no solution too
        if (curRes.getNumerator() <= 0)
        {
            return SolveResult::NOANSWER;
        }
        tmpRes[i] = curRes;
    }
    // transfer fraction to int
    int mul = 1;
    for (int i = 0; i < n; i++)
    {
        mul = lcm(mul, tmpRes[i].getDenominator());
    }
    for (int i = 0; i < n; i++)
    {
        tmpRes[i] = tmpRes[i] * Fraction(mul, 1);
        res.push_back(tmpRes[i].getNumerator());
    }
    return SolveResult::ONEANSWER;
}

SolveResult getElementCnt(vector<Substance> &reactant, vector<Substance> &resultant, vector<int> &reactCnt, vector<int> &resultCnt)
{
    int n = reactant.size() + resultant.size();
    set<string> elements;

    // calc total elements' name
    for (int i = 0; i < reactant.size(); i++)
    {
        map<string, int> curEle = reactant[i].getElements();
        for (map<string, int>::iterator itr = curEle.begin(); itr != curEle.end(); ++itr)
        {
            elements.insert(itr->first);
        }
    }
    for (int i = 0; i < resultant.size(); i++)
    {
        map<string, int> curEle = resultant[i].getElements();
        for (map<string, int>::iterator itr = curEle.begin(); itr != curEle.end(); ++itr)
        {
            elements.insert(itr->first);
        }
    }
    int m = elements.size();
    // generate matrix
    vector<vector<Fraction> > matrix;
    for (set<string>::iterator itr = elements.begin(); itr != elements.end(); ++itr)
    {
        string eleName = *itr;
        vector<Fraction> curRow;
        for (int i = 0; i < reactant.size(); i++)
        {
            map<string, int> curEle = reactant[i].getElements();
            map<string, int>::iterator tmp = curEle.find(eleName);
            if (tmp != curEle.end())
            {
                curRow.push_back(Fraction(tmp->second, 1));
            }
            else
            {
                curRow.push_back(Fraction(0, 1));
            }
        }
        for (int i = 0; i < resultant.size(); i++)
        {
            map<string, int> curEle = resultant[i].getElements();
            map<string, int>::iterator tmp = curEle.find(eleName);
            if (tmp != curEle.end())
            {
                curRow.push_back(Fraction(-tmp->second, 1));
            }
            else
            {
                curRow.push_back(Fraction(0, 1));
            }
        }
        matrix.push_back(curRow);
    }
    // solve the matrix
    vector<int> answer;
    SolveResult res = solve(matrix, answer);
    if (res != SolveResult::ONEANSWER)
    {
        return res;
    }
    reactCnt = vector<int>(answer.begin(), answer.begin() + reactant.size());
    resultCnt = vector<int>(answer.begin() + reactant.size(), answer.end());
    return res;
}
