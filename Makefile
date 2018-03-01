CC = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall

OBJS = main.o service.o stats.o File.o

trackermon: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ./bin/trackermon
	rm *.o

stats.o: ./src/stats.c
	$(CC) $(CFLAGS) ./src/stats.c

service.o: ./include/service.h ./src/service.c
	$(CC) $(CFLAGS) ./src/service.c

main.o: service.o stats.o File.o
	$(CC) $(CFLAGS) main.c

File.o: 
	$(CC) $(CFLAGS) ./src/File.c

clean:
	rm -f ./bin/trackermon