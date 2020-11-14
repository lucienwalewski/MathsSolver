#include <vector>
#include "layer.h"

class NeuralNetwork
{
public:
    NeuralNetwork(int epoches, double learning_rate, int num_in, int num_out);
    ~NeuralNetwork();
    void calculate(double *input, int label = 10);
    void addLayer(int num, activationFunction a = SIGMOID);

    bool train;
    int epoches, num_in, num_out, num_layer;
    double learning_rate, loss;
    double *input;
    double *output;
    std::vector<Layer *> layer;

private:
    void init();
    void forward(double *input, int label);
    void backward();
};