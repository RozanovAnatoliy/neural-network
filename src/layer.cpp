#include "layer.h"

#include <ctime>
#include <iostream>

Layer::Layer(int numNeurons, int numPrevNeurons)
{
    this->numNeurons = numNeurons;
    this->numPrevNeurons = numPrevNeurons;
    srand(time(0));
    for (int i = 0; i < numNeurons; i++)
        neurons.push_back(Neuron(numPrevNeurons, randVector(numPrevNeurons)));
}

vector<double> Layer::computeOutputs()
{
    vector<double> sums(numNeurons);
    vector<double> outputs(numNeurons);

    for (int i = 0; i < numNeurons; i++)
        sums[i] = neurons[i].getSum();

    for (int i = 0; i < numNeurons; i++) {
        outputs[i] = activateNeuron(sums, sums[i]);
        neurons[i].setOutput(outputs[i]);
    }

    this->outputs = outputs;
    return outputs;
}

void Layer::setInputs(vector<double> &inputs)
{
    for (int i = 0; i < numNeurons; i++)
        neurons[i].setInputs(inputs);
}

int Layer::getNumNeurons()
{
    return numNeurons;
}

int Layer::getNumPrevNeurons()
{
    return numPrevNeurons;
}

vector<double> Layer::getOutputs()
{
    return this->outputs;
}

void Layer::updateWeights(vector<double> &gradient, double learnRate)
{
    for (int i = 0; i < this->numNeurons; i++) {
        neurons[i].updateWeights(gradient[i], learnRate);
    }
}

void Layer::updateBiases(vector<double>& gradient, double learnRate)
{
    for (int i = 0; i < this->numNeurons; i++) {
        neurons[i].updateBias(gradient[i], learnRate);
    }
}

vector<double> Layer::computeWeightedSumErrors(vector<double> &gradient)
{
    vector<double> weightedErrors(numPrevNeurons);
    for (int j = 0; j < numPrevNeurons; j++) {
        weightedErrors[j] = 0.0;
        for (int i = 0; i < numNeurons; i++) {
            weightedErrors[j] += neurons[i].getIdxWeight(j) * gradient[i];
        }
    }
    return weightedErrors;
}

vector<double> Layer::randVector(int n)
{
    vector<double> vec;
    for (int i = 0; i < n; i++) {
        double rand = -0.5 + (double)std::rand() / RAND_MAX;
        vec.push_back(rand);
    }
    return vec;
}
