#include <iostream>
#include "substance.h"
#include "helper.h"
#include "format.h"

using namespace std;

int main(void)
{
	string equation;
	while (getline(cin, equation))
	{
		vector<Substance> reactant, resultant;
		string inputRes = getInput(equation, reactant, resultant);
		if (inputRes != "")
		{
			cout << inputRes << endl;
		}
		else
		{
			vector<int> reactCnt, resultCnt;
			SolveResult res = getElementCnt(reactant, resultant, reactCnt, resultCnt);
			if (res == SolveResult::NOANSWER)
			{
				cout << "No answer" << endl;
			}
			else if (res == SolveResult::MULANSWER)
			{
				cout << "Multiple answers" << endl;
			}
			else if (res == SolveResult::ONEANSWER)
			{
				cout << getOutput(reactant, resultant, reactCnt, resultCnt) << endl;
			}
		}
	}
	return 0;
}