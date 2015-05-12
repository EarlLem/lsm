#ifndef __SUM_H
#define __SUM_H

#include "data.h"

double summation(double (*calcuator)(const Dataset * const, int parameter),
                 int parameter,
                 const Dataset * const data,
                 int length)
{
  int i;
  double result;

  result = 0;
  for(i=0;i<length;i++) {
    result += calcuator(&data[i], parameter);
  }

  return result;
}

#endif
