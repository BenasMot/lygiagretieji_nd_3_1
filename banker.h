#include <mutex>
#include <vector>
#include <iostream>
using namespace std;

class Banker {
  vector<mutex *> mutexes;
  vector<bool> available;

 public:
  Banker(int mutex_count) {
    for (int i = 0; i < mutex_count; ++i) {
      this->mutexes.push_back(new mutex());
    }
  }
  void lock(vector<bool> request) {
    while (true) {
      bool can_lock = true;
      vector<bool> result(this->available.size());

      for (int i = 0; i < request.size(); ++i) {
        if (available[i] == request[i]) {
          result[i] = false;
        } else {
          cout << "PIZDEC" << endl;
          can_lock = false;
          break;
        }
      }

      if (can_lock) {
        for (int i = 0; i < this->available.size(); i++) {
          this->mutexes[i]->lock();
        }
        this->available = result;
        break;
      }
    }
  }

  void unlock(vector<bool> request) {
    for (int i = 0; i < request.size(); i++) {
      this->mutexes[i]->unlock();
    }
  }

  void cleanup() {
    for (int i = 0; i < mutexes.size(); ++i) {
      delete this->mutexes[i];
    }
  }
};