//Sequence of different values can be sorted by ascending if there is defined the ratio of order (<) above these values. 
//For example, the sequence A, B, C, D is sorted in ascending order means that A < B, B < C and C < D. 
//Given a set of relations of the form A < B, it is required to find out whether it is possible to form an increasing sequence.


#include "AscendingSequenceProblem.h"

using namespace asp;

int main()
{
	AscSeqChecker checker;
	checker.demo();
	system("pause");
	return 0;
}