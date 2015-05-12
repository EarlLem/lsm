TARGET = lsm
SRCS = main.c matrix.c data.c lsm.c sum.c

OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -lm

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.c : matrix.h data.h lsm.h
lsm.c : lsm.h matrix.h data.h sum.h def.h
sum.c : sum.h data.h
matrix.c : matrix.h def.h debug.h
data.c : data.h

.c.o :
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f *.o $(TARGET)
