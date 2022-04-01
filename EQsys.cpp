#include <iostream>
#include <vector>
#include "VectorExten.h"
#include "SQmatrix.h"
#include "EQsys.h"

EQsys::EQsys() {
    //пустая система
    varCnt = 0;
    matr = SQmatrix(0);
    freeTerms = std::vector<double>(0, 0);
}

EQsys::EQsys(int s) {
    //незаполненная система
    varCnt = s;
    matr = SQmatrix(s);
    freeTerms = std::vector<double>(s, 0);
}

EQsys::EQsys(int s, std::vector<std::vector<double>>& v) {
    //система, с заданной основной матрицей (задается через вектор)
    //система однородна
    try {
        matr = SQmatrix(s, v);
    }
    catch (int err) {
        throw err;
    }

    varCnt = s;
    freeTerms = std::vector<double>(s, 0);
}

EQsys::EQsys(int s, SQmatrix m) {
    //система, с заданной основной матрицей (задается через матрицу)
    //система однородна

    if (m.sizef() != s) {
        throw EQSYS_MATRIX_SIZE_MISSMATCH;
    }

    varCnt = s;
    matr = m;
    freeTerms = std::vector<double>(s, 0);
}

EQsys::EQsys(int s, std::vector<std::vector<double>>& v, std::vector<double>& b) {
    //система, с заданной основной матрицей (задается через вектор)
    //система неоднородна
    varCnt = s;
    try {
        matr = SQmatrix(s, v);
    }
    catch (int err) {
        throw err;
    }

    if (b.size() != s) {
        throw EQSYS_FREETERMS_SIZE_MISSMATCH;
    }

    freeTerms = b;
}

EQsys::EQsys(int s, SQmatrix m, std::vector<double>& b) {
    //система, с заданной основной матрицей (задается через матрицу)
    //система неоднородна

    if (m.sizef() != s) {
        throw EQSYS_MATRIX_SIZE_MISSMATCH;
    }

    if (b.size() != s) {
        throw EQSYS_FREETERMS_SIZE_MISSMATCH;
    }

    varCnt = s;
    matr = m;
    freeTerms = b;
}

std::vector<double> EQsys::LUsolve() {
    std::pair<SQmatrix, SQmatrix> LUres = matr.LUdecomp();
    //проверка правильности LU разложения
    if (!matr.LUcheck(LUres, 0.01)) {
        throw EQSYS_LUSOL_LUERROR;
    }

    std::vector<double> tmp(varCnt, 0);
    std::vector<double> res(varCnt, 0);

    for (int i = 0; i < varCnt; ++i) {
        double sumTmp = 0;
        for (int j = 0; j < i; ++j) {
            sumTmp += LUres.first[i][j] * tmp[j];
        }
        tmp[i] = freeTerms[i] - sumTmp;
    }

    for (int i = varCnt - 1; i >= 0; --i) {
        double sumTmp = 0;
        for (int j = i; j < varCnt; ++j) {
            sumTmp += LUres.second[i][j] * res[j];
        }
        res[i] = (tmp[i] - sumTmp) / (LUres.second[i][i]);
    }

    return res;
}