#ifndef __DATA_H
#define __DATA_H

typedef struct _Dataset {
  double x;
  double y;
} Dataset;

void inputData(Dataset data[], int dataNumber, char filename[256]);
void dispData(Dataset data[], int dataNumber);

#endif
