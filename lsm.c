#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "lsm.h"
#include "matrix.h"
#include "data.h"
#include "sum.h"
#include "def.h"

static double calc_sigma_powx(const Dataset * const data, int parameter) {
  return pow(data->x, parameter);
}

static double calc_sigma_powxy(const Dataset * const data, int parameter) {
  return pow(data->x, parameter) * data->y;
}

static int _lsmCreateExponentMatrixForA(const Matrix* matrix, int degree) {
  if(matrix->y != degree+1 || matrix->x != degree+1) {
    return FAIL;
  }

  int x,y;
  int exp;

  for(y=0;y < matrix->y;y++) {
    for(x=0;x < matrix->x;x++) {
      matrixSetValue(matrix, y, x, 2*degree-y-x);
    }
  }

  return SUCCESS;
}

static int _lsmCreateExponentVectorForB(const Matrix* vector, int degree) {
  if(vector->y != degree+1 || vector->x != 1) {
    return FAIL;
  }

  int y;
  int exp;

  for(y=0;y < vector->y;y++) {
    matrixSetValue(vector, y, 0, degree-y);
  }

  return SUCCESS;
}

Matrix* lsm(Dataset data[], int dataNumber, int degree) {
  // lsm formula
  // vector Result = inv(matrix A) * vector A

  int i;

  //指数指定行列
  Matrix* matAexp;
  Matrix* vecBexp;

  // matrix variable
  // row1 : (col1 , col2)
  // row2 : (col1 , col2)
  Matrix* matA;
  Matrix* matAinv;
  Matrix* vecB;
  Matrix* vecResult;

  matAexp = matrixInit(degree + 1, degree + 1);
  matA = matrixInit(degree + 1, degree + 1);
  vecBexp = matrixInit(degree + 1, 1);
  vecB = matrixInit(degree + 1, 1);

  // 指数行列を生成
  _lsmCreateExponentMatrixForA(matAexp, degree);
  _lsmCreateExponentVectorForB(vecBexp, degree);

  dispData(data, dataNumber);

  printf("\tDebug\n");
  matrixPrint(matAexp);
  matrixPrint(vecBexp);

  for(i=0; i < _matrixGetDataSize(matA); i++) {
    matA->data[i] = summation(calc_sigma_powx, matAexp->data[i], data, dataNumber);
  }

  for(i=0; i < _matrixGetDataSize(vecB); i++) {
    vecB->data[i] = summation(calc_sigma_powxy, vecBexp->data[i], data, dataNumber);
  }

  matrixPrint(matA);
  matrixPrint(vecB);

  matAinv = matrixGetInverse(matA);

  matrixPrint(matAinv);

  vecResult = matrixGetMul(matAinv, vecB);

  matrixPrint(vecResult);

  return vecResult;
}
