#ifndef UTILITY_H
#define UTILITY_H

#include <vector>

class Utility
{
public:
    Utility();

    static std::vector<double> subtract(const std::vector<double>& left, const std::vector<double>& right);

    static double norm(const std::vector<double>& vec);
};

#endif // UTILITY_H
