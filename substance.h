# ifndef __SUBSTANCE_H__
# define __SUBSTANCE_H__

#include <map>
#include <stack>
#include <string>
using namespace std;

class Substance
{
    private:
        string name;
        map<string, int> elements;
        bool getElementsByName(string &);
        bool adjustStack(stack<pair<string, int> > &, int);
    public:
        Substance(string name);
        Substance(const Substance &a);
        Substance& operator = (Substance &a);
        string getName(void);
        map<string, int> getElements(void);
};

# endif
