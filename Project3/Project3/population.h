#ifndef POPULATION_H_
#define POPULATION_H_
#include "ant.h"

#define MAX_POPULATION 100

class population
{
private:
	ant *firstPopulation[MAX_POPULATION];

	int curIndex;


public:
	int fitnessPopulation[MAX_POPULATION];

	population(void);
	~population(void);

	void AddIndividual(ant *);
	ant *GetBestIndividual();
};

#endif

