#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"

#include <vector>

class Layer
{
public:
    Layer(int numNeurons, int numPrevNeurons);

    int getNumNeurons();
    int getNumPrevNeurons();
    vector<double> getOutputs();

    vector<double> computeOutputs();
    void setInputs(vector<double> &inputs);
    void updateWeights(vector<double> &gradient, double learnRate);
    void updateBiases(vector<double> &gradient, double learnRate);
    vector<double> computeWeightedSumErrors(vector<double> &gradient);

protected:
    vector<Neuron> neurons;
    vector<double> outputs;
    int numNeurons;
    int numPrevNeurons;

    virtual double activateNeuron(vector<double> &sums, double sum) { return 0; }
    vector<double> randVector(int n);
};

#endif