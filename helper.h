# ifndef __HELPER_H__
# define __HELPER_H__

#include <vector>

#include "fraction.h"
#include "substance.h"
using namespace std;

// the status of solve. 0: has only one solution, 1: has no solutions, 2: has multiple solutions
enum SolveResult
{
    ONEANSWER = 0,
    NOANSWER = 1,
    MULANSWER = 2
};

SolveResult getElementCnt(vector<Substance> &, vector<Substance> &, vector<int> &, vector<int> &);

# endif
