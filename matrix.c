#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "matrix.h"
#include "def.h"
#include "debug.h"

// private method
static bool _matrixIsNull(const Matrix* const matrix) {
  return matrix == NULL;
}

static bool _matrixIsSameSize(const Matrix* const matrixA, const Matrix* const matrixB) {
  assert(!_matrixIsNull(matrixA));
  assert(!_matrixIsNull(matrixB));

  return (matrixA->y == matrixB->y) && (matrixA->x == matrixB->x);
}

static bool _matrixPointIsValidRange(const Matrix* matrix, const int y, const int x) {
  assert(!_matrixIsNull(matrix));

  return (matrix->y > y) && (matrix->x > x) && y >= 0 && x >= 0;
}

static bool _matrixPointIsInvalidRange(const Matrix* matrix, const int y, const int x) {
  assert(!_matrixIsNull(matrix));

  return !_matrixPointIsValidRange(matrix, y, x);
}

int _matrixGetDataSize(const Matrix* const matrix) {
  assert(!_matrixIsNull(matrix));

  return matrix->y * matrix->x;
}

static int _matrixGetDataIndex(const Matrix* const matrix, int y, int x) {
  assert(!_matrixIsNull(matrix));
  assert(_matrixPointIsValidRange(matrix, y, x));

  return matrix->x*y + x;
}

// public method
Matrix* matrixInit(int y, int x) {
  int i;
  Matrix* matrix;
  double* data;

  if(y <= 0 || x <= 0) {
    return NULL;
  }

  matrix = (Matrix *)malloc(sizeof(Matrix));

  if(_matrixIsNull(matrix)) {
    return NULL;
  }

  data = (double *)malloc(sizeof(double)*y*x);

  if(data == NULL) {
    free(matrix);
    return NULL;
  }

  matrix->data = data;
  matrix->y = y;
  matrix->x = x;

  return matrix;
}

int matrixSetIdentityMatrix(const Matrix* matrix) {
  int y,x;

  if(_matrixIsNull(matrix)) {
    return FAIL;
  }

  for(y=0;y<matrix->y;y++) {
    for(x=0;x<matrix->x;x++) {
      //斜めのところに1、それ以外0
      if(y == x) {
        matrixSetValue(matrix, y, x, 1.0);
      } else {
        matrixSetValue(matrix, y, x, 0);
      }
    }
  }

  return SUCCESS;
}

Matrix* matrixGetIdentityMatrix(int y, int x) {
  Matrix* matrixResult;

  if(y <= 0 || x <= 0) {
    return NULL;
  }

  matrixResult = matrixInit(y, x);
  if(_matrixIsNull(matrixResult)) {
    return NULL;
  }

  if(matrixSetIdentityMatrix(matrixResult) == FAIL) {
    return NULL;
  }

  return matrixResult;
}

Matrix* matrixInitWithValues(int y, int x, double* values) {
  Matrix* matrix;

  matrix = matrixInit(y, x);

  if(_matrixIsNull(matrix)) {
    return NULL;
  }

  memcpy(matrix->data, values, _matrixGetDataSize(matrix));

  return matrix;
}

Matrix* matrixDestroy(Matrix* const matrix) {
  if(_matrixIsNull(matrix)) {
    return NULL;
  }

  free(matrix->data);
  free(matrix);

  return NULL;
}

double matrixGetValue(const Matrix* const matrix, int y, int x) {
  if(_matrixIsNull(matrix)) {
    return FAIL;
  }

  if(_matrixPointIsInvalidRange(matrix, y, x)) {
    return FAIL;
  }

  return matrix->data[_matrixGetDataIndex(matrix, y, x)];
}

int matrixSetValue(const Matrix* matrix, int y, int x, double value) {
  if(_matrixIsNull(matrix)) {
    return FAIL;
  }

  if(_matrixPointIsInvalidRange(matrix, y, x)) {
    return FAIL;
  }

  matrix->data[_matrixGetDataIndex(matrix, y, x)] = value;

  return SUCCESS;
}

