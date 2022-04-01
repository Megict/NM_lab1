#pragma once
#include <vector>
#include "SQmatrix.h"

#define EQSYS_FREETERMS_SIZE_MISSMATCH 120
#define EQSYS_MATRIX_SIZE_MISSMATCH 120
#define EQSYS_LUSOL_LUERROR 201

class EQsys {
    //����� ��������� ������� ��������� � �������� ����
private:
    int varCnt;
    SQmatrix matr;
    std::vector<double> freeTerms;

public:

    //������ �������
    EQsys();

    //������������� �������
    EQsys(int s);

    //�������, � �������� �������� �������� (�������� ����� ������)
    //������� ���������
    EQsys(int s, std::vector<std::vector<double>>& v);

    //�������, � �������� �������� �������� (�������� ����� �������)
    //������� ���������
    EQsys(int s, SQmatrix m);

    //�������, � �������� �������� �������� (�������� ����� ������)
    //������� �����������
    EQsys(int s, std::vector<std::vector<double>>& v, std::vector<double>& b);

    //�������, � �������� �������� �������� (�������� ����� �������)
    //������� �����������
    EQsys(int s, SQmatrix m, std::vector<double>& b);

    //������ ���� � ������� LU ����������
    std::vector<double> LUsolve(); 
};