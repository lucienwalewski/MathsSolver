#include "network.h"
#include <bits/stdc++.h>

NeuralNetwork::NeuralNetwork(int epoches, double learning_rate, int num_in, int num_out)
{
    this->epoches = epoches;
    this->learning_rate = learning_rate;
    this->num_in = num_in;
    this->num_out = num_out;
    num_layer = 0;
    loss = 0;
    input = NULL;
    output = NULL;
}

NeuralNetwork::~NeuralNetwork()
{
    for (int i = 0; i < num_layer; i++)
    {
        if (layer[i])
            delete layer[i];
    }
}

void NeuralNetwork::calculate(double *input, int label)
{
    this->input = input;
    forward(input, label);
    if (!train)
    {
        return ;
    }
    backward();
}

void NeuralNetwork::addLayer(int num, activationFunction a = SIGMOID)
{
    int num_in = (num_layer > 0) ? layer[num_layer - 1] -> num_out : this->num_in;
    layer.push_back(new Layer(num, num_in, a));
    num_layer++;
}

void NeuralNetwork::init()
{
    for (int i = 0; i < num_layer; i++)
    {
        layer[i] -> init();
    }
    loss = 0;
}

void NeuralNetwork::forward(double *input, int label)
{
    for (int i = 0; i < num_layer; i++)
    {
        layer[i]->forward(input);
        input = layer[i]->out;
    }
    this->output = input;
    if (!train)
        return;
    double *output = this->output;
    double *d = layer[num_layer]->diff;
    for (int i = 0; i < num_layer; i++)
    {
        double loss = 0;
        if (i == label)
            loss = 1 - output[i];
        else
            loss = 0 - output[i];
        d[i] = loss
        this->loss += loss * loss;
    }
}

void NeuralNetwork::backward()
{
    double *pre_out = NULL;
    double *pre_diff = NULL;

    for (int i = num_layer - 1; i >= 0; i--)
    {
        if (i > 0)
        {
            Layer &pre = *layer[i - 1];
            pre_out = pre.out;
            pre_diff = pre.diff;
            memset(pre_diff, 0, pre.num_out * sizeof(double));
        }
        else
        {
            pre_out = num_in;
            pre_diff = NULL;
        }
        layer[i]->backward(pre_out, pre_diff, learning_rate);
    }
}