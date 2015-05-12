#ifndef __SUM_H
#define __SUM_H

#include "data.h"

double summation(double (*calcuator)(const Dataset * const, int parameter),
                 int parameter,
                 const Dataset * const data,
                 int length);

#endif
