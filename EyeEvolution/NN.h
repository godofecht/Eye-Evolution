#ifndef NN_H
#define NN_H

#include<vector>
#include<cmath>
#include<cassert>
#include<iostream>

using namespace std;

class Neuron;
typedef vector<Neuron> Layer;
class connection
{
public:
	double weight;
	double deltaweight;
};
class Neuron
{
	public:

	Neuron(unsigned numOutputs, unsigned myIndex)
	{
		for (unsigned c = 0; c < numOutputs; ++c) {
			m_outputWeights.push_back(connection());
			m_outputWeights.back().weight = randomWeight();
		}

		m_myIndex = myIndex;
	}
	void feedForward(Layer &prevLayer)
	{
		double sum = 0.0;

		// We sum the previous layer's output
		// Include the bias node from the previous layer.

		for (unsigned n = 0; n < prevLayer.size(); ++n) {
			sum += prevLayer[n].getOutputVal() *
				prevLayer[n].m_outputWeights[m_myIndex].weight;
		}

		m_outputVal = transferFunction(sum);
	}

	double getOutputVal()
	{
		return m_outputVal;
	}
	void setOutputVal(double n)
	{
		m_outputVal = n;
	}

	void calcHiddenGradients(const Layer& nextLayer)
	{
		double dow = sumDOW(nextLayer);
		m_gradient = dow * transferFunctionDerivative(m_outputVal);
	}
	void calcOutputGradients(double targetVal)
	{
		double delta = targetVal - m_outputVal;
		m_gradient = delta * transferFunctionDerivative(m_outputVal);
	}
	void updateInputWeights(Layer& prevLayer) //Function exists only to verify Neural Network's functionality. 
	{
		for (unsigned n = 0; n < prevLayer.size(); ++n) {
			Neuron& neuron = prevLayer[n];
			double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaweight;

			double newDeltaWeight =
				// Individual input is magnified by the gradient and train rate:
				eta
				* neuron.getOutputVal()
				* m_gradient
				// Also adding momentum = a fraction of the previous delta weight;
				+ alpha
				* oldDeltaWeight;

			neuron.m_outputWeights[m_myIndex].deltaweight = newDeltaWeight;
			neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
		}
	}





	double  eta = 0.15;
	double  alpha = 0.5;


	double m_recentAverageSmoothingFactor = 100.0;

	vector <connection> m_outputWeights;
private:
	double m_gradient;
	double m_outputVal;
	unsigned m_myIndex;

	double  randomWeight()
	{
		return (rand() / double(RAND_MAX));
	}
	double  sumDOW(const Layer& nextLayer) const
	{
		double sum = 0.0;

		// Sum our contributions of the errors at the nodes we feed.

		for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
			sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
		}

		return sum;
	}
	double  transferFunctionDerivative(double x)
	{
		return 1 - x * x;
	}
	double  transferFunction(double x)
	{
		return tanh(x);
	}
};


#endif