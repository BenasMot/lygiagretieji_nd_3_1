#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>
using namespace std;

void worker(vector<mutex *> mtx, int n);
void setTimeout(int ms);
vector<int> randomArray(int size);

int workers = 8;
int mutex_count = 3;

int main() {
  vector<mutex *> mutexes(3);
  for (int i = 0; i < mutex_count; ++i) {
    mutexes[i] = new mutex();
  }

  thread tid[workers];
  for (int i = 0; i < workers; ++i) {
    tid[i] = thread(worker, mutexes, i);
  }

  for (int i = 0; i < workers; ++i) {
    tid[i].join();
  }

  for (int i = 0; i < mutex_count; ++i) {
    delete mutexes[i];
  }

  return 0;
}

void worker(vector<mutex *> mtx, int n) {
  while (true) {
    vector<int> random_order = randomArray(mutex_count);
    for (auto i : random_order) {
      mtx[i]->lock();
    }

    cout << "Worker " << n << " locked everything" << endl;
    setTimeout(200);

    for (auto i : random_order) {
      mtx[i]->unlock();
    }
  }
}

void setTimeout(int ms) { this_thread::sleep_for(chrono::milliseconds(ms)); }

vector<int> randomArray(int size) {
  vector<int> arr(size);
  for (int i : arr) {
    arr.push_back(i);
  }
  shuffle(arr.begin(), arr.end(), default_random_engine());
  return arr;
}