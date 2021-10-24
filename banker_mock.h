#include <mutex>
#include <vector>
using namespace std;

class Banker {
  vector<mutex *> mutexes;

 public:
  Banker(int mutex_count) {
    for (int i = 0; i < mutex_count; ++i) {
      this->mutexes.push_back(new mutex());
    }
  }
  void lock(vector<bool> request) {
    for (int i = 0; i < request.size(); ++i) {
      if (request[i]) {
        this->mutexes[i]->lock();
      }
    }
  }

  void unlock(vector<bool> request) {
    for (int i = 0; i < request.size(); ++i) {
      if (request[i]) {
        this->mutexes[i]->unlock();
      }
    }
  }

  void cleanup() {
    for (int i = 0; i < mutexes.size(); ++i) {
      delete this->mutexes[i];
    }
  }
};