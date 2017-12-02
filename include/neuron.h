#ifndef NEURON_H
#define NEURON_H

#include <vector>

using namespace std;

class  Neuron
{
public:

    Neuron() {};
    Neuron(int numPrevNeurons, vector<double> &weights);
    Neuron(vector<double> &weights, vector<double> &inputs, int numPrevNeurons);

    double getBias();
    int getNumPrevNeurons();
    vector<double> getWeights();
    double getOutput();
    double getIdxWeight(int idx);
    void setInputs(vector<double> &inputs);
    void setOutput(double output);

    void updateBias(double gradient, double learnRate);
    void updateWeights(double gradient, double learnRate);
    double getSum();

private:
    int numPrevNeurons;
    vector<double> weights;
    vector<double> inputs;
    double bias;
    double output;
};

#endif