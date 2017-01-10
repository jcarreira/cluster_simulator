SOURCES = Task.cpp Job.cpp Scheduler.cpp Event.cpp Cluster.cpp Node.cpp
CFLAGS  = --std=c++14 -ggdb -Wall

all:
	g++ $(CFLAGS) main.cpp $(SOURCES) -o simulator

clean:
	rm -rf simulator
