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
int lock_after_itarations = 60;

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
  int iterations = 0;
  while (true) {
    vector<int> random_order(mutex_count);
    if (iterations % 20 == 0) {
      random_order = randomArray(mutex_count);
    } else {
      random_order = {0, 1, 2};
    }

    for (int i = 0; i < mutex_count; ++i) {
      mtx[random_order[i]]->lock();
      cout << "Worker " << n << " locked " << i << endl;
    }

    setTimeout(1000);

    for (int i = 0; i < mutex_count; ++i) {
      cout << "Worker " << n << " unlocked " << i << endl;
      mtx[random_order[i]]->unlock();
    }
    iterations++;
  }
}

void setTimeout(int ms) { this_thread::sleep_for(chrono::milliseconds(ms)); }

vector<int> randomArray(int size) {
  vector<int> arr(size);
  for (int i = 0; i < size; ++i) {
    arr.push_back(i);
  }
  shuffle(arr.begin(), arr.end(), default_random_engine(0));
  return arr;
}