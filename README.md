# Fully connected neural network

Fully connected neural network with one hidden layer for classification of handwritten digits.  
Activate function on output layer: softmax  
Error on output layer: cross-entropy  
MNIST dataset: http://yann.lecun.com/exdb/mnist/

## Instalation
### Windows
Create visual studio 2015 project in _build folder:  
&nbsp;&nbsp;&nbsp;&nbsp; build_windows.bat --cmake -G "Visual Studio 14 2015"  
Compile project. Binary file will be in _bin folder:  
&nbsp;&nbsp;&nbsp;&nbsp; build_windows.bat --build  
### Linux
cmake .  
make  

## Usage
NeuralNetwork.exe options  
Options:  
1. Path to train images (default: ..\\data\\train-images.idx3-ubyte):  
&nbsp;&nbsp;&nbsp;&nbsp; --trainImages=string  
2. Path to train labels (default: ..\\data\\train-labels.idx1-ubyte):  
&nbsp;&nbsp;&nbsp;&nbsp; --trainLabels=string  
3. Path to test images (default: ..\\data\\t10k-images.idx3-ubyte):  
&nbsp;&nbsp;&nbsp;&nbsp; --testImages=string  
4. Path to test labels (default: ..\\data\\t10k-labels.idx1-ubyte):  
&nbsp;&nbsp;&nbsp;&nbsp; --testLabels=string  
5. Min cross entropy error in train (default: 0.005):  
&nbsp;&nbsp;&nbsp;&nbsp; --minError=double  
6. Max epoches in train (default: 25):  
&nbsp;&nbsp;&nbsp;&nbsp; --maxEpoches=integer  
7. Learn rate (default: 0.008):  
&nbsp;&nbsp;&nbsp;&nbsp; --learnRate=double  
8. Num hidden neurons (default: 300):  
&nbsp;&nbsp;&nbsp;&nbsp; --numHiddenNeurons=integer

Example:  
NeuralNetwork.exe --trainImages=train-images.idx3-ubyte --minError=0.05 --numHiddenNeurons=500  

## Results (default parameters)
train accuracy: 0.999517  
test accuracy: 0.9715,  
where accuracy = number of correct classifications / (number of correct classifications + number of incorrect classifications)