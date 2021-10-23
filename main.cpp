#include <stdlib.h>

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "banker.h"
#include "generate_state.h"
#include "timeout.h"

using namespace std;

void worker(Banker banker, int n);

mutex debug;
void log(string msg) {
  debug.lock();
  cout << msg << endl;
  debug.unlock();
}

// Initial values
int mutex_count = 3;
int worker_count = 8;
int lock_after = 6;
int random_after = 3;

int main() {
  // Initialise banker
  Banker banker(mutex_count);

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
  return 0;
}

// Lock if true in [i][j] place and is doLock. If doLock is false, unock [i][j].
void changeFromState(vector<vector<bool> > state, Banker banker, bool doLock) {
  for (int i = 0; i < worker_count; ++i) {
    for (int j = 0; j < mutex_count; ++j) {
      if (state[i][j]) {
        if (doLock) {
          banker.lock(j);
        } else {
          banker.unlock(j);
        }
      }
    }
  }
}

void worker(Banker banker, int n) {
  int iteration = 0;
  while (true) {
    vector<vector<bool> > state =
        generateState(iteration, worker_count, mutex_count);

    changeFromState(state, banker, true);
    setTimeout(600);
    cout << "------- THREAD " <<n<<" -------" << endl;
    cout << "Working... " << endl;
    cout << "Iteration:  " << iteration << endl;
    cout << "Locking at: " << lock_after << endl;
    cout << "Random at:  " << random_after << endl;
    cout << "------------------------" << endl;
    changeFromState(state, banker, false);

    iteration++;
  }
}
