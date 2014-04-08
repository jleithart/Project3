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

	
	debugFile.open("debug.txt");
	searchPop->FillFitness();
	searchPop->OutputFitness();
	std::cout << std::endl;
	//system("PAUSE");

	for(int i = 0; i < NUM_GENERATIONS; i++){
		selectPop->ResetPopulation();

		bestIndex = GetBestIndividualIndex();
		bestAnt = searchPop->GetIndividual(bestIndex);
		bestAnt->Evaluate();
		selectPop->AddIndividual(bestAnt);
		selectPop->AddIndividual(bestAnt);
		//system("PAUSE");
		while(selectPop->curIndex < MAX_POPULATION){
			Select();
		}
		
		// THIS IS WORKING NOW
		CopyPopulation(selectPop, searchPop);
		searchPop->FillFitness();
		if(i % 5 == 0){
			bestAnt = searchPop->GetBestIndividual();
			debugFile << i << " " << searchPop->GetAverageFitness() << " " << bestAnt->GetFood() << std::endl;
		}
		
	}
	debugFile.close();
}

void GeneticProgram::GetBestAndAverage(){
	ant *bestAnt = searchPop->GetBestIndividual();
	std::cout << "The average fitness is " << searchPop->GetAverageFitness() << std::endl;
	std::cout << "The best fitness is " << bestAnt->GetFood() << std::endl;
	bestAnt->PrintBoard();
	//bestAnt->root->PrintTree(bestAnt->root);
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

	//GetIndividual might be shallow copying and that's why we're getting weird results
	//write a node copy function
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
			//std::cout << "new:: " << searchPop->fitnessPopulation[i] << std::endl;
			//std::cout << "old:: " << searchPop->fitnessPopulation[index] << std::endl;
			index = i;
		}
	}
	//system("PAUSE");
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
	int firstNodeNum = rand() % first->GetSize();
	node *firstNode = first->root;

	std::stack<node *> firstStack;
	firstStack.push(firstNode);
	while(firstNodeNum > 0 && !firstStack.empty()){
		if(firstNode->left != NULL){
			firstStack.push(firstNode->left);
		}
		if(firstNode->mid != NULL){
			firstStack.push(firstNode->mid);
		}
		if(firstNode->right != NULL){
			firstStack.push(firstNode->right);
		}

		firstNode = firstStack.top();
		firstStack.pop();
		firstNodeNum--;
	}
	while(!firstStack.empty()){
		firstStack.pop();
	}

	//firstNode should be a random node
	//do the same with second node
	node *secondNode = second->root;
	int secondNodeNum = rand() % second->GetSize();

	std::stack<node *> secondStack;
	secondStack.push(secondNode);
	while(secondNodeNum > 0 && !secondStack.empty()){
		if(secondNode->left != NULL){
			secondStack.push(secondNode->left);
		}
		if(secondNode->mid != NULL){
			secondStack.push(secondNode->mid);
		}
		if(secondNode->right != NULL){
			secondStack.push(secondNode->right);
		}

		secondNode = secondStack.top();
		secondStack.pop();
		secondNodeNum--;
	}
	while(!secondStack.empty()){
		secondStack.pop();
	}

	//now we have both subtree nodes to swap
	node *tmpNode = firstNode->copyTree(firstNode, firstNode->parent);
	firstNode = firstNode->copyTree(secondNode, firstNode->parent);
	secondNode = secondNode->copyTree(tmpNode, secondNode->parent);

	//make sure the parent has the right spot
	if(firstNode->parent != NULL){
		switch(firstNode->loc){
			case nleft:
				firstNode->parent->left = firstNode;
				break;
			case nmid:
				firstNode->parent->mid = firstNode;
				break;
			case nright:
				firstNode->parent->right = firstNode;
				break;
		}
	}
	else{
		firstNode->loc = root;
	}
	if(secondNode->parent != NULL){
		switch(secondNode->loc){
			case nleft:
				secondNode->parent->left = secondNode;
				break;
			case nmid:
				secondNode->parent->mid = secondNode;
				break;
			case nright:
				secondNode->parent->right = secondNode;
				break;
		}
	}
	else{
		secondNode->loc = root;
	}

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
		m_pop->firstPopulation[i] = i_pop->firstPopulation[i];
		//CopyIndividual(i_pop->GetIndividual(i), m_pop->GetIndividual(i));
		//m_pop[i] = CopyIndividual(i_pop->GetIndividual(i));
	}
}