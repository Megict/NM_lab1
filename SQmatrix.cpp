#include <iostream>
#include <vector>
#include "SQmatrix.h"
#include "VectorExten.h"


SQmatrix::SQmatrix() {
    //������ �������
    size = 0;
    matrix = std::vector<std::vector<double>>(0, std::vector<double>(0, 0));
}

SQmatrix::SQmatrix(int s) {
    //������������� �������

    if (s < 0) {
        //����� ����������� ������
        throw ERR_MATR_IRR_SIZE;
    }

    size = s;
    matrix = std::vector<std::vector<double>>(s, std::vector<double>(s, 0));
}

SQmatrix::SQmatrix(int s, std::vector<std::vector<double>>& v) {
    //������� � �������� �����������

    size_t sz = v.size();
    if (sz > 0) {
        for (int i = 0; i < sz; ++i) {
            if (v[i].size() != sz) {
                //�������������� �������� ����� � ��������
                throw ERR_MATR_NOT_MATRIX;
            }
        }
    }
    else {
        //������� ������� �����������
        throw ERR_MATR_NULL_SIZE;
    }

    if (s != sz) {
        //���������� ����������� �� ������������� ��������
        throw ERR_MATR_SIZE_MISSMATCH;
    }

    size = s;
    matrix = v;
}

SQmatrix::SQmatrix(int s, std::string type) {
    //������� � �������� �����������
    size = s;

    if (s < 0) {
        //����� ����������� ������
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
    //�������� ������������ ���������� �������
    //���������� true, ���� ��� ��

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
    //�������� ���� ������.
    // ������ 1 - ������������� �������� ������
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
    //�������� ���� ������.
    // ������ 1 - ������������� �������� ������
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
        //�������� �� ��������� = 1
        L[i][i] = 1;
    }

    for (int j = 0; j < size - 1; ++j) {

        //����������� ���������� ������� U � ����.�����. ����.
        //�����������, �� ������� ��� ����� ���������� ������ ������������ � L.

        for (int i = j + 1; i < size; ++i) {
            //���������� �����������, �� ������� ���� �������� ������ U[j], 
            //����� ��� �������� � U[i] ��-� U[i][j] ��������� � 0
            double fst = U[i][j] / U[j][j];
            //������ ����������� � L
            L[i][j] = fst;
            //���������� ��������
            U[i] = U[i] - (U[j] * fst);
        }
    }

    return std::pair<SQmatrix, SQmatrix>(L, U);
}

//�� ���� ���� ��������� LU ����������, �����������, ����� �� ������������ L � U �����. �������
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
    //������� ��������� �������
    SQmatrix A(size);
    for (int i = 0; i < size; ++i) {
        A[i][i] = 1;
    }

    for (int j = 0; j < size; ++j) {

        //����������� ���������� ������� D � ����.�����. ����.

        //�������������� ������� �������� ���������� � 1.
        A[j] = A[j] / D[j][j];
        D[j] = D[j] / D[j][j];

        for (int i = j + 1; i < size; ++i) {
            //���������� �����������, �� ������� ���� �������� ������ 
            //����� ��� �������� ������ ��-� ��������� � 0
            double fst = D[i][j] / D[j][j];

            //���������� ��������
            D[i] = D[i] - (D[j] * fst);
            A[i] = A[i] - (A[j] * fst);
        }

    }

    for (int j = size - 1; j >= 0; --j) {

        //����������� ���������� ������� D � ����. ����

        for (int i = j - 1; i >= 0; --i) {

            //���������� �����������, �� ������� ���� �������� ������ 
            //����� ��� �������� ������ ��-� ��������� � 0
            double fst = D[i][j] / D[j][j];

            //���������� ��������
            D[i] = D[i] - (D[j] * fst);
            A[i] = A[i] - (A[j] * fst);
        }

    }

    return A;
}


double SQmatrix::det() {
    SQmatrix D(*this);

    for (int j = 0; j < size; ++j) {

        //����������� ���������� ������� D � ����.�����. ����.

        for (int i = j + 1; i < size; ++i) {
            //���������� �����������, �� ������� ���� �������� ������ 
            //����� ��� �������� ������ ��-� ��������� � 0
            double fst = D[i][j] / D[j][j];

            //���������� ��������
            D[i] = D[i] - (D[j] * fst);
        }
    }

    double det = 1;
    //������� ������������, ��� ������������ ��������� �� ������� ���������
    for (int i = 0; i < size; ++i) {
        det *= D[i][i];
    }
    return det;
}


std::vector<double>& SQmatrix::operator[](int i) {
    return matrix[i];
}
