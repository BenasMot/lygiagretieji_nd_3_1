#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex myMutex, myMutex1, myMutex2;

void shared_cout_thread_even(int i);
void shared_cout_thread_odd(int i);
void shared_cout_main(int i);
void worker(int n);

int iterations = 0;
int workers = 8;
int mutex_count = 3;
int dydis = 10;

int main() {
  thread tid[workers];

  for (int i = 0; i < workers; ++i) {
    tid[i] = thread(worker, i);
  }

  for (int i = 0; i > -dydis; i--) {
    shared_cout_main(i);
  }

  for (int i = 0; i < workers; ++i) {
    tid[i].join();
  }

  return 0;
}

void worker(int n) {
  while (true) {
    ++iterations;
    if (n % 2 == 0 && iterations % 20 == 0)
      shared_cout_thread_even(n);
    else
      shared_cout_thread_odd(n);
  }
}
void shared_cout_thread_even(int i) {
  lock_guard<mutex> g1(myMutex1);
  lock_guard<mutex> g2(myMutex2);
  cout << " " << i << " ";
}

void shared_cout_thread_odd(int i) {
  lock_guard<mutex> g2(myMutex2);
  lock_guard<mutex> g1(myMutex1);
  cout << " " << i << " ";
}

void shared_cout_main(int i) {
  lock_guard<mutex> g(myMutex);
  cout << " " << i << " ";
}
