#include <vector>
#include "VectorExten.h"


//���������� �������� � ���������
const std::vector<double> operator*(const double left, const std::vector<double>& right) { //��������� �� �����
    std::vector<double> res(0);
    for (double a : right) {
        res.push_back(left * a);
    }
    return res;
}

const std::vector<double> operator*(const std::vector<double>& left, const double right) { //��������� �� �����
    std::vector<double> res(0);
    for (double a : left) {
        res.push_back(right * a);
    }
    return res;
}

const std::vector<double> operator/(const std::vector<double>& left, const double right) { //������� �� �����
    std::vector<double> res(0);
    for (double a : left) {
        res.push_back(a / right);
    }
    return res;
}


const std::vector<double> operator+(const std::vector<double>& left, const std::vector<double>& right) { //�������� �������� ���������� �����
    if (left.size() != right.size()) {
        throw(1);
    }
    std::vector<double> res(left.size());
    for (size_t i = 0; i < left.size(); ++i) {
        res[i] = left[i] + right[i];
    }
    return res;
}

const std::vector<double> operator-(const std::vector<double>& left, const std::vector<double>& right) { //��������� �������� ���������� �����
    if (left.size() != right.size()) {
        throw(1);
    }
    std::vector<double> res(left.size());
    for (size_t i = 0; i < left.size(); ++i) {
        res[i] = left[i] - right[i];
    }
    return res;
}