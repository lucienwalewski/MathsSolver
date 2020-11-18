#ifndef CNN_HPP
#define CNN_HPP


class CNN
{
public:
    CNN();
    int train();
    double validate();
    void info();

private:
    int forward_prop();
    int backword_prop();
    double cross_entropy();
};

#endif // CNN_HPP
