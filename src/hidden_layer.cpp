#include "hidden_layer.h"

HiddenLayer::HiddenLayer(int numNeurons, int numPrevNeurons) : Layer(numNeurons, numPrevNeurons)
{
}

double HiddenLayer::activateNeuron(vector<double> &sums, double sum)
{
    return hyperTanFunction(sum);
}

vector<double> HiddenLayer::computeGradient(vector<double> &layerOutputs,
    vector<double> &nextLayerWeightedSumErrors)
{
    vector<double> gradient(numNeurons);
    for (int i = 0; i < this->numNeurons; i++) {
        double derivative = derivativeHyperTanFunction(layerOutputs[i]);
        gradient[i] = nextLayerWeightedSumErrors[i] * derivative;
    }
    return gradient;
}

double HiddenLayer::hyperTanFunction(double x)
{
    return tanh(x);
}

double HiddenLayer::derivativeHyperTanFunction(double x)
{
    return (1.0 - x) * (1.0 + x);
}