int matrixCopy(const Matrix* matrixDest, const Matrix* const matrixSrc) {
  if(_matrixIsNull(matrixDest) || _matrixIsNull(matrixSrc)) {
    return FAIL;
  }

  if(_matrixIsSameSize(matrixDest, matrixSrc)) {
    return FAIL;
  }

  memcpy(matrixDest->data, matrixSrc->data, sizeof(double)*_matrixGetDataSize(matrixSrc));

  return SUCCESS;
}

Matrix* matrixGetCopy(const Matrix* const matrixSrc) {
  Matrix* matrixDest;

  if(_matrixIsNull(matrixSrc)) {
    return NULL;
  }

  matrixDest = matrixInit(matrixSrc->y, matrixSrc->x);

  if(_matrixIsNull(matrixDest)) {
    return NULL;
  }

  if(matrixCopy(matrixDest, matrixSrc) == FAIL) {
    return NULL;
  }

  return matrixDest;
}

int matrixCalcMul(const Matrix* matrixResult, const Matrix* const matrixA,const Matrix* const matrixB) {
  int tmp_pos;
  int result_x;
  int result_y;

  double tmp;

  if(_matrixIsNull(matrixResult) || _matrixIsNull(matrixA) || _matrixIsNull(matrixB)) {
    return FAIL;
  }

  if(matrixA->x != matrixB->y) {
    return FAIL;
  }

  if(matrixResult->y != matrixA->y || matrixResult->x != matrixB->x) {
    return FAIL;
  }

  for(result_y=0;result_y<matrixResult->y;result_y++) {
    tmp = 0;
    for(result_x=0;result_x<matrixResult->x;result_x++) {
      tmp = 0;
      for(tmp_pos=0;tmp_pos<matrixA->x;tmp_pos++) {
        tmp += matrixGetValue(matrixA, result_y, tmp_pos) * matrixGetValue(matrixB, tmp_pos, result_x);
      }

      matrixSetValue(matrixResult, result_y, result_x, tmp);
    }
  }

  return SUCCESS;
}

Matrix* matrixGetMul(const Matrix* const matrixA, const Matrix* const matrixB) {
  Matrix* matrixResult;

  printf("\tMul\n");

  if(_matrixIsNull(matrixA) || _matrixIsNull(matrixB)) {
    return NULL;
  }

  printf("\tMul:1\n");

  if(matrixA->x != matrixB->y) {
    return NULL;
  }

  printf("\tMul:2\n");

  matrixResult = matrixInit(matrixA->y, matrixB->x);
  if(_matrixIsNull(matrixResult)) {
    return NULL;
  }

  printf("\tMul:3\n");

  if(matrixCalcMul(matrixResult, matrixA, matrixB) == FAIL) {
    return NULL;
  }

  printf("\tMul:Result\n");
  matrixPrint(matrixResult);

  return matrixResult;
}

int matrixCalcScalaMul(const Matrix* const matrixResult ,const double value,const Matrix* const matrix) {
  int x,y;

  if(_matrixIsNull(matrix) || _matrixIsNull(matrixResult)) {
    return FAIL;
  }

  if(!_matrixIsSameSize(matrix, matrixResult)) {
    return FAIL;
  }

  for(y=0;y<matrix->y;y++) {
    for(x=0;x<matrix->x;x++) {
      matrixSetValue(matrixResult, y, x, value*matrixGetValue(matrix, y, x));
    }
  }

  return SUCCESS;
}

Matrix* matrixGetScalaMul(const double value,const Matrix* const matrix) {
  Matrix* matrixResult;

  if(_matrixIsNull(matrix)) {
    return NULL;
  }

  matrixResult = matrixInit(matrix->y, matrix->x);
  if(_matrixIsNull(matrixResult)) {
    return NULL;
  }

  if(matrixCalcScalaMul(matrixResult, value, matrix) == FAIL) {
    return NULL;
  }

  return matrixResult;
}

