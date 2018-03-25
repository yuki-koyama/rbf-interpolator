#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <vector>

namespace RBF {
   
enum class FunctionType
{
    Gaussian,         // f(r) = exp(-(epsilon * r)^2)
    ThinPlateSpline,  // f(r) = (r^2) * log(r)
    InverseQuadratic, // f(r) = (1 + (epsilon * r)^2)^(-1)
    BiharmonicSpline, // f(r) = r
};

class Interpolator
{
public:
    Interpolator(FunctionType functionType = FunctionType::BiharmonicSpline, const double epsilon = 2.0);

    // API
    void    resetAll();
    void    addCenterPoint(const double y, const std::vector<double>& x);
    void    computeWeights(const bool useRegularization = false, const double lambda = 0.1);
    double  getInterpolatedValue(const std::vector<double>& x) const;

    // Getter methods
    const std::vector<double>&              getYs() const { return ys; }
    const std::vector<std::vector<double>>& getXs() const { return xs; }
    const std::vector<double>&              getW()  const { return w;  }

private:

    // Function type
    FunctionType functionType;
    
    // A control parameter used in some kernel functions
    double epsilon;
    
    // Data points
    std::vector<double>              ys;
    std::vector<std::vector<double>> xs;

    // Weights
    std::vector<double>              w;

    // Used for error check
    bool readyForUse;

    // Returns f(r)
    double getRBFValue(const double r) const;
    // Returns f(||xj - xi||)
    double getRBFValue(const std::vector<double>& xi, const std::vector<double>& xj) const;
};

}

#endif // INTERPOLATOR_H
