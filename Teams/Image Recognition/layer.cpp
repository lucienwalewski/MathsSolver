#include <bits/stdc++.h>
#include "layer.h"

Layer::Layer(int num_in, int num_out, activationFunction a = SIGMOID)
{
    this->num_in = num_in;
    this->num_out = num_out;
    act = a;
    weight = new double*[num_in];
    diff = new double[num_in];
    out = new double[num_in];

    init();
}

void Layer::init()
{
    srand(time(0));
    memset(out, 0, num_in * sizeof(double));
    memset(diff, 0, num_in * sizeof(double));
    for (int i = 0; i < num_in; i++)
    {
        weight[i] = new double[num_out + 1];
        for (int w = 0; w <= num_out; w++)
        {
            weight[i][w] = rand() % 10000 * 0.000001 - 0.5;
        }
    }
}

Layer::Layer(Layer &next)
{
    num_in = next.num_in;
    num_out = next.num_out;
    act = next.act;
    memcpy(out, next.out, num_in * sizeof(double));
    memcpy(diff, next.diff, num_in * sizeof(double));
    for (int i = 0; i < num_in; i++)
        memcpy(weight[i], next.weight[i], (num_out + 1) * sizeof(double));
}

Layer::~Layer()
{
    delete [] out;
    delete [] diff;
    for (int i = 0; i < num_in; i++)
    {
        delete [] weight[i];
    }
    delete [] weight;
}

double Layer::activation(double x, activationFunction a = SIGMOID)
{
    switch (a)
    {
    case SIGMOID
        return (1.0 / 1.0 + exp(-x));
    
    default:
        std::cout<<"Activation not found"<<std::endl;
        return x;
    }
}

double Layer::gradient(double x, activationFunction a = SIGMOID)
{
    switch (a)
    {
    case SIGMOID
        return x * (1.0 - x);
    
    default:
        std::cout<<"Activation not found"<<std::endl;
        return 1;
    }
}

void Layer::forward(double *in)
{
    for (int i = 0; i < num_in; i++)
    {
        double x = 0;
        for (int j = 0; j < num_out; j++)
        {
            x += weight[i][j] * in[j];
        }
        x += weight[num_out];
        out[i] = activation(x, act);
    }
}

void Layer::backward(double *pre_data, double *pre_diff, double learning_rate)
{
    for (int i = 0; i < num_in; i++)
    {
        double d = diff[i] * gradient(out[i], act);
        for (int j = 0; j < num_out; j++)
        {
            if (pre_diff)
            {
                pre_diff[j] += weight[i][j] * d;
            }
            weight[i][j] += d * learning_rate * pre_data[j];
        }
        weight[i][num_out] += d * learning_rate;
    }
}