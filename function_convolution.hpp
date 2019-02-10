//
//  functions.hpp
//  COP_1
//
//  Created by Poorva garg on 10/02/19.
//  Copyright © 2019 Poorva garg. All rights reserved.
//

#ifndef function_convolution_h
#define function_convolution_h

#include <vector>
using namespace std;
vector<float> sigmoid(vector<float> v);
vector<float> softmax(vector<float> v);
vector<vector<float> > tanh(vector<vector<float> > m);
vector<vector<float> > relu(vector<vector<float> > m);
vector<vector<float> > maxpooling(vector<vector<float> > m, int width, int stride=1);
vector<vector<float> > average_pooling(vector<vector<float> > m, int width, int stride=1);
vector<vector<float> > convolve(vector<vector<float> > matrix, vector<vector<float> > kernel);
vector<vector<float>> toeplitz_convolve(vector<vector<float> > matrix, vector<vector<float> > kernel, int option);
#endif /* function_convolution_h */
