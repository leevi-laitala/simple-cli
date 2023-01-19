CC = g++
APP = cli

BASEFLAGS = -Wall -std=c++20
LDFLAGS = -I /opt/homebrew/Cellar/boost/1.81.0_1/include
LLIBFLAGS = -L /opt/homebrew/Cellar/boost/1.81.0_1
LINKFLAGS = 

FLAGS = $(BASEFLAGS) $(LLIBFLAGS) $(LDFLAGS) $(LINKFLAGS)

$(APP): main.o
	$(CC) $(FLAGS) main.o -o bin/$(APP) 

main.o: main.cpp include/*
	$(CC) $(FLAGS) -c main.cpp 

clean:
	rm *.o bin/$(APP)
