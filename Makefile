SOURCES = Task.cpp Job.cpp Scheduler.cpp Event.cpp Cluster.cpp Node.cpp ReplicateScheduler.cpp MigrateScheduler.cpp Params.cpp
CCFLAGS  = --std=c++17 -ggdb -Wall

all:
	g++ $(CCFLAGS) main.cpp $(SOURCES) -o simulator

clean:
	rm -rf simulator *.o
