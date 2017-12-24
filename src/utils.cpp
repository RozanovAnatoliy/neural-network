#include "utils.h"

#include <fstream>

int ReverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return((int) ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void readMnist(string filename, vector<vector<double> > &vec)
{
    ifstream file(filename, ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*)&magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*)&number_of_images, sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        file.read((char*)&n_rows, sizeof(n_rows));
        n_rows = ReverseInt(n_rows);
        file.read((char*)&n_cols, sizeof(n_cols));
        n_cols = ReverseInt(n_cols);
        for (int i = 0; i < number_of_images; ++i)
        {
            vector<double> tp;
            for (int r = 0; r < n_rows; ++r)
            {
                for (int c = 0; c < n_cols; ++c)
                {
                    unsigned char temp = 0;
                    file.read((char*)&temp, sizeof(temp));
                    tp.push_back((double)temp / 255.0);
                }
            }
            vec.push_back(tp);
        }
    }
}

void readMnistLabel(string filename, vector<vector<double>> &vec)
{
    ifstream file (filename, ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        for(int i = 0; i < number_of_images; ++i)
        {
            vector<double> tp(10);
            unsigned char temp = 0;
            file.read((char*) &temp, sizeof(temp));
            tp[(int)temp] = 1.0;
            vec.push_back(tp);
        }
    }
}

double computeAccuracy(vector<vector<double>> outputs, vector<vector<double>> labels)
{
    int outputMaxIdx, labelMaxIdx;
    int numCorrect = 0;
    for (size_t i = 0; i < outputs.size(); i++) {
        outputMaxIdx = getMaxIdx(outputs[i]);
        labelMaxIdx = getMaxIdx(labels[i]);
        if (outputMaxIdx == labelMaxIdx) {
            numCorrect++;
        }
    }
    double accuracy = (double)numCorrect / outputs.size();
    return accuracy;
}

int getMaxIdx(vector<double> vec) {
    int maxIdx = 0;
    double max = vec[0];
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] > max) {
            max = vec[i];
            maxIdx = i;
        }
    }
    return maxIdx;
}
vector<string> split(string str, string delimiter)
{
    vector<string> result(2);

    int delimiterPosition = str.find(delimiter);
    if (delimiterPosition != string::npos) {
        result[0] = str.substr(0, delimiterPosition);
        result[1] = str.substr(delimiterPosition + 1, str.size());
    }
    return result;
}