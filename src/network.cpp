#include "network.h"

#include <ctime>
#include <iostream>

void Shuffle(vector<int> sequence) {
    for (size_t i = 0; i < sequence.size(); i++) {
        int r = i + (rand() % static_cast<int>((sequence.size() - 1) - i + 1));
        int tmp = sequence[r];
        sequence[r] = sequence[i];
        sequence[i] = tmp;
    }
}

Network::Network(int numInputNeurons, int numHiddenNeurons, int numOutputNeurons)
{
    hiddenLayer = new HiddenLayer(numHiddenNeurons, numInputNeurons);
    outputLayer = new OutputLayer(numOutputNeurons, numHiddenNeurons);
}

Network::~Network()
{
    delete hiddenLayer;
    delete outputLayer;
}

vector<double> Network::test(vector<double> &inputs)
{
    hiddenLayer->setInputs(inputs);
    vector<double> outputs = forwardPropagation();
    return outputs;
}

double Network::MeanCrossEntropyError(vector<vector<double>> trainInputs, vector<vector<double>> trainLabels)
{
    double sumError = 0.0;
    for (size_t i = 0; i < trainInputs.size(); i++) {
        vector<double> outputs = test(trainInputs[i]);
        for (size_t j = 0; j < outputs.size(); j++) {
            sumError += log(outputs[j]) * trainLabels[i][j];
        }
    }
    return -1.0 * sumError / trainInputs.size();
}

double Network::train(vector<vector<double>> trainInputs, vector<vector<double>> trainLabels,
    int maxEpoches, double minError, double learnRate)
{
    unsigned int startTime, endTime;
    vector<double> hiddenOutputs, outputs, labels;
    double currentError, meanCurrentError;
    for (int epoch = 0; epoch < maxEpoches; epoch++) {
        startTime = clock();
        currentError = 0.;
        vector<int> sequence(trainInputs.size());
        for (size_t i = 0; i < sequence.size(); i++) {
            sequence[i] = i;
        }
        Shuffle(sequence);
        for (size_t i = 0; i < trainInputs.size(); i++) {
            int idx = sequence[i];
            labels = trainLabels[idx];
            outputs = test(trainInputs[idx]);
            hiddenOutputs = hiddenLayer->getOutputs();
            backwardPropagation(hiddenOutputs, outputs, labels, learnRate);
        }
        meanCurrentError = MeanCrossEntropyError(trainInputs, trainLabels);
        endTime = clock();
        cout << "epoch = " << epoch << " | error = " << meanCurrentError << " | time (ms) = " 
            << endTime - startTime << endl;
        if (meanCurrentError < minError)
            break;
    }
    return meanCurrentError;
}

vector<double> Network::forwardPropagation()
{
    vector<double> hidden_outputs = hiddenLayer->computeOutputs();
    outputLayer->setInputs(hidden_outputs);
    vector<double> outputs = outputLayer->computeOutputs();
    return outputs;
}

void Network::backwardPropagation(vector<double> &hiddenOutputs ,vector<double> &outputs,
    vector<double> &labels, double learnRate)
{
    vector<double> outputGradiend = outputLayer->computeGradient(outputs, labels);
    outputLayer->updateWeights(outputGradiend, learnRate);
    outputLayer->updateBiases(outputGradiend, learnRate);
    vector<double> outputWeightedSumErrors = outputLayer->computeWeightedSumErrors(outputGradiend);
    vector<double> hiddenGradient = hiddenLayer->computeGradient(hiddenOutputs, outputWeightedSumErrors);
    hiddenLayer->updateWeights(hiddenGradient, learnRate);
    hiddenLayer->updateBiases(hiddenGradient, learnRate);
}
