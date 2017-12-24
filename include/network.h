#ifndef NETWORK_H
#define NETWORK_H

#include "hidden_layer.h"
#include "output_layer.h"

class Network
{
public:
    Network(int numInputNeurons, int numHiddenNeurons, int numOutputNeurons);
    ~Network();

    double MeanCrossEntropyError(vector<vector<double>> trainInputs, vector<vector<double>> trainLabels);
    vector<double> test(vector<double> &inputs);
    double train(vector<vector<double>> trainInputs, vector<vector<double>> trainLabels,
        int maxEpoches, double minError, double learnRate);

private:
    HiddenLayer *hiddenLayer;
    OutputLayer *outputLayer;

    vector<double> forwardPropagation();
    void backwardPropagation(vector<double> &hiddenOutputs, vector<double> &outputs,
        vector<double> &expectredValues, double learnRate);
};

#endif