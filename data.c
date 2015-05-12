#include <stdio.h>
#include "data.h"

void inputData(Dataset data[], int dataNumber, char filename[256])
{
  FILE *fp;
  int i;

  fp = fopen(filename, "r");
  if(fp==NULL) {
    printf("Error.\n");
    printf("Can't open file.\n");
    exit(1);
  }

  for(i=0; i<dataNumber; i++) {
    fscanf(fp, "%lf", &data[i].x);
    fscanf(fp, "%lf", &data[i].y);
  }

  fclose(fp);
}

void dispData(Dataset data[], int dataNumber)
{
  int i;

  for(i=0; i<dataNumber; i++) {
    printf("%lf %lf\n", data[i].x, data[i].y);
  }

}
