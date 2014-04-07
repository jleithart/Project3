#pragma once
#include "population.h"

#define NUM_GENERATIONS 500
class GeneticProgram
{
private:
	population *searchPop;
	population *selectPop;
	int TourneySize;

	void ComparePopulation();

public:
	void PrintPopulation(population *);
	void PrintPopulation();
	void PrintFitness();
	void Init();



	GeneticProgram(void);
	~GeneticProgram(void);

	void Select();
	void Search();
	int GetBestIndividualIndex();
	int TourneySelect();
	void Crossover(ant *, ant *);
	void Mutate(ant *);

	void CopyPopulation(population *, population *);
	void CalcFitness(population *);
	void PrintIndividual();

	void GetBestAndAverage();

	ant *CopyIndividual(ant *, ant *);

	ant *GetBest();

};

