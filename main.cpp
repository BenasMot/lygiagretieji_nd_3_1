#include <stdlib.h>

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "banker.h"
#include "timeout.h"

using namespace std;

void worker(vector<mutex *> mutexes, int n);

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
  
  // Initialise mutexes
  vector<mutex *> mutexes(mutex_count);
  for (int i = 0; i < mutex_count; ++i) {
    mutexes[i] = new mutex();
  }

  // Launch threads
  thread threads[worker_count];
  for (int i = 0; i < worker_count; ++i) {
    threads[i] = thread(worker, mutexes, i);
  }

  // Wait for threads to complete execution
  for (int i = 0; i < worker_count; ++i) {
    threads[i].join();
  }

  // Cleanup mutexes
  for (int i = 0; i < mutex_count; ++i) {
    delete mutexes[i];
  }
  return 0;
}

bool randBool() { return rand() % 2; }

vector<vector<bool> > generateState(int iteration) {
  char type = 'u';
  if (iteration % 42 > 22) {
    type = 'r';
  }
  if (iteration % 42 == 41) {
    type = 'l';
  }

  vector<vector<bool> > state;
  switch (type) {
    case 'l':
      // Locked:
      // 1 1 1
      // 1 1 1
      // 1 1 1
      for (int i = 0; i < worker_count; ++i) {
        vector<bool> row;
        for (int j = 0; j < mutex_count; ++j) {
          row.push_back(1);
        }
        state.push_back(row);
      }
      break;

    case 'u':
      // Unlocked:
      // 1 0 0 0
      // 0 1 0 0
      // 0 0 1 0
      // 0 0 0 1
      for (int i = 0; i < worker_count; ++i) {
        vector<bool> row;
        for (int j = 0; j < mutex_count; ++j) {
          bool val = (i == j);
          row.push_back(val);
        }
        state.push_back(row);
      }
      break;

    case 'r':
    default:
      // Random:
      // 0 1 1 0
      // 1 0 0 0
      // 1 1 0 1
      // 0 1 0 1
      for (int i = 0; i < worker_count; ++i) {
        vector<bool> row;
        for (int j = 0; j < mutex_count; ++j) {
          bool val = randBool();
          row.push_back(randBool());
        }
        state.push_back(row);
      }
      break;
  }
  return state;
}

// Lock if true in [i][j] place and is doLock. If doLock is false, unock [i][j].
void changeFromState(vector<vector<bool> > state, vector<mutex *> mutexes,
                     bool doLock) {
  for (int i = 0; i < worker_count; ++i) {
    for (int j = 0; j < mutex_count; ++j) {
      if (state[i][j]) {
        if (doLock) {
          mutexes[j]->lock();
        } else {
          mutexes[j]->unlock();
        }
      }
    }
  }
}

void worker(vector<mutex *> mutexes, int n) {
  vector<vector<bool> > unlocked = generateState('u');
  vector<vector<bool> > locked = generateState('l');

  int iteration = 0;
  while (true) {
    vector<vector<bool> > state = generateState(iteration);

    changeFromState(state, mutexes, true);
    cout << "Test" << n << endl;
    setTimeout(200);
    changeFromState(state, mutexes, false);

    iteration++;
  }
}
