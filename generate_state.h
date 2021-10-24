#include <stdlib.h>

#include <vector>

using namespace std;

extern int lock_after;
extern int random_after;

bool randBool() { return rand() % 2; }

vector<bool> generateState(int iteration, int mutex_count) {
  char type = 'u';
  if (iteration % lock_after > random_after) {
    type = 'r';
  }
  if (iteration % lock_after == lock_after - 1) {
    type = 'l';
  }

  vector<bool> state;
  switch (type) {
    case 'l':
      // Locked:
      // 1 1 1
      state = vector<bool>(mutex_count, 1);
      break;

    case 'u':
      // Unlocked:
      // 1 0 0 0
      state[iteration % mutex_count] = true;
      break;

    case 'r':
    default:
      // Random:
      // 0 1 1 0
      for (int j = 0; j < mutex_count; ++j) {
        bool val = randBool();
        state.push_back(randBool());
      }
      break;
  }
  return state;
}