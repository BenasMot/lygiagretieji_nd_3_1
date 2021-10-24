#include <iostream>
#include <string>
#include <vector>

using namespace std;

extern int lock_after;
extern int random_after;

bool randBool() { return rand() % 2; }

static int iteration = 0;
vector<bool> generateState(int mutex_count) {
  char type = 'u';
  if (iteration % lock_after > random_after) {
    type = 'r';
  }
  if (iteration % lock_after == lock_after - 1) {
    type = 'l';
  }

  vector<bool> state(mutex_count, 0);

  switch (type) {
    case 'l':
      // Locked:
      // 1 1 1
      state = vector<bool>(mutex_count, 1);
      iteration++;
      break;

    case 'u':
      // Unlocked:
      // 1 0 0 0
      state[iteration % mutex_count] = 1;
      iteration++;
      break;

    case 'r':
    default:
      // Random:
      // 0 1 1 0
      for (int i = 0; i < mutex_count; ++i) {
        state[i] = randBool();
      }
      iteration++;
      break;
  }
  return state;
}