//Гаврилов М.С. 8О-306
#include <iostream>
#include <vector>
#include "VectorExten.h"
#include "SQmatrix.h"
#include "EQsys.h"

//вариант 7
/*
    std::vector<std::vector<double>> mat =
    {{1, -5, -7, 1},
     {1, -3, -9, -4},
     {-2, 4, 2, 1},
     {-9, 9, 5, 3} };

    std::vector<double> ft =
    { -75, -41, 18, 29};

    4
    1 -5 -7 1
    1 -3 -9 -4
    -2 4 2 1 
    -9 9 5 3
    -75 -41 18 29
*/

int main() {
    printf("input number of variables\n");
    int n;
    std::cin >> n;
    std::vector<std::vector<double>> inp1(n, std::vector<double> (n,0));
    std::vector<double> inp2(n, 0);

    printf("input matrix\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> inp1[i][j];
        }
    }
    printf("input free terms\n");
    for (int i = 0; i < n; ++i) {
        std::cin >> inp2[i];
    }
    try {
        //задание матрицы
        SQmatrix matr(4, inp1);
        //задание системы
        EQsys system1(4, matr, inp2);
        //решение системы
        std::vector<double> res = system1.LUsolve();
        printf("---------\n");
        printf("result:\n");
        for (int i = 0; i < 4; ++i) {
            printf("%.3lf\n", res[i]);
        }
        printf("\n---------\n");

        //отыскание обратнойй матрицы
        SQmatrix res2 = matr.inverse();
        printf("-----------------------------------------\n");
        printf("inverse matrix:\n");
        res2.print();
        printf("-----------------------------------------\n");
        //отыскание определителя
        double det = matr.det();
        printf("\ndeterminant: %lf\n", det);
    }
    catch (int err) {
        printf("error occured.\n error code: %d", err);
        return;
    }
}
