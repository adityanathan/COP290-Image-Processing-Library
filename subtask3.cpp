//
//  subtask3.cpp
//  COP_1
//
//  Created by Poorva garg on 10/02/19.
//  Copyright © 2019 Poorva garg. All rights reserved.
//

#include <stdio.h>
#include <vector>
#
using namespace std;

vector<vector<vector<float> > > Pool_layer (vector<vector<vector< float> > > input)
{
    int depth =  static_cast<int>(input.size());
    int rows = static_cast<int>(input[0].size());
    
    vector<vector<vector< float > > > ans(depth, (vector<vector< float > >(rows/2, vector<float>(rows/2,0))));
    
    for (int j=0; j<input.size();j++)
    {
        ans[j] = average_pooling(input[j],2,2);
    }
    return ans;
}

vector<vector<vector< float> > > relu_layer(vector<vector<vector<float> > > input)
{
    int depth =  static_cast<int>(input.size());
    int rows = static_cast<int>(input[0].size());
    vector<vector<vector< float > > > ans(depth, (vector<vector< float > >(rows, vector<float>(rows,0))));
    for (int j=0; j<input.size();j++)
    {
        ans[j] = relu(input[j]);
    }
    return ans;
    return ans;
}


