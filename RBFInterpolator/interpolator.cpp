#include "interpolator.h"
#include "utility.h"

#include <cmath>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

Interpolator::Interpolator() :
    functionType(GAUSSIAN),
    epsilon(10.0),
    readyForUse(false)
{
}

void Interpolator::resetAll()
{
    ys.clear();
    xs.clear();

    w.clear();

    readyForUse = false;
}

void Interpolator::addCenterPoint(double y, vector<double> x)
{
    ys.push_back(y);
    xs.push_back(x);

    readyForUse = false;
}

void Interpolator::computeWeights()
{
    // todo

    readyForUse = true;
}

double Interpolator::getInterpolatedValue(vector<double> x)
{
    if (!readyForUse) {
        return 0.0;
    }

    VectorXd xVec = Map<VectorXd>(&x[0], x.size());

    double result = 0.0;
    for (int i = 0; i < w.size(); ++ i) {
        VectorXd xiVec = Map<VectorXd>(&xs[i][0], xs[i].size());
        result += w[i] * getRBFValue((xVec - xiVec).norm());
    }

    return result;
}

double Interpolator::getRBFValue(double r)
{
    double result;
    switch (functionType) {
    case GAUSSIAN:
        result = exp(- pow((epsilon * r), 2.0));
        break;
    default:
        break;
    }
    return result;
}
