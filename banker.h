#include <mutex>
#include <vector>
using namespace std;

class Banker {
  vector<mutex *> mutexes;
  vector<bool> available;

 public:
  Banker(int mutex_count) {
    for (int i = 0; i < mutex_count; ++i) {
      this->mutexes.push_back(new mutex());
    }
    this->available.resize(mutex_count, 1);
  }

  void lock(vector<bool> request) {
    while (true) {
      bool can_lock = true;
      vector<bool> result(this->available.size());

      for (int i = 0; i < request.size(); ++i) {
        if (request[i] && available[i]) {
          result[i] = false;
        } else if (!request[i]) {
          result[i] = available[i];
        } else {
          can_lock = false;
          break;
        }
      }

      if (can_lock) {
        for (int i = 0; i < this->available.size(); i++) {
          if (request[i]) {
            this->mutexes[i]->lock();
          }
        }
        this->available = result;
        break;
      }
    }
  }

  void unlock(vector<bool> request) {
    for (int i = 0; i < request.size(); i++) {
      if (request[i]) {
        this->mutexes[i]->unlock();
        this->available[i] = true;
      }
    }
  }

  void cleanup() {
    for (int i = 0; i < mutexes.size(); ++i) {
      delete this->mutexes[i];
    }
  }
};
