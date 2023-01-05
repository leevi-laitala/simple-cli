CC = g++
ARGS = -Wall -std=c++20
APP = cli

$(APP): main.o
	$(CC) main.o -o bin/$(APP) $(ARGS)

main.o: main.cpp include/*
	$(CC) -c main.cpp $(ARGS)

clean:
	rm *.o bin/$(APP)
