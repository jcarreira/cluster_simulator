#include <queue>
#include <memory>
#include <vector>

#include "Event.h"

std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, EventComparator> event_queue;


void run_simulation() {
    while (event_queue.size()) {
        auto event = event_queue.top();
        event_queue.pop();

        process_event(event);
    }
}


int main() {
    auto scheduler = std::make_unique<Scheduler>();
    auto cluster = createCluster();
    auto jobs = createJobs();

    scheduler.start(cluster, jobs);

    run_simulation();

    return 0;
}
