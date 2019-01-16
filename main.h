#include<string>
#include<iostream>
#include<vector>
#include <fstream>
#include <cmath>
#include<string.h>
using namespace std;

class image_processing_library{
public:
    vector<float> read_file(std::string s);
    vector<float> sigmoid(vector<float> v);
    vector<float> softmax(vector<float> v);
    vector<vector<float> > tanh(vector<vector<float> > m);
    vector<vector<float> > relu(vector<vector<float> > m);
    vector<vector<float> > maxpooling(vector<vector<float> > m, int width, int stride=1);
    vector<vector<float> > average_pooling(vector<vector<float> > m, int width, int stride=1);
    vector<vector<float> > reflect_kernel(vector<vector<float> > kernel);
    vector<vector<float> > convolve(vector<vector<float> > matrix, vector<vector<float> > kernel);
    vector<vector<float> > padding(vector<vector<float> > matrix, int pad);
    vector<vector<float> > matrix_multiply(vector<vector<float> > mat1, vector<vector<float> > mat2);
    vector < vector <float> > toeplitz_convolve(vector<vector<float> > matrix, vector<vector<float> > kernel);
    vector<vector<float> > read_matrix(string s, int rows);
};
