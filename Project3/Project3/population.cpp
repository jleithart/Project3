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

ant *population::GetIndividual(int index){
	return firstPopulation[index];
}

void population::FillFitness(){
	for(int i = 0; i < MAX_POPULATION; i++){
		firstPopulation[i]->Evaluate();
		fitnessPopulation[i] = firstPopulation[i]->GetFood();
	}
}
void population::OutputFitness(){
	for(int i = 0; i < MAX_POPULATION; i++){
		std::cout << fitnessPopulation[i] << std::endl;
	}
}

void population::ResetPopulation(){
	curIndex = 0;
	for(int i = 0; i < MAX_POPULATION; i++){
		firstPopulation[i] = NULL;
		fitnessPopulation[i] = 0;
	}
}

float population::GetAverageFitness(){
	float sum = 0;
	for(int i = 0; i < MAX_POPULATION; i++){
		sum += fitnessPopulation[i];
	}

	return sum/MAX_POPULATION;
}

void population::AddIndividual(ant *i_ant){
	if(curIndex < MAX_POPULATION){
		firstPopulation[curIndex] = i_ant;
		curIndex++;
	}
}

void population::Output(){
	ant *A1 = GetBestIndividual();
	std::cout << "Average Fitness:: " << GetAverageFitness() << std::endl;
	std::cout << "Best Fitness:: " << A1->GetFood() << std::endl;
	A1->PrintBoard();

}
