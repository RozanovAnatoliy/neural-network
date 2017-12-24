#ifndef OUTPUT_LAYER_H
#define OUTPUT_LAYER_H

#include "layer.h"

class OutputLayer : public Layer
{
public:
    OutputLayer(int numNeurons, int numPrevNeurons);
    
    virtual double activateNeuron(vector<double> &sums, double sum);
    vector<double> computeGradient(vector<double> &outputs, vector<double> &labels);
    double computeCrossEntropyError(vector<double> &output, vector<double> &labels);

private:
    double softmax(vector<double> &sums, double sum, int n);
};

#endif