#include "function_convolution.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct mat_bias{
    vector<vector<vector<vector<float>>>> matrix;
    vector<float> bias;
};

mat_bias read_matrix(string s, int rows, int columns, int depth, int channels)
{
    try
    {
        vector<float> v;
        ifstream infile;
        infile.open(s);
        if(!infile)
        {
            throw "Error in file opening, kindly check the path of the file given";
        }
        string sd;
        float data;
        while(getline(infile, sd))
        {
            data=stof(sd);
            v.push_back(data);
        }
        vector<vector<vector<vector< float > > > > ans(channels,vector<vector<vector< float > > >(depth, (vector<vector< float > >(rows, vector<float>(columns,0)))));
        vector<float> bias_ans;
        int counter=0;
        if(channels*rows*columns*depth<=v.size())
        {
            for(int x=0; x<channels; x++)
            {
                for(int k=0; k<depth;k++)
                {
                    for(int i=0;i<rows;i++)
                    {
                        for(int j=0;j<columns;j++)
                        {
                            ans[x][k][i][j]=v[counter];
                            counter++;
                        }
                    }
                }
            }
            while(counter<v.size())
            {
                bias_ans.push_back(v[counter]);
                counter++;
            }
        }
        struct mat_bias return_out = {ans, bias_ans};
        return return_out;
    }
    catch (std::invalid_argument)
    {
        throw "Either the data in your file is not valid or you have given a larger number of rows.";
    }
    catch (const char* msg)
    {
        throw msg;
    }
}

vector<vector<float>> matrix_elementwise_add(vector<vector<float>> a, vector<vector<float>> b)
{
    //Assuming a.size()=b.size() and a[0].size()=b[0].size()
    vector<vector<float>> result(a.size(),vector<float>(a[0].size(),0));
    if(a.size()==b.size() && a[0].size()==b[0].size())
    {
        for(int i=0; i<a.size(); i++)
        {
            for(int j=0; j<a[0].size(); j++)
            {
                result[i][j]=a[i][j]+b[i][j];
            }
        }
    }
    else
    {
        cout<<"Matrix Dimensions aren't equal";
    }

    return result;
}

vector<vector<vector<float>>> convolution_layer(vector<vector<vector<float>>> inputs, vector<vector<vector<vector<float>>>> filters, vector<float> bias)
{
    //Assuming filters[0].size()=inputs.size()
    int output_dim = inputs[0].size()-filters[0][0].size()+1;
    int n = inputs.size();
    vector<vector<vector<float>>> output(filters.size(),vector<vector<float>>(output_dim,vector<float>(output_dim,0)));
    for(int j=0; j<filters.size(); j++)
    {
        vector<vector<vector<float>>> intermediate_output(n,vector<vector<float>>(output_dim,vector<float>(output_dim,0)));
        for(int i=0; i<n; i++)
        {
            intermediate_output[i]=convolve(inputs[i], filters[j][i]);
        }
        vector<vector<float>> summed_matrix(output_dim,vector<float>(output_dim,0));
        for(int k=0;k<n;k++)
        {
            summed_matrix=matrix_elementwise_add(summed_matrix,intermediate_output[k]);
        }
        vector<vector<float>> bias_matrix(output_dim,vector<float>(output_dim,bias[j]));
        summed_matrix=matrix_elementwise_add(summed_matrix,bias_matrix);
        output[j]=summed_matrix;
    }
    return output;
}

vector<vector<vector<float> > > pool_layer (vector<vector<vector< float> > > input)
{
    int depth = input.size();
    int rows = input[0].size();

    vector<vector<vector< float > > > ans(depth, (vector<vector< float > >(rows/2, vector<float>(rows/2,0))));

    for (int j=0; j<input.size();j++)
    {
        ans[j] = maxpooling(input[j],2,2);
    }
    return ans;
}

vector<vector<vector< float> > > relu_layer(vector<vector<vector<float> > > input)
{
    int depth =  input.size();
    int rows = input[0].size();
    vector<vector<vector< float > > > ans(depth, (vector<vector< float > >(rows, vector<float>(rows,0))));
    for (int j=0; j<input.size();j++)
    {
        ans[j] = relu(input[j]);
    }
    return ans;
}

vector<float> lenet(string image, string conv1, string conv2, string fc1, string fc2)
{
    mat_bias input_image = read_matrix(image,28,28,1,1);
    mat_bias convolve_layer1=read_matrix(conv1,5,5,1,20);
    mat_bias convolve_layer2=read_matrix(conv2,5,5,20,50);
    mat_bias fc_layer1=read_matrix(fc1,4,4,50,500);
    mat_bias fc_layer2=read_matrix(fc2,1,1,500,10);

    vector<vector<vector<float>>> cv1_output = convolution_layer((input_image.matrix)[0], convolve_layer1.matrix, convolve_layer1.bias);
    vector<vector<vector<float>>> pool1_output = pool_layer(cv1_output);
    vector<vector<vector<float>>> cv2_output = convolution_layer(pool1_output, convolve_layer2.matrix, convolve_layer2.bias);
    vector<vector<vector<float>>> pool2_output = pool_layer(cv2_output);
    vector<vector<vector<float>>> fc1_output = convolution_layer(pool2_output, fc_layer1.matrix, fc_layer1.bias);
    vector<vector<vector<float>>> relu1_output = relu_layer(fc1_output);
    vector<vector<vector<float>>> fc2_output = convolution_layer(relu1_output, fc_layer2.matrix, fc_layer2.bias);
    vector<float> final_output(fc2_output.size(), 0);
    for(int i=0; i<fc2_output.size();i++)
    {
        final_output[i]=fc2_output[i][0][0];
    }
    vector<float> ans=softmax(final_output);
    return ans;
}
