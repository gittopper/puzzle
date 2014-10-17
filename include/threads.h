#pragma once
#include <iostream>
#include <windows.h>
#include <memory>

class Task {
public:
  virtual void* run() = 0;
  virtual ~Task(){}
};

class Thread {
public:
  Thread(std::auto_ptr<Task> run);
  Thread();
  virtual ~Thread();
  void start();
  void* join();
private:
  HANDLE hThread;
  unsigned wThreadID;
  // task object will be deleted automatically
  std::auto_ptr<Task> task;
  Thread(const Thread&);
  const Thread& operator=(const Thread&);
  // called when run() completes
  void setCompleted();
  // stores return value from run()
  void* result;
  virtual void* run() {return 0;}
  static unsigned WINAPI startThreadRunnable(LPVOID pVoid);
  static unsigned WINAPI startThread(LPVOID pVoid);
  void printError(LPTSTR lpszFunction, LPSTR fileName, int lineNumber);
};

