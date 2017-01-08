all:
	g++ --std=c++14 main.cpp Task.cpp Job.cpp Scheduler.cpp Event.cpp -o simulator

clean:
	rm -rf simulator
