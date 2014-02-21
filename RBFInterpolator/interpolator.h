#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <vector>

class Interpolator
{
public:
    Interpolator();

    // function definition
    enum FUNCTION_TYPE {
        GAUSSIAN,       // f(r) = exp(-(epsilon*r)^2)
    } functionType;

    double epsilon;

    // API
    void    addCenterPoint(double y, std::vector<double> x);
    void    computeWeights();
    double  getInterpolatedValue(std::vector<double> x);

private:

    // registered center points
    std::vector<double>               ys;
    std::vector<std::vector<double> > xs;

    // computed weights
    std::vector<double>               w;

    // for error check
    bool readyForUse;
};

#endif // INTERPOLATOR_H
