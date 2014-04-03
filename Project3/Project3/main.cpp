
#include "GeneticProgram.h"
#include <iostream>
#include <time.h>

using namespace std;

int main(){
	srand(time(NULL));
//	ant *A1 = new ant();
//	A1->PrintBoard();

//	A1->Evaluate();
//	A1->PrintBoard();
	GeneticProgram *GP = new GeneticProgram();
	GP->Search();
	//ant *A1 = Search->GetBestIndividual();
	//A1->PrintBoard();
	system("PAUSE");
	return 0;
}