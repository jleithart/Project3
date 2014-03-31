#include "population.h"


population::population(void)
{
	for(int i = 0; i < MAX_POPULATION; i++){
		firstPopulation[i] = new ant();
		firstPopulation[i]->Evaluate();
		fitnessPopulation[i] = firstPopulation[i]->GetFood();
	}
}

ant *population::GetBestIndividual(){
	int tmpMax = fitnessPopulation[0];
	int bestIndex = 0;

	for(int i = 1; i < MAX_POPULATION; i++){
		if(tmpMax < fitnessPopulation[i]){
			tmpMax = fitnessPopulation[i];
			bestIndex = i;
		}
		
	}
	std::cout << fitnessPopulation[bestIndex] << std::endl;
	return firstPopulation[bestIndex];
}

population::~population(void)
{
}
