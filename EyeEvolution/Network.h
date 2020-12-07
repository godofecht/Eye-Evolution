#ifndef NETWORK_H
#define NETWORK_H

#include "NN.h"
#include <vector>

using namespace std;

class Network
{
	public:
		Network(const vector <unsigned> &topology);
		void backPropagate(const vector <double> &targetVals);
		void feedForward(vector <double> &inputVals);
		void getResults(vector <double> &resultVals);
		double getRecentAverageError(void) const { return m_recentAverageError; }

		vector<double> GetWeights() const;
		void PutWeights(vector<double> &weights);

	private:
		vector <Layer> m_layers;
		double m_gradient;
		double m_error;
		double m_recentAverageError;
		double m_recentAverageSmoothingFactor;
};
#endif