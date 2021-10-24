#include <iostream>
#include <thread>
#include <vector>

#include "banker.h"
#include "generate_state.h"
#include "timeout.h"

using namespace std;

void worker(Banker banker, int n);

// Initial values
int mutex_count = 4;
int worker_count = 4;
int lock_after = 16;
int random_after = 12;

// Mutex for console output
mutex master;

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

void worker(Banker banker, int n) {
  while (true) {

    vector<bool> state = generateState(mutex_count);

    banker.lock(state);
    master.lock();
    cout << "------- THREAD " << n << " -------" << endl;
    cout << "Working... " << endl;
    cout << "Iteration:  " << iteration % lock_after << endl;
    cout << "Locking at: " << lock_after << endl;
    cout << "Random at:  " << random_after << endl;
    cout << "------------------------" << endl;
    master.unlock();
    setTimeout(100);
    banker.unlock(state);
  }
}
