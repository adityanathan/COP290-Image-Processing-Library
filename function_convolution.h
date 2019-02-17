//
//  functions.hpp
//  COP_1
//
//  Created by Poorva garg on 10/02/19.
//  Copyright © 2019 Poorva garg. All rights reserved.
//

#ifndef function_convolution_h
#define function_convolution_h
#include <string>
#include <vector>
using namespace std;
vector<float> sigmoid(vector<float> v);
vector<float> softmax(vector<float> v);
vector<vector<float> > tanh(vector<vector<float> > m);
vector<vector<float> > relu(vector<vector<float> > m);
vector<vector<float> > maxpooling(vector<vector<float> > m, int width, int stride);
vector<vector<float> > average_pooling(vector<vector<float> > m, int width, int stride);
vector<vector<float> > convolve(vector<vector<float> > matrix, vector<vector<float> > kernel);
vector<vector<float>> toeplitz_convolve(vector<vector<float> > matrix, vector<vector<float> > kernel, int option);

vector<float> lenet(string image, string conv1, string conv2, string fc1, string fc2);

#endif /* function_convolution_h */
