
#include <stdlib.h>

#include <vector>

using namespace std;

bool randBool() { return rand() % 2; }

vector<vector<bool> > generateState(int iteration, int worker_count,
                                    int mutex_count) {
  char type = 'u';
  if (iteration % 42 > 22) {
    type = 'r';
  }
  if (iteration % 42 == 41) {
    type = 'l';
  }

  vector<vector<bool> > state;
  switch (type) {
    case 'l':
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

    case 'u':
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

    case 'r':
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
