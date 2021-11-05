#include <cstdlib>

class Scheduler {
  class Task {
   public:
    int priority;
    explicit Task(int p) : priority(p) {}
  };
  Task ** taskarr;
  size_t n;

 public:
  Scheduler(Scheduler & rhs) : taskarr(new Task *[rhs.n]), n(rhs.n) {
    for (size_t i = 0; i < n; i++) {
      taskarr[i] = new Task(*rhs.taskarr[i]);
    }
  }
  ~Scheduler() {
    for (size_t i = 0; i < n; i++) {
      delete taskarr[i];
    }
    delete[] taskarr;
  }
};
