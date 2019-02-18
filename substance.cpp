#include "substance.h"
#include <stack>
using namespace std;

bool Substance::adjustStack(stack<pair<string, int>> &st, int times)
{
    if (st.empty())
    {
        return false;
    }
    string curStr = st.top().first;
    st.pop();
    string startStr = "";
    stack<pair<string, int>> tmp;
    if (curStr == ")")
    {
        startStr = "(";
    }
    else if (curStr == "]")
    {
        startStr = "[";
    }
    while (!st.empty())
    {
        pair<string, int> cur = st.top();
        st.pop();
        // calc inner elements
        if (cur.first != startStr)
        {
            // if it is not an element and is not the desire startStr
            if (cur.second < 0)
            {
                return false;
            }
            cur.second *= times;
            tmp.push(cur);
        }
        else
        {
            // push back to st
            while (!tmp.empty())
            {
                cur = tmp.top();
                tmp.pop();
                st.push(cur);
            }
            return true;
        }
    }
    return false;
}

// use DFA to get elements info from name
// 0: ready to receive elements
// 1: has received first Upper alpha
// 2: has received number after an element
// 3: has received lower case alpha after an upper alpha
// 4: has receive ) ]
// 5: has received number after receive ) ]
bool Substance::getElementsByName(string &_name)
{
    int state = 0;
    string curEle = "";
    int curCnt = 0;
    // stack of elements and its count, if count is -1, means it is not an element, is one of "()[]"
    stack<pair<string, int>> st;

    for (int i = 0; i < _name.length(); i++)
    {
        char curCh = _name[i];
        if (state == 0)
        {
            if (curCh >= 'A' && curCh <= 'Z')
            {
                curEle = string(1, curCh);
                state = 1;
            }
            else if (curCh == '[' || curCh == '(')
            {
                st.push(pair<string, int>(string(1, curCh), -1));
            }
            else if (curCh == ']' || curCh == ')')
            {
                st.push(pair<string, int>(string(1, curCh), -1));
                state = 4;
            }
            else
            {
                return false;
            }
        }
        else if (state == 1)
        {
            if (curCh >= 'A' && curCh <= 'Z')
            {
                st.push(pair<string, int>(curEle, 1));
                curEle = string(1, curCh);
            }
            else if (curCh >= 'a' && curCh <= 'z')
            {
                curEle += curCh;
                state = 3;
            }
            else if (curCh >= '0' && curCh <= '9')
            {
                curCnt = curCh - '0';
                state = 2;
            }
            else if (curCh == '[' || curCh == '(')
            {
                st.push(pair<string, int>(curEle, 1));
                st.push(pair<string, int>(string(1, curCh), -1));
                state = 0;
            }
            else if (curCh == ']' || curCh == ')')
            {
                st.push(pair<string, int>(curEle, 1));
                st.push(pair<string, int>(string(1, curCh), -1));
                state = 4;
            }
            else
            {
                return false;
            }
        }
        else if (state == 2)
        {
            if (curCh >= 'A' && curCh <= 'Z')
            {
                st.push(pair<string, int>(curEle, curCnt));
                curEle = string(1, curCh);
                state = 1;
            }
            else if (curCh >= '0' && curCh <= '9')
            {
                curCnt = curCnt * 10 + curCh - '0';
            }
            else if (curCh == '[' || curCh == '(')
            {
                st.push(pair<string, int>(curEle, curCnt));
                st.push(pair<string, int>(string(1, curCh), -1));
                state = 0;
            }
            else if (curCh == ']' || curCh == ')')
            {
                st.push(pair<string, int>(curEle, curCnt));
                st.push(pair<string, int>(string(1, curCh), -1));
                state = 4;
            }
            else
            {
                return false;
            }
        }
        else if (state == 3)
        {
            if (curCh >= 'A' && curCh <= 'Z')
            {
                st.push(pair<string, int>(curEle, 1));
                curEle = string(1, curCh);
                state = 1;
            }
            else if (curCh >= 'a' && curCh <= 'z')
            {
                curEle += curCh;
            }
            else if (curCh >= '0' && curCh <= '9')
            {
                curCnt = curCh - '0';
                state = 2;
            }
            else if (curCh == '[' || curCh == '(')
            {
                st.push(pair<string, int>(curEle, 1));
                st.push(pair<string, int>(string(1, curCh), -1));
                state = 0;
            }
            else if (curCh == ']' || curCh == ')')
            {
                st.push(pair<string, int>(curEle, 1));
                st.push(pair<string, int>(string(1, curCh), -1));
                state = 4;
            }
            else
            {
                return false;
            }
        }
        else if (state == 4)
        {
            if (curCh >= 'A' && curCh <= 'Z')
            {
                if (!adjustStack(st, 1))
                {
                    return false;
                }
                curEle = string(1, curCh);
                state = 1;
            }
            else if (curCh >= '0' && curCh <= '9')
            {
                curCnt = curCh - '0';
                state = 5;
            }
            else if (curCh == '[' || curCh == '(')
            {
                if (!adjustStack(st, 1))
                {
                    return false;
                }
                st.push(pair<string, int>(string(1, curCh), -1));
                state = 0;
            }
            else if (curCh == ']' || curCh == ')')
            {
                if (!adjustStack(st, 1))
                {
                    return false;
                }
                st.push(pair<string, int>(string(1, curCh), -1));
            }
            else
            {
                return false;
            }
        }
        else if (state == 5)
        {
            if (curCh >= 'A' && curCh <= 'Z')
            {
                if (!adjustStack(st, curCnt))
                {
                    return false;
                }
                curEle = string(1, curCh);
                state = 1;
            }
            else if (curCh >= '0' && curCh <= '9')
            {
                curCnt = curCnt * 10 + curCh - '0';
            }
            else if (curCh == '[' || curCh == '(')
            {
                if (!adjustStack(st, curCnt))
                {
                    return false;
                }
                st.push(pair<string, int>(string(1, curCh), -1));
                state = 0;
            }
            else if (curCh == ']' || curCh == ')')
            {
                if (!adjustStack(st, curCnt))
                {
                    return false;
                }
                st.push(pair<string, int>(string(1, curCh), -1));
                state = 4;
            }
            else
            {
                return false;
            }
        }
    }
    // deal with the end character '$', only ends at state 1, 2, 3, 4, 5 is valid
    if (state == 0)
    {
        return false;
    }
    else if (state == 1)
    {
        st.push(pair<string, int>(curEle, 1));
    }
    else if (state == 2)
    {
        st.push(pair<string, int>(curEle, curCnt));
    }
    else if (state == 3)
    {
        st.push(pair<string, int>(curEle, 1));
    }
    else if (state == 4)
    {
        if (!adjustStack(st, 1))
        {
            return false;
        }
    }
    else if (state == 5)
    {
        if (!adjustStack(st, curCnt))
        {
            return false;
        }
    }
    // fill the element map
    while (!st.empty())
    {
        pair<string, int> cur = st.top();
        st.pop();
        elements[cur.first] += cur.second;
    }
    return true;
}

Substance::Substance(string name)
{
    this->name = "";
    this->elements = map<string, int>();
    if (this->getElementsByName(name))
    {
        this->name = name;
    }    
}

Substance::Substance(const Substance &a)
{
    this->name = a.name;
    this->elements = a.elements;
}

Substance& Substance::operator = (Substance &a)
{
    this->name = a.name;
    this->elements = a.elements;
    return a;
}

string Substance::getName(void)
{
    return this->name;
}

map<string, int> Substance::getElements(void)
{
    return this->elements;
}
