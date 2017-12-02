#ifndef HIDDEN_LAYER_H
#define HIDDEN_LAYER_H

#include "layer.h"

class HiddenLayer : public Layer
{
public:
    HiddenLayer(int numNeurons, int numPrevNeurons);

    vector<double> computeGradient(vector<double> &layerOutputs, vector<double> &nextLayerWeightedSumErrors);
    virtual double activateNeuron(vector<double> &sums, double sum);

private:
    double hyperTanFunction(double x);
    double derivativeHyperTanFunction(double x);
};

#endif