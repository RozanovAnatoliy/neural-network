#include "output_layer.h"

OutputLayer::OutputLayer(int num_neurons, int num_prev_neurons) : Layer(num_neurons, num_prev_neurons)
{
}

vector<double> OutputLayer::computeGradient(vector<double> &outputs, vector<double> &labels)
{
    vector<double> gradient(numNeurons);
    for (int i = 0; i < numNeurons; i++)
        gradient[i] = labels[i] - outputs[i];
    return gradient;
}

double OutputLayer::activateNeuron(vector<double> &sums, double sum)
{
    double output = softmax(sums, sum, numNeurons);
    return output;
}

double OutputLayer::softmax(vector<double> &sums, double sum, int n)
{
    double sumexp = 0.0;
    for (int i = 0; i < n; i++)
        sumexp += exp(sums[i]);
    double result = exp(sum) / sumexp;
    return result;
}

double OutputLayer::computeCrossEntropyError(vector<double> &output, vector<double> &labels)
{
    double sum = 0.0;
    for (int i = 0; i < numNeurons; i++) {
        sum += log(output[i]) * labels[i];
    }
    return -1.0 * sum;
}

