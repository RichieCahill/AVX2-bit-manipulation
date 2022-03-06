//This code was provedid by alice

#pragma once
#include <fmt/core.h>
#include <chrono>

class CBenchmark {
 private:
  std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds>
      t0;
  double elapsedTime;
  std::string msg;

 public:
  explicit CBenchmark(std::string msg) : elapsedTime(0), msg(std::move(msg)) { reset(); }

  constexpr void reset() { elapsedTime = 0; }

  void start() {
    t0 = std::chrono::time_point_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now());
  }

  void end() {
    auto end = std::chrono::time_point_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now());
    elapsedTime += (end - t0).count();
  }

  [[nodiscard]] double elapsed() const { return elapsedTime; }
  std::string display() const {
    return fmt::format("{} elapsed time: {}\n", msg, elapsedTime);
  }
  std::string displayavg(uint64_t iterations) const {
    return fmt::format("{} elapsed time: {}\n", msg, elapsedTime / iterations);
  }

  template <typename Func>
  static std::string benchmark(const std::string& msg,
                        uint64_t numIterations, Func func) {
    uint64_t iter = numIterations;
    CBenchmark bench(msg);
    bench.start();
    for (; numIterations > 0; numIterations--) func();
    bench.end();
    return bench.displayavg(iter);
  }
};