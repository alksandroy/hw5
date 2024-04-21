#ifndef RECCHECK
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here

// Add your implementation of schedule() and other helper functions here

bool findSchedule(const AvailabilityMatrix& avail,
                  const size_t dailyNeed,
                  const size_t maxShifts,
                  vector<size_t>& workerNumassigned,
                  DailySchedule& sched,
                  size_t day,
                  size_t slot) {
    if (day == avail.size()) {
        return true;
    }

    if (slot == dailyNeed) {
        return findSchedule(avail, dailyNeed, maxShifts, workerNumassigned,
                            sched, day + 1, 0);
    }

    size_t firstWorker = 0;
    if (slot > 0) {
        firstWorker = sched[day][slot - 1] + 1;
    }

    for (size_t worker = firstWorker; worker < avail[day].size(); worker++) {
        if (avail[day][worker] && workerNumassigned[worker] < maxShifts) {
            workerNumassigned[worker]++;
            sched[day][slot] = worker;

            if (findSchedule(avail, dailyNeed, maxShifts, workerNumassigned,
                             sched, day, slot + 1)) {
                return true;
            }
            workerNumassigned[worker]--;
            sched[day][slot] = INVALID_ID;

        }
    }
    return false;
}

bool schedule(const AvailabilityMatrix& avail,
              const size_t dailyNeed,
              const size_t maxShifts,
              DailySchedule& sched) {
    if (avail.size() == 0U) {
        return false;
    }
    vector<size_t> workerNumassigned(avail[0].size(), 0);
    sched.clear();
    sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));
    // Add your code below
    return findSchedule(avail, dailyNeed, maxShifts, workerNumassigned, sched,
                        0, 0);
}
