#include "utility.h"

#include <cassert>
#include <cmath>

using namespace std;

Utility::Utility()
{
}

vector<double> Utility::subtract(const vector<double>& left, const vector<double>& right)
{
    assert (left.size() == right.size());

    vector<double> vec;

    for (int i = 0; i < left.size(); ++ i) {
        vec.push_back(left[i] - right[i]);
    }

    return vec;
}

double Utility::norm(const vector<double> &vec)
{
    double n = 0.0;
    for (int i = 0; i < vec.size(); ++ i) {
        n += vec[i] * vec[i];
    }
    return sqrt(n);
}
