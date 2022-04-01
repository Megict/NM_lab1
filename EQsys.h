#pragma once
#include <vector>
#include "SQmatrix.h"

#define EQSYS_FREETERMS_SIZE_MISSMATCH 120
#define EQSYS_MATRIX_SIZE_MISSMATCH 120
#define EQSYS_LUSOL_LUERROR 201

class EQsys {
    //класс описывает систему уравнений в матричом виде
private:
    int varCnt;
    SQmatrix matr;
    std::vector<double> freeTerms;

public:

    //пустая система
    EQsys();

    //незаполненная система
    EQsys(int s);

    //система, с заданной основной матрицей (задается через вектор)
    //система однородна
    EQsys(int s, std::vector<std::vector<double>>& v);

    //система, с заданной основной матрицей (задается через матрицу)
    //система однородна
    EQsys(int s, SQmatrix m);

    //система, с заданной основной матрицей (задается через вектор)
    //система неоднородна
    EQsys(int s, std::vector<std::vector<double>>& v, std::vector<double>& b);

    //система, с заданной основной матрицей (задается через матрицу)
    //система неоднородна
    EQsys(int s, SQmatrix m, std::vector<double>& b);

    //решить СЛАУ с помощью LU разложения
    std::vector<double> LUsolve(); 
};