typedef enum
{
    SIGMOID
} activationFunction;

class Layer
{
public:
    Layer(int num_in, int num_out, activationFunction a = SIGMOID);
    Layer(Layer &next);
    void init();
    ~Layer();
    void forward(double *in);
    void backward(double *pre_data, double *pre_diff, double learning_rate);

    activationFunction act;
    int num_in, num_out;
    double **weight;
    double *diff;
    double *out;
private:
    double activation(double x, activationFunction a);
    double gradient(double x, activationFunction a);
}