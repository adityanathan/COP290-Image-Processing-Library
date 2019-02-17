#ifndef _functions_h
#define _functions_h

#include <vector>
using namespace std;
vector<vector<float> > matrix_multiply_with_mkl(vector<vector<float> > mat1, vector<vector<float> > mat2);
vector<vector<float> > matrix_multiply_with_openblas(vector<vector<float> > mat1, vector<vector<float> > mat2);
vector<vector< float> > matrix_multiply_with_pthreads(vector<vector<float> > mat1, vector<vector< float> > mat2);

#endif