double matrixCalcDeterminant(const Matrix* const matrix) {
  double det;
  double buf;
  int i,x,y;

  Matrix* matrixTemp;

  if(_matrixIsNull(matrix)) {
    return FAIL;
  }

  matrixTemp = matrixInit(matrix->y, matrix->x);

  if(_matrixIsNull(matrixTemp)) {
    return FAIL;
  }

  matrixCopy(matrixTemp, matrix);

  for(x=0;x<matrixTemp->x;x++) {
    for(y=0;y<matrixTemp->y;y++) {

      //上三角行列のゼロにしなければならない場所
      //に入った時
      if(x<y) {

        //何で割ればゼロになるか求める
        buf = matrixGetValue(matrixTemp, y, x) / matrixGetValue(matrixTemp, x, x);
        __DP("buf = %lf\n",buf);

        //行基本変換
        //任意のゼロではない数を掛けあわせて足し算
        //（-の値をかけているとおいて、減算に変更）
        for(i=0;i<matrixTemp->x;i++) {
          double __tmp;
          __tmp = matrixGetValue(matrixTemp, y, i) - matrixGetValue(matrixTemp, x, i) * buf;
          matrixSetValue(matrixTemp, y, i, __tmp);
        }
        __DEXE(matrixPrint(matrixTemp));
      }
    }
  }

  __DEXE(matrixPrint(matrixTemp));

  //対角成分を乗算
  for(i=0,det=1.0;i<matrixTemp->x;i++) {
    det *= matrixGetValue(matrixTemp, i, i);
  }

  matrixTemp = matrixDestroy(matrixTemp);

  return det;
}

int matrixCalcInverse(const Matrix* matrixInv, const Matrix* const matrix) {
  int x,y,z;
  double buf;

  if(_matrixIsNull(matrix) || _matrixIsNull(matrixInv)) {
    return FAIL;
  }

  if(!_matrixIsSameSize(matrixInv, matrix)) {
    return FAIL;
  }

  if(matrixSetIdentityMatrix(matrixInv) == FAIL) {
    return FAIL;
  }

  printf("Inv:IdentityM\n");
  matrixPrint(matrixInv);

  //掃き出し法で逆行列を求める
  for(y=0;y<matrix->y;y++) {
    buf = 1 / matrixGetValue(matrix, y, y);
    for(x=0;x<matrix->x;x++) {
      double __tmp;

      __tmp = matrixGetValue(matrix, y, x) * buf;
      matrixSetValue(matrix, y, x, __tmp);

      __tmp = matrixGetValue(matrixInv, y, x) * buf;
      matrixSetValue(matrixInv, y, x, __tmp);
    }

    for(x=0;x<matrix->x;x++) {
      if(y != x) {
        buf = matrixGetValue(matrix, x, y);
        for(z=0;z<matrix->x;z++) {
          double __tmp;

          __tmp = matrixGetValue(matrix, x, z) - matrixGetValue(matrix, y, z) * buf;
          matrixSetValue(matrix, x, z, __tmp);

          __tmp = matrixGetValue(matrixInv, x, z) - matrixGetValue(matrixInv, y, z) * buf;
          matrixSetValue(matrixInv, x, z, __tmp);
        }
      }
    }
  }

  return SUCCESS;
}

Matrix* matrixGetInverse(const Matrix* const matrix) {
  Matrix* matrixResult;

  if(_matrixIsNull(matrix)) {
    return NULL;
  }

  matrixResult = matrixInit(matrix->y, matrix->x);
  if(_matrixIsNull(matrixResult)) {
    return NULL;
  }

  if(matrixCalcInverse(matrixResult, matrix) == FAIL) {
    return NULL;
  }

  return matrixResult;
}

void matrixPrint(const Matrix* const matrix) {
  int x,y;

  if(_matrixIsNull(matrix)) {
    printf("Matrix is NULL.\n");
    return;
  }

  printf("Matrix[%d][%d]\n",matrix->y,matrix->x);

  for(y=0;y<matrix->y;y++) {
    printf("(");
    for(x=0;x<matrix->x;x++) {
      printf(" %lf ",matrixGetValue(matrix, y, x));
    }
    printf(")\n");
  }
}
