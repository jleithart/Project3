#include "GeneticProgram.h"


GeneticProgram::GeneticProgram(void)
{
	searchPop = new population();
	selectPop = new population();
	TourneySize = 3;
	Init();
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

	
	searchPop->FillFitness();
	searchPop->OutputFitness();
	std::cout << std::endl;
	system("PAUSE");

	for(int i = 0; i < NUM_GENERATIONS; i++){
		selectPop->ResetPopulation();

		bestIndex = GetBestIndividualIndex();
		bestAnt = searchPop->GetIndividual(bestIndex);
		std::cout << "before eval:: " << bestAnt->GetFood() << std::endl;
		bestAnt->Evaluate();
		std::cout << "after eval:: " <<  bestAnt->GetFood() << std::endl;
		selectPop->AddIndividual(bestAnt);
		selectPop->AddIndividual(bestAnt);
		system("PAUSE");
		while(selectPop->curIndex < MAX_POPULATION){
			Select();
		}
		//selectPop->FillFitness();
		std::cout << std::endl;
		//selectPop->OutputFitness();
		system("PAUSE");
		/*
		* SOMETHING IS REALLY GOING WRONG WHEN I EVALUATE
		* MY GUESS IS THE COPY ISN'T WORKING PROPERLY
		*/
		//selectPop->Output();
		CopyPopulation(selectPop, searchPop);
		std::cout << std::endl;
		searchPop->FillFitness();
		searchPop->OutputFitness();
		ComparePopulation();
		system("PAUSE");
	}
}

void GeneticProgram::GetBestAndAverage(){
	
}

void GeneticProgram::CalcFitness(population *pop){
	pop->FillFitness();
}

void GeneticProgram::ComparePopulation(){
	ant *searchAnt = NULL;
	ant *selectAnt = NULL;
	for(int i = 0; i < MAX_POPULATION; i++){
		if(searchPop->fitnessPopulation[i] != selectPop->fitnessPopulation[i]){
			searchAnt = searchPop->GetIndividual(i);
			selectAnt = selectPop->GetIndividual(i);
			searchAnt->Evaluate();
			selectAnt->Evaluate();
			std::cout << "searchAnt " << i << ":: " << searchAnt->GetFood() << "! Fitness array:: " << searchPop->fitnessPopulation[i] << std::endl;
			std::cout << "selectAnt " << i << ":: " << selectAnt->GetFood() << "! Fitness array:: " << selectPop->fitnessPopulation[i] << std::endl;
			system("PAUSE");
		}
	}
}

void GeneticProgram::Select(){
	int firstWinnerIndex = TourneySelect();
	int secondWinnerIndex = TourneySelect();

	ant *firstAnt = searchPop->GetIndividual(firstWinnerIndex);
	ant *secondAnt = searchPop->GetIndividual(secondWinnerIndex);

	Crossover(firstAnt, secondAnt);

	Mutate(firstAnt);
	Mutate(secondAnt);

	std::cout << "before eval:: " << firstAnt->GetFood() << std::endl;
	firstAnt->Evaluate();
	std::cout << "after eval:: " <<  firstAnt->GetFood() << std::endl;

	selectPop->AddIndividual(firstAnt);
	selectPop->AddIndividual(secondAnt);
}

int GeneticProgram::GetBestIndividualIndex(){
	int index = 0;
	for(int i = 0; i < MAX_POPULATION; i++){
		if(searchPop->fitnessPopulation[i] > searchPop->fitnessPopulation[index]){
			std::cout << "new:: " << searchPop->fitnessPopulation[i] << std::endl;
			std::cout << "old:: " << searchPop->fitnessPopulation[index] << std::endl;
			index = i;
		}
	}
	system("PAUSE");
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

ant * GeneticProgram::CopyIndividual(ant * inputAnt, ant *outputAnt){
	node *tmp = inputAnt->GetRoot();
	outputAnt->SetRoot(tmp);
	/*
	inputAnt->Evaluate();
	outputAnt->Evaluate();
	if( inputAnt->GetFood() != outputAnt->GetFood()){
		inputAnt->PrintBoard();
		outputAnt->PrintBoard();
		system("PAUSE");
	}
	*/
	return NULL;
}

void GeneticProgram::CopyPopulation(population *i_pop, population *m_pop){
	for(int i = 0; i < MAX_POPULATION; i++){
		CopyIndividual(i_pop->GetIndividual(i), m_pop->GetIndividual(i));
		//m_pop[i] = CopyIndividual(i_pop->GetIndividual(i));
	}
}