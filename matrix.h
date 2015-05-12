#ifndef __MATRIX_H
#define __MATRIX_H

typedef struct _Matrix {
  double* data;
  int x;
  int y;
} Matrix;

int _matrixGetDataSize(const Matrix* const matrix);

Matrix* matrixInit(int y, int x);
int matrixSetIdentityMatrix(const Matrix* matrix);
Matrix* matrixGetIdentityMatrix(int y, int x);
Matrix* matrixInitWithValues(int y, int x, double* values);
Matrix* matrixDestroy(Matrix* const matrix);
double matrixGetValue(const Matrix* const matrix, int y, int x);
int matrixSetValue(const Matrix* matrix, int y, int x, double value);
Matrix* matrixGetCopy(const Matrix* const matrixSrc);
int matrixCalcMul(const Matrix* matrixResult, const Matrix* const matrixA,const Matrix* const matrixB);
Matrix* matrixGetMul(const Matrix* const matrixA, const Matrix* const matrixB);
int matrixCalcScalaMul(const Matrix* const matrixResult ,const double value,const Matrix* const matrix);
Matrix* matrixGetScalaMul(const double value,const Matrix* const matrix);
double matrixCalcDeterminant(const Matrix* const matrix);
int matrixCalcInverse(const Matrix* matrixInv, const Matrix* const matrix);
Matrix* matrixGetInverse(const Matrix* const matrix);
void matrixPrint(const Matrix* const matrix);

#endif
