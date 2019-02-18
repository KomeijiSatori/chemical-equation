#ifndef __FORMAT_H__
#define __FORMAT_H__

#include <vector>

#include "substance.h"
using namespace std;

// return the error message of parse input, if no error, "" is returned
string getInput(string &input, vector<Substance> &, vector<Substance> &);
string getOutput(vector<Substance> &, vector<Substance> &, vector<int> &, vector<int> &);

#endif
