#pragma once
#include <vector>

#define ERR_MATR_IRR_SIZE 15
#define ERR_MATR_SIZE_MISSMATCH 12
#define ERR_MATR_NOT_MATRIX 11
#define ERR_MATR_NULL_SIZE 10
#define ERR_MATR_MULT_SIZE_MISSMATCH 101


class SQmatrix {
    //класс опиывает квадратную матрицу
private:
    int size;
    std::vector<std::vector<double>> matrix;
public:
    //Конструкторы:
    SQmatrix();

    SQmatrix(int s);

    SQmatrix(int s, std::vector<std::vector<double>>& v);

    SQmatrix(int s, std::string type);

    //Компоненты:
    const int sizef();

    const std::vector<std::vector<double>> matrixf();

    //Провекрка:
    bool check();

    //изуализация:
    void print();

    //арифметические операции:
    SQmatrix sum(const SQmatrix& lhs, const SQmatrix& rhs);

    SQmatrix mult(const SQmatrix& lhs, const SQmatrix& rhs);

    //LU разложение
    std::pair<SQmatrix, SQmatrix> LUdecomp();

    bool LUcheck(const std::pair<SQmatrix, SQmatrix>& inp, double prec);

    //вычисление обратной матрицы методом Жордана-Гаусса
    SQmatrix inverse();

    //вычисление определителя методом Гаусса
    double det();

    std::vector<double>& operator[](int i);
};

