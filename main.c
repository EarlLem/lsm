#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "lsm.h"
#include "data.h"

void printForm(Matrix* result, int degree) {
  int i;
  int exp;

  printf("y = ");

  for(i=degree; i >= 0; i--) {
    for(exp=i; exp > 0; exp--)
      printf("x*");
    if(i!=0) {
      printf("(%lf) + ", matrixGetValue(result, i, 0));
    } else {
      printf("(%lf)", matrixGetValue(result, i, 0));
    }
  }

  printf("\n");
}

int main(int argc, char *argv[]) {

  Dataset* data;
  int dataNumber;
  char filename[256];
  int degree;

  Matrix* result;

  if(argc-1 != 3) {
    printf("Error.\n");
    printf("Usage: ./lsm [Data Number] [Filename] [Degree]\n");
    exit(1);
  }

  dataNumber = atoi(argv[1]);
  strcpy(filename, argv[2]);
  degree = atoi(argv[3]);

  data = (Dataset*)malloc(sizeof(Dataset)*dataNumber);

  inputData(data, dataNumber, filename);

  result = lsm(data, dataNumber, degree);

  printf("Result\n\n");
  matrixPrint(result);

  printForm(result, degree);

  return 0;
}
