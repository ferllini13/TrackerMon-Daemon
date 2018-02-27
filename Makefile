CC = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall
OBJS = stats.o main.o

trackermon: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ./bin/trackermon
	rm *.o

stats.o: ./include/stats.h ./src/stats.c
	$(CC) $(CFLAGS) ./src/stats.c

main.o: 
	$(CC) $(CFLAGS) main.c

clean:
	rm ./bin/trackermon