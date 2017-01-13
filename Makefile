SOURCES = Task.cpp Job.cpp Scheduler.cpp Event.cpp Cluster.cpp Node.cpp ReplicateScheduler.cpp MigrateScheduler.cpp
CFLAGS  = --std=c++17 -ggdb -Wall

all:
	g++ $(CFLAGS) main.cpp $(SOURCES) -o simulator

clean:
	rm -rf simulator *.o
