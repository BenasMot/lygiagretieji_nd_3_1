#include <stdlib.h>

#include <string>
#include <vector>

using namespace std;

extern int lock_after;
extern int random_after;

bool randBool() { return rand() % 2; }

vector<vector<bool> > generateState(int iteration, int worker_count,
                                    int mutex_count) {
  string type = "unlocked";
  if (iteration % lock_after > random_after) {
    type = "random";
  }
  if (iteration % lock_after == lock_after - 1) {
    type = "locked";
  }

  vector<vector<bool> > state;
  switch (type) {
    case "locked":
      // Locked:
      // 1 1 1
      // 1 1 1
      // 1 1 1
      for (int i = 0; i < worker_count; ++i) {
        vector<bool> row;
        for (int j = 0; j < mutex_count; ++j) {
          row.push_back(1);
        }
        state.push_back(row);
      }
      break;

    case "unlocked":
      // Unlocked:
      // 1 0 0 0
      // 0 1 0 0
      // 0 0 1 0
      // 0 0 0 1
      for (int i = 0; i < worker_count; ++i) {
        vector<bool> row;
        for (int j = 0; j < mutex_count; ++j) {
          bool val = (i == j);
          row.push_back(val);
        }
        state.push_back(row);
      }
      break;

    case "random":
    default:
      // Random:
      // 0 1 1 0
      // 1 0 0 0
      // 1 1 0 1
      // 0 1 0 1
      for (int i = 0; i < worker_count; ++i) {
        vector<bool> row;
        for (int j = 0; j < mutex_count; ++j) {
          bool val = randBool();
          row.push_back(randBool());
        }
        state.push_back(row);
      }
      break;
  }
  return state;
}
