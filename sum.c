
#include "sum.h"
#include "data.h"

double summation(double (*calculator)(const Dataset * const, int parameter),
                 int parameter,
                 const Dataset * const data,
                 int length)
{
  int i;
  double result;

  result = 0;
  for(i=0;i<length;i++) {
    result += calculator(&data[i], parameter);
  }

  return result;
}
