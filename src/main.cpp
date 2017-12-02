#include "utils.h"
#include "network.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    int numInputNeurons;
    vector<vector<double>> trainImages;
    vector<vector<double>> trainLabels;
    vector<vector<double>> testImages;
    vector<vector<double>> testLabels;

    int maxEpoches = 25;
    double minError = 0.005;
    double learnRate = 0.008;
    int numOutputNeurons = 10;
    int numHiddenNeurons = 300;
    string pathToTrainImages = "..\\data\\train-images.idx3-ubyte";
    string pathToTrainLabels = "..\\data\\train-labels.idx1-ubyte";
    string pathToTestImages = "..\\data\\t10k-images.idx3-ubyte";
    string pathToTestLabels = "..\\data\\t10k-labels.idx1-ubyte";

    for (int i = 1; i < argc; i++) {
        vector<string> argNameAndValue = split(argv[i], "=");
        string argName = argNameAndValue[0];
        string argValue = argNameAndValue[1];

        if (argName == "--trainImages") {
            pathToTrainImages = argValue;
        } else if (argName == "--trainLabels") {
            pathToTrainLabels = argValue;
        } else if (argName == "--testImages") {
            pathToTestImages = argValue;
        } else if (argName == "--testLabels") {
            pathToTestLabels = argValue;
        } else if (argName == "--minError") {
            minError = stod(argValue);
        } else if (argName == "--numHiddenNeurons") {
            numHiddenNeurons = stoi(argValue);
        } else if (argName == "--learnRate") {
            learnRate = stod(argValue);
        } else if (argName == "--maxEpoches") {
            maxEpoches = stoi(argValue);
        } else {
            cout << endl<< "Incorrect command argument: " << argv[i] << endl;
            cout << "Usage: programName <options>" << endl;
            cout << "Options:" << endl;
            cout << "--trainImages=<string>          Path to train images" << endl;
            cout << "--trainLabels=<string>          Path to train labels" << endl;
            cout << "--testImages=<string>           Path to test images" << endl;
            cout << "--testLabels=<string>           Path to test labels" << endl;
            cout << "--minError=<double>             Min cross entropy error in train" << endl;
            cout << "--maxEpoches=<integer>          Max epoches in train" << endl;
            cout << "--learnRate=<double>            Learn rate" << endl;
            cout << "--numHiddenNeurons=<integer>    Num hidden neurons" << endl;
            cout << "Example:" << endl;
            cout << "NeuralNetwork.exe --trainImages=train-images.idx3-ubyte --minError=0.05" << endl;
            return 1;
        }
    }
    cout << "path to train images = " << pathToTrainImages << endl;
    cout << "path to train labels = " << pathToTrainLabels << endl;
    cout << "path to test images = " << pathToTestImages << endl;
    cout << "path to test labels = " << pathToTestLabels << endl;
    cout << "min cross entropy error in train = " << minError << endl;
    cout << "max epoches in train = " << maxEpoches << endl;
    cout << "learn rate = " << learnRate << endl;
    cout << "num hidden neurons = " << numHiddenNeurons << endl << endl;

    readMnist(pathToTrainImages, trainImages);
    readMnistLabel(pathToTrainLabels, trainLabels);
    readMnist(pathToTestImages, testImages);
    readMnistLabel(pathToTestLabels, testLabels);
    numInputNeurons = trainImages[0].size();

    Network network(numInputNeurons, numHiddenNeurons, numOutputNeurons);
    network.train(trainImages, trainLabels, maxEpoches, minError, learnRate);

    int outputMaxIdx, labelMaxIdx;
    vector<vector<double>> outputs(testImages.size());
    for (size_t i = 0; i < testImages.size(); i++) {
        outputs[i] = network.test(testImages[i]);
        outputMaxIdx = getMaxIdx(outputs[i]);
        labelMaxIdx = getMaxIdx(outputs[i]);
    }
    double accuracy = computeAccuracy(outputs, testLabels);
    cout << "accuracy = " << accuracy << endl;
    return 0;
}
