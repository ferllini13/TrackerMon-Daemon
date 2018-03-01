CC = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall
OBJS = stats.o main.o File.o


trackermon: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ./bin/trackermon
	rm *.o

stats.o: 
	$(CC) $(CFLAGS) ./src/stats.c 

main.o: stats.o File.o
	$(CC) $(CFLAGS) main.c

File.o: 
	$(CC) $(CFLAGS) ./src/File.c

clean:
	rm -f ./bin/trackermon