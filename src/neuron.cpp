#include "neuron.h"

#include <cmath>

Neuron::Neuron(int numPrevNeurons, vector<double> &weights) {
    this->numPrevNeurons = numPrevNeurons;
    this->output = 0.;
    this->bias = 0.0;

    weights.resize(numPrevNeurons);
    inputs.resize(numPrevNeurons);

    this->weights = weights;
}

Neuron::Neuron(vector<double> &weights, vector<double> &inputs, int numPrevNeurons) {
    this->numPrevNeurons = numPrevNeurons;
    this->weights = weights;
    this->inputs = inputs;
    this->output = 0.;
    this->bias = 0.0;
}

void Neuron::setInputs(vector<double> &inputs)
{
    this->inputs = inputs;
}

void Neuron::setOutput(double output)
{
    this->output = output;
}

double Neuron::getOutput()
{
    return output;
}

double Neuron::getIdxWeight(int idx)
{
    return weights[idx];
}

double Neuron::getBias()
{
    return this->bias;
}

int Neuron::getNumPrevNeurons()
{
    return numPrevNeurons;
}

vector<double> Neuron::getWeights()
{
    return weights;
}

double Neuron::getSum()
{
    double sum = bias;
    for (int i = 0; i < numPrevNeurons; i++)
        sum += inputs[i] * weights[i];
    return sum;
}

void Neuron::updateBias(double gradient, double learnRate)
{
    this->bias += learnRate * gradient;
}

void Neuron::updateWeights(double gradient, double learnRate)
{
    for (int i = 0; i < this->numPrevNeurons; i++)
        weights[i] += learnRate * gradient * inputs[i];
}