#include <mutex>
using namespace std;

class Banker {
  vector<mutex *> mutexes;

 public:
  void init(int mutex_count) {
    for (int i = 0; i < mutex_count; ++i) {
      mutexes[i] = new mutex();
    }
  }
  void lock(int i) { mutexes[i]->lock(); }

  void unlock(int i) { mutexes[i]->unlock(); }

  void cleanup() {
    for (int i = 0; i < mutexes.size(); ++i) {
      delete mutexes[i];
    }
  }
};