#ifndef TIMER_H
#define TIMER_H
#include <logger.hpp>
#include <string>
#include <time.h>

class Timer {
  public:
    Timer() {}

    int getN() const {
        return n_;
    }

    float getAvgTime() const {
        return n_ > 0 ? total_time_ / n_ : 0;
    }

    void start() {
        begin_time_ = clock();
        running_ = true;
    }
    float stop() {
        if (!running_) return time();
        float curTime = clock();
        elapsed_time_ = (curTime - float(begin_time_)) / CLOCKS_PER_SEC;
        running_ = false;
        n_++;
        total_time_ += elapsed_time_;
        return elapsed_time_;
    }

    float time() const {
        if (running_) {
            float curTime = clock();
            elapsed_time_ = (curTime - float(begin_time_)) / CLOCKS_PER_SEC;
        }
        return elapsed_time_;
    }
    void reset() {
        elapsed_time_ = 0;
        running_ = false;
    }

    static std::string asString(float t) {
        float s = t - int(t / 60) * 60;
        float m = t = (t - s) / 60;
        float h = t = (t - m) / 60;
        return getLogString(h, ":", m, ":", s);
    }

    std::string asString() {
        return asString(time());
    }

    ~Timer() {}

  private:
    mutable clock_t begin_time_ = 0;
    mutable int n_ = 0;
    mutable float total_time_ = 0;
    mutable float elapsed_time_ = 0;
    mutable bool running_ = false;
};
inline std::string getTimeStamp() {
    time_t t = time(0);  // get time now
    struct tm* now = localtime(&t);

    return getLogString(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
                        now->tm_hour, now->tm_min, now->tm_sec);
}

#endif  // TIMER_H
