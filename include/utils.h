#ifndef READ_MNIST_H
#define READ_MNIST_H

#include <vector>

using namespace std;

void readMnist(string filename, vector<vector<double>> &vec);
void readMnistLabel(string filename, vector<vector<double>> &vec);
int ReverseInt (int i);

vector<string> split(string str, string delimiter);
int getMaxIdx(vector<double >vec);
double computeAccuracy(vector<vector<double>> outputs, vector<vector<double>> labels);

#endif