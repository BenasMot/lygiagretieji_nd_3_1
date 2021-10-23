#include <stdlib.h>

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "banker.h"
#include "timeout.h"
#include "generate_state.h"

using namespace std;

void worker(Banker* banker, int n);

mutex debug;
void log(string msg) {
  debug.lock();
  cout << msg << endl;
  debug.unlock();
}

// Initial values
int mutex_count = 3;
int worker_count = 8;

int main() {
  Banker banker;
  // Initialise mutexes
  banker.init(mutex_count);
  vector<mutex*> mutexes(mutex_count);
  for (int i = 0; i < mutex_count; ++i) {
    mutexes[i] = new mutex();
  }

  // Launch threads
  thread threads[worker_count];
  for (int i = 0; i < worker_count; ++i) {
    threads[i] = thread(worker, banker, i);
  }

  // Wait for threads to complete execution
  for (int i = 0; i < worker_count; ++i) {
    threads[i].join();
  }

  // Cleanup mutexes
  banker.cleanup();
  for (int i = 0; i < mutex_count; ++i) {
    delete mutexes[i];
  }
  return 0;
}

// Lock if true in [i][j] place and is doLock. If doLock is false, unock [i][j].
void changeFromState(vector<vector<bool> > state, Banker* banker, bool doLock) {
  for (int i = 0; i < worker_count; ++i) {
    for (int j = 0; j < mutex_count; ++j) {
      if (state[i][j]) {
        if (doLock) {
          banker->lock(j);
        } else {
          banker->unlock(j);
        }
      }
    }
  }
}

void worker(Banker* banker, int n) {
  int iteration = 0;
  while (true) {
    vector<vector<bool> > state = generateState(iteration, worker_count, mutex_count);

    changeFromState(state, banker, true);
    cout << "Test" << n << endl;
    setTimeout(200);
    changeFromState(state, banker, false);

    iteration++;
  }
}
