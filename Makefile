CC = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall
OBJS = stats.o service.o main.o

trackermon: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ./bin/trackermon
	rm *.o

stats.o: ./include/stats.h ./src/stats.c
	$(CC) $(CFLAGS) ./src/stats.c

service.o: ./include/service.h ./src/service.c
	$(CC) $(CFLAGS) ./src/service.c

main.o:
	$(CC) $(CFLAGS) main.c

clean:
	rm ./bin/trackermon