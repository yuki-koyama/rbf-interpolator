#include "interpolator.h"
#include <cmath>
#include <Eigen/Core>
#include <Eigen/LU>

using namespace std;
using namespace Eigen;

extern VectorXd solveLinearSystem(const MatrixXd& A, const VectorXd& y);

Interpolator::Interpolator() :
    functionType(BIHARMONICSPLINE),
    epsilon(2.0),
    lambda(0.1),
    useRegularization(true),
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

void Interpolator::addCenterPoint(const double y, const vector<double>& x)
{
    ys.push_back(y);
    xs.push_back(x);

    readyForUse = false;
}

void Interpolator::computeWeights()
{
    assert(ys.size() == xs.size());

    const int dim = ys.size();

    MatrixXd O = MatrixXd::Zero(dim, dim);
    VectorXd y = Map<VectorXd>(&ys[0], dim);

    for (int i = 0; i < dim; ++ i)
    {
        for (int j = 0; j < dim; ++ j)
        {
            O(i, j) = getRBFValue(xs[i], xs[j]);
        }
    }

    MatrixXd A;
    VectorXd b;
    if (useRegularization)
    {
        MatrixXd O2 = MatrixXd::Zero(dim * 2, dim);
        for (int i = 0; i < dim; ++ i)
        {
            for (int j = 0; j < dim; ++ j)
            {
                O2(i, j) = O(i, j);
            }
        }
        const double coef = 0.5 * lambda;
        for (int i = 0; i < dim; ++ i)
        {
            O2(i + dim, i) = coef;
        }

        VectorXd y2 = VectorXd::Zero(dim * 2);
        for (int i = 0; i < dim; ++ i)
        {
            y2(i) = y(i);
        }

        A = O2.transpose() * O2;
        b = O2.transpose() * y2;
    } else {
        A = O;
        b = y;
    }

    VectorXd x = solveLinearSystem(A, b);
    assert(x.rows() == dim);

    w.resize(dim);
    for (int i = 0; i < dim; ++ i)
    {
        w[i] = x(i);
    }

    readyForUse = true;
}

double Interpolator::getInterpolatedValue(const vector<double>& x) const
{
    if (!readyForUse)
    {
        return 0.0;
    }

    const int dim = w.size();
    
    double result = 0.0;
    for (int i = 0; i < dim; ++ i)
    {
        result += w[i] * getRBFValue(x, xs[i]);
    }

    return result;
}

double Interpolator::getRBFValue(const double r) const
{
    double result;
    switch (functionType)
    {
    case GAUSSIAN:
        result = exp(- pow((epsilon * r), 2.0));
        break;
    case THINPLATESPLINE:
        result = r * r * log(r);
        if (isnan(result))
        {
            result = 0.0;
        }
        break;
    case INVERSEQUADRATIC:
        result = 1.0 / (1.0 + pow((epsilon * r), 2.0));
        break;
    case BIHARMONICSPLINE:
        result = r;
        break;
    default:
        break;
    }
    return result;
}

double Interpolator::getRBFValue(const vector<double>& xi, const vector<double>& xj) const
{
    assert (xi.size() == xj.size());

    const VectorXd xiVec = Map<const VectorXd>(&xi[0], xi.size());
    const VectorXd xjVec = Map<const VectorXd>(&xj[0], xj.size());

    return getRBFValue((xjVec - xiVec).norm());
}

VectorXd solveLinearSystem(const MatrixXd& A, const VectorXd& y)
{
    FullPivLU<MatrixXd> lu(A);
    return lu.solve(y);
}

