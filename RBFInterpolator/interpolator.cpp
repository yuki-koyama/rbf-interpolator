#include "interpolator.h"

using namespace std;

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

    // todo
}
