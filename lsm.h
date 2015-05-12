#ifndef __LSM_H
#define __LSM_H

#include "data.h"
#include "matrix.h"

Matrix* lsm(Dataset data[], int dataNumber, int degree);

#endif
