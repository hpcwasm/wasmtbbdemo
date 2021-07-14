
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>
#include <emscripten/threading.h>
#include <emscripten/val.h>
#include <iostream>
#include <memory>
#include <vector>
#include <ctime>

#include <tbb/task_group.h>
#include <tbb/parallel_for.h>
#include <tbb/task_scheduler_init.h>

using namespace tbb;

struct mytask {
  mytask(size_t n) : _n(n) {}
  void operator()() {
    volatile double sum = 0;
    for (int i = 0; i < 100000000; ++i) {
      sum += 5.3 / i;
    } // Deliberately run slow
    // std::cout << "[" << _n << "]";
  }
  size_t _n;
};

// static std::vector<mytask> tasks;

class Example {
public:
  static std::shared_ptr<tbb::task_scheduler_init> sched;

  static std::vector<mytask> tasks;

  static void init(int numThreads) {
    sched = std::make_shared<tbb::task_scheduler_init>(numThreads);
    std::cout << "Example::init(" << numThreads << ")"
              << std::endl;
  }

  static int createTasks(int numTasks) {
    for (int i = 0; i < numTasks; ++i)
      tasks.push_back(mytask(i));
    std::cout << "created " << numTasks << " tasks" << std::endl;
    return numTasks;
  }

  static int runParallel(int grainsize) {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, tasks.size()),
                      [](const tbb::blocked_range<size_t> &r) {
                        for (size_t i = r.begin(); i < r.end(); ++i) {
                          tasks[i]();
                        }
                      });
    std::cout << "runParallel done " << std::endl;            
    return grainsize;
  }

  static int runSerial() {
    for (size_t i = 0; i < tasks.size(); i++) {
      tasks[i]();
    }
    std::cout << "runSerial done " << std::endl;            
    return 1;
  }
};

std::vector<mytask> Example::tasks;
std::shared_ptr<tbb::task_scheduler_init> Example::sched;

int Fib(int n) {
  std::cout << "(n < 2)" << std::endl;
  if (n < 2) {
    std::cout << "(n < 2)" << std::endl;
    return n;
  } else {
    int x, y;

    // {
    //   task_group g;
    //   g.run([&] { x = Fib(n - 1); }); // spawn a task
    //   g.run([&] { y = Fib(n - 2); }); // spawn another task
    //   g.wait();                       // wait for both tasks to complete
    // }
    {

      x = Fib(n - 1);
      x = Fib(n - 2);
    }
    return x + y;
  }
}

int main(){
  std::cout << "test\n";
  auto example = Example();
  clock_t begin_time = clock();
  example.init(2);
  clock_t end_time = clock();
  std::cout << float( end_time - begin_time ) /  CLOCKS_PER_SEC << std::endl; 

  begin_time = clock();
  example.createTasks(64);
  end_time = clock();
  std::cout << float( end_time - begin_time ) /  CLOCKS_PER_SEC << std::endl;
  begin_time = clock();
  example.runParallel(16);
  end_time = clock();
  std::cout << float( end_time - begin_time ) /  CLOCKS_PER_SEC << std::endl;
  begin_time = clock();
  example.runSerial();
  end_time = clock();
  std::cout << float( end_time - begin_time ) /  CLOCKS_PER_SEC << std::endl;
  return 0;
}
// int myrun2(int n) { return Fib(n); }

EMSCRIPTEN_BINDINGS(tbbdemo) {
  emscripten::class_<Example>("Example")
      .class_function("init", &Example::init)
      .class_function("createTasks", &Example::createTasks)
      .class_function("runParallel", &Example::runParallel)
      .class_function("runSerial", &Example::runSerial);
}