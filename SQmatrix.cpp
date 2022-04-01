#include <iostream>
#include <vector>
#include "SQmatrix.h"
#include "VectorExten.h"


SQmatrix::SQmatrix() {
    //пустая матрица
    size = 0;
    matrix = std::vector<std::vector<double>>(0, std::vector<double>(0, 0));
}

SQmatrix::SQmatrix(int s) {
    //незаполненная матрица

    if (s < 0) {
        //задан невозможный размер
        throw ERR_MATR_IRR_SIZE;
    }

    size = s;
    matrix = std::vector<std::vector<double>>(s, std::vector<double>(s, 0));
}

SQmatrix::SQmatrix(int s, std::vector<std::vector<double>>& v) {
    //матрица с заданным заполнением

    size_t sz = v.size();
    if (sz > 0) {
        for (int i = 0; i < sz; ++i) {
            if (v[i].size() != sz) {
                //несоответствие размеров строк и столбцов
                throw ERR_MATR_NOT_MATRIX;
            }
        }
    }
    else {
        //матрица нулевой размерности
        throw ERR_MATR_NULL_SIZE;
    }

    if (s != sz) {
        //заявленная размерность не соответствует реальной
        throw ERR_MATR_SIZE_MISSMATCH;
    }

    size = s;
    matrix = v;
}

SQmatrix::SQmatrix(int s, std::string type) {
    //матрица с заданным заполнением
    size = s;

    if (s < 0) {
        //задан невозможный размер
        throw ERR_MATR_IRR_SIZE;
    }

    matrix = std::vector<std::vector<double>>(s, std::vector<double>(s, 0));

    if (type == "ident") {
        for (int i = 0; i < size; i++) {
            matrix[i][i] = 0;
        }
    }

}

bool SQmatrix::check() {
    //проверка корректности заполнения матрицы
    //возвращает true, если все ок

    if (matrix.size() != size) {
        return false;
    }

    for (int i = 0; i < size; ++i) {
        if (matrix[i].size() != size) {
            return false;
        }
    }

    return true;
}

const int SQmatrix::sizef() {
    if (matrix.size() == size) {
        return size;
    }
    else {
        return -1;
    }
}

const std::vector<std::vector<double>> SQmatrix::matrixf() {
     return matrix;
}

void SQmatrix::print() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%.2lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

SQmatrix SQmatrix::sum(const SQmatrix& lhs, const SQmatrix& rhs) {
    //сложение двух матриц.
    // ошибка 1 - несответствие размеров матриц
    if (lhs.size != rhs.size) {
        throw 1;
    }

    SQmatrix res(lhs.size);
    for (int i = 0; i < res.size; ++i) {
        for (int j = 0; j < res.size; ++j) {
            res.matrix[i][j] = lhs.matrix[i][j] + rhs.matrix[i][j];
        }
    }

    return res;
}

SQmatrix SQmatrix::mult(const SQmatrix& lhs, const SQmatrix& rhs) {
    //сложение двух матриц.
    // ошибка 1 - несответствие размеров матриц
    if (lhs.size != rhs.size) {
        throw ERR_MATR_MULT_SIZE_MISSMATCH;
    }

    SQmatrix res(lhs.size);
    for (int i = 0; i < res.size; ++i) {
        for (int j = 0; j < res.size; ++j) {
            for (int k = 0; k < res.size; ++k) {
                res.matrix[i][j] += lhs.matrix[i][k] * rhs.matrix[k][j];
            }
        }
    }

    return res;
}

std::pair<SQmatrix, SQmatrix> SQmatrix::LUdecomp() {
    SQmatrix L(size);
    SQmatrix U((*this));

    for (int i = 0; i < size; ++i) {
        //элементы на диагонали = 1
        L[i][i] = 1;
    }

    for (int j = 0; j < size - 1; ++j) {

        //Выполняется приведение матрицы U к верх.треуг. виду.
        //Коэфициенты, на которые для этого умножаются строки записываются в L.

        for (int i = j + 1; i < size; ++i) {
            //вычисление коэфициента, на который надо умножить строку U[j], 
            //чтобы при сложении с U[i] эл-т U[i][j] обратился в 0
            double fst = U[i][j] / U[j][j];
            //запись коэфициента в L
            L[i][j] = fst;
            //выполнение сложения
            U[i] = U[i] - (U[j] * fst);
        }
    }

    return std::pair<SQmatrix, SQmatrix>(L, U);
}

//на вход идет результат LU разложения, проверяется, равно ли произведение L и U изнач. матрицы
bool SQmatrix::LUcheck(const std::pair<SQmatrix, SQmatrix>& inp, double prec){
    SQmatrix multRes = (*this).mult(inp.first, inp.second);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (multRes[i][j] - matrix[i][j] > prec) {
                return false;
            }
        }
    }
    //multRes.print();
    return true;
}


SQmatrix SQmatrix::inverse() {
    SQmatrix D(*this);
    //задание единичной матрицы
    SQmatrix A(size);
    for (int i = 0; i < size; ++i) {
        A[i][i] = 1;
    }

    for (int j = 0; j < size; ++j) {

        //Выполняется приведение матрицы D к верх.треуг. виду.

        //предварительно угловые элементы приводятся к 1.
        A[j] = A[j] / D[j][j];
        D[j] = D[j] / D[j][j];

        for (int i = j + 1; i < size; ++i) {
            //вычисление коэфициента, на который надо умножить строку 
            //чтобы при сложении первый эл-т обратился в 0
            double fst = D[i][j] / D[j][j];

            //выполнение сложения
            D[i] = D[i] - (D[j] * fst);
            A[i] = A[i] - (A[j] * fst);
        }

    }

    for (int j = size - 1; j >= 0; --j) {

        //Выполняется приведение матрицы D к диаг. виду

        for (int i = j - 1; i >= 0; --i) {

            //вычисление коэфициента, на который надо умножить строку 
            //чтобы при сложении первый эл-т обратился в 0
            double fst = D[i][j] / D[j][j];

            //выполнение сложения
            D[i] = D[i] - (D[j] * fst);
            A[i] = A[i] - (A[j] * fst);
        }

    }

    return A;
}


double SQmatrix::det() {
    SQmatrix D(*this);

    for (int j = 0; j < size; ++j) {

        //Выполняется приведение матрицы D к верх.треуг. виду.

        for (int i = j + 1; i < size; ++i) {
            //вычисление коэфициента, на который надо умножить строку 
            //чтобы при сложении первый эл-т обратился в 0
            double fst = D[i][j] / D[j][j];

            //выполнение сложения
            D[i] = D[i] - (D[j] * fst);
        }
    }

    double det = 1;
    //рассчет определителя, как произведения элементов на главной диагонали
    for (int i = 0; i < size; ++i) {
        det *= D[i][i];
    }
    return det;
}


std::vector<double>& SQmatrix::operator[](int i) {
    return matrix[i];
}
