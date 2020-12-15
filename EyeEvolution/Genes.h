#pragma once
#include <vector>

using namespace std;
class Gene
{

	vector<double> code;

public:

	vector<double> weights;
	vector<double> eye_positions;
	
	Gene()
	{

	}

	void InitializeRandom(int numEyes, int numWeights)
	{
		weights.clear();
		eye_positions.clear();
		for (int i = 0; i < numEyes; i++)
		{
			eye_positions.push_back((float)rand() / RAND_MAX);
		//	cout << eye_positions[0];
		}


		for (int i = 0; i < numWeights; i++)
		{
			weights.push_back((float)rand() / RAND_MAX);
		}
		
	}


	Gene(vector<double> p,vector<double> w)
	{
		eye_positions = p;
		weights = w;
	}

	vector<double> GetEyePositions()
	{

		return eye_positions;
	}
};

class ChildrenPair
{

public:
	Gene gene1, gene2;
	ChildrenPair(Gene g1, Gene g2)
	{
		gene1 = g1; gene2 = g2;
	}
};

static class GeneticAlgorithm
{

public:
	static ChildrenPair Crossover(Gene g1, Gene g2)
	{
		//weights
		vector <double> c3;
		vector <double> c4;
		vector<double> c1 = g1.weights; vector<double>c2 = g2.weights;
		int crossoverPoint = rand() % (c1.size() - 1);
		for (int i = 0; i < c1.size(); i++)
		{
			if (i < crossoverPoint)
			{
				c3.push_back(c1[i]);
				c4.push_back(c2[i]);
			}
			else
			{
				c3.push_back(c2[i]);
				c4.push_back(c1[i]);
			}
		}

		//eye positions

		vector <double> c5;
		vector <double> c6;
		vector<double> c7 = g1.eye_positions; vector<double>c8 = g2.eye_positions;
		crossoverPoint = rand() % (c7.size() - 1);
		for (int i = 0; i < c7.size(); i++)
		{
			if (i < crossoverPoint)
			{
				c5.push_back(c7[i]);
				c6.push_back(c8[i]);
			}
			else
			{
				c5.push_back(c8[i]);
				c6.push_back(c7[i]);
			}
		}
		Gene Gene1(c5,c3);
		Gene Gene2(c6, c4);

		ChildrenPair C(Gene1, Gene2);
		return C;
	}
};

