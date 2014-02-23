#include "interpolator.h"
#include "utility.h"

#include <cmath>
#include <Eigen/Core>
#include <Eigen/LU>

using namespace std;
using namespace Eigen;

extern VectorXd solveLinearSystem(MatrixXd A, VectorXd y);

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
    assert(ys.size() == xs.size());

    int dim = ys.size();

    MatrixXd A = MatrixXd::Zero(dim, dim);
    VectorXd y = Map<VectorXd>(&ys[0], dim);

    for (int i = 0; i < dim; ++ i) {
        for (int j = 0; j < dim; ++ j) {
            A(i, j) = getRBFValue(xs[i], xs[j]);
        }
    }

    VectorXd x = solveLinearSystem(A, y);

    w.clear();
    for (int i = 0; i < dim; ++ i) {
        w.push_back(x(i));
    }

    readyForUse = true;
}

double Interpolator::getInterpolatedValue(vector<double> x)
{
    if (!readyForUse) {
        return 0.0;
    }

    int    dim    = w.size();
    double result = 0.0;

    for (int i = 0; i < dim; ++ i) {
        result += w[i] * getRBFValue(x, xs[i]);
    }

    return result;
}

vector<double> Interpolator::getYs() {
    return ys;
}

vector<vector<double> > Interpolator::getXs() {
    return xs;
}

double Interpolator::getRBFValue(double r)
{
    double result;
    switch (functionType) {
    case GAUSSIAN:
        result = exp(- pow((epsilon * r), 2.0));
        break;
    case THINPLATESPLINE:
        result = r * r * log(r);
        break;
    case INVERSEQUADRATIC:
        result = 1.0 / (1.0 + pow((epsilon * r), 2.0));
        break;
    default:
        break;
    }
    return result;
}

double Interpolator::getRBFValue(vector<double> xi, vector<double> xj)
{
    VectorXd xiVec = Map<VectorXd>(&xi[0], xi.size());
    VectorXd xjVec = Map<VectorXd>(&xj[0], xj.size());

    return getRBFValue((xjVec - xiVec).norm());
}

VectorXd solveLinearSystem(MatrixXd A, VectorXd y)
{
    FullPivLU<MatrixXd> lu(A);
    return lu.solve(y);
}
