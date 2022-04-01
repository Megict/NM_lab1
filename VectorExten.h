#pragma once
#include <vector>

const std::vector<double> operator*(const double left, const std::vector<double>& right);
const std::vector<double> operator*(const std::vector<double>& left, const double right);
const std::vector<double> operator+(const std::vector<double>& left, const std::vector<double>& right);
const std::vector<double> operator-(const std::vector<double>& left, const std::vector<double>& right);
const std::vector<double> operator/(const std::vector<double>& left, const double right);
