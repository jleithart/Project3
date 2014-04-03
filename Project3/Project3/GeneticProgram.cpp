#include "GeneticProgram.h"


GeneticProgram::GeneticProgram(void)
{
	searchPop = new population();
	selectPop = new population();
	TourneySize = 3;
}


GeneticProgram::~GeneticProgram(void)
{
}

void GeneticProgram::Init(){
	searchPop->FillFitness();
}

void GeneticProgram::PrintPopulation(){
//	searchPop->Output();
}

void GeneticProgram::PrintPopulation(population *pop){
	pop->Output();
}

void GeneticProgram::PrintFitness(){
//	saerchPop->OutputFitness();
}

void GeneticProgram::Search(){
	ant *bestAnt = NULL;
	int bestIndex;

	searchPop->OutputFitness();
	searchPop->Output();
	std::cout << std::endl << std::endl;
	for(int i = 0; i < NUM_GENERATIONS; i++){
		selectPop->ResetPopulation();

		bestIndex = GetBestIndividualIndex();
		bestAnt = searchPop->GetIndividual(bestIndex);
		selectPop->AddIndividual(bestAnt);
		selectPop->AddIndividual(bestAnt);

		while(selectPop->curIndex < MAX_POPULATION){
			Select();
		}
		selectPop->FillFitness();
		selectPop->OutputFitness();
		selectPop->Output();
		system("PAUSE");
		CopyPopulation(selectPop, searchPop);
	}
}

void GeneticProgram::GetBestAndAverage(){
	
}

void GeneticProgram::CalcFitness(population *pop){
	pop->FillFitness();
}

void GeneticProgram::Select(){
	int firstWinnerIndex = TourneySelect();
	int secondWinnerIndex = TourneySelect();

	ant *firstAnt = searchPop->GetIndividual(firstWinnerIndex);
	ant *secondAnt = searchPop->GetIndividual(secondWinnerIndex);

	Crossover(firstAnt, secondAnt);

	Mutate(firstAnt);
	Mutate(secondAnt);
	selectPop->AddIndividual(firstAnt);
	selectPop->AddIndividual(secondAnt);
}

int GeneticProgram::GetBestIndividualIndex(){
	int index = 0;
	for(int i = 0; i < MAX_POPULATION; i++){
		if(searchPop->fitnessPopulation[i] > searchPop->fitnessPopulation[index]){
			index = i;
		}
	}
	return index;
}

int GeneticProgram::TourneySelect(){
	int winningIndex = rand()%MAX_POPULATION;
	int tmpIndex;

	for(int i = 0; i < TourneySize; i++){
		tmpIndex = rand()%MAX_POPULATION;
		if(searchPop->fitnessPopulation[tmpIndex] > searchPop->fitnessPopulation[winningIndex]){
			winningIndex = tmpIndex;
		}
	}

	return winningIndex;
}

void GeneticProgram::Crossover(ant *first, ant *second){
	//do this
}

void GeneticProgram::Mutate(ant *ant){
	// traverse through tree and mutate
	ant->mutate();

}

//ant * GeneticProgram::CopyIndividual(){}

void GeneticProgram::CopyPopulation(const population *i_pop, population *m_pop){
	for(int i = 0; i < MAX_POPULATION; i++){
		//copy each individual
	}
}