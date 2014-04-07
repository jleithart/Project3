
#include "GeneticProgram.h"
#include <iostream>
#include <time.h>

using namespace std;

int main(){
	srand((unsigned)time(NULL));
//	ant *A1 = new ant();
//	A1->PrintBoard();

//	A1->Evaluate();
//	A1->PrintBoard();
	GeneticProgram *GP = new GeneticProgram();
	GP->Search();
	GP->GetBestAndAverage();
	system("PAUSE");
	return 0;
}