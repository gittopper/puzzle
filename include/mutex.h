#ifndef _MutexLock_H_
#define _MutexLock_H_

//File: MutexLock.h

#include <windows.h>
#include <process.h>
#include <iostream>

//File: NonCopyable.h

#include <iostream>

namespace examples
{
  class NonCopyable
  {
  protected:
    NonCopyable(){}
        ~NonCopyable(){}

  private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
  };

  class MutexLock : public NonCopyable
  {
  public:
    MutexLock()
    {
      m_hMutex = (HANDLE) ::CreateMutex(0, 0, 0);
      if(NULL == m_hMutex)
      {
        std::cout << "ERROR: Cannot create mutex" << std::endl;
      }
    }

    virtual ~MutexLock()
    {
      ::CloseHandle(m_hMutex);
    }

    void lock()
    {
      if(::WaitForSingleObject(m_hMutex, INFINITE) != WAIT_OBJECT_0)
      {
        std::cout << "ERROR: Cannot acquire mutex" << std::endl;
      }
    }

    bool tryLock(size_t timeOut)
    {
      bool retval = false;
      switch(::WaitForSingleObject(m_hMutex, timeOut))
      {
      case WAIT_OBJECT_0:
        retval = true;
        break;
      case WAIT_TIMEOUT:
        std::cout << "ERROR: Cannot acquire mutex" << std::endl;
        break;
      default:
        std::cout << "ERROR: Cannot acquire mutex" << std::endl;
        break;
      }

      return retval;
    }

    void unlock()
    {
      if(::ReleaseMutex(m_hMutex) == 0)
      {
        std::cout << "ERROR: Cannot release mutex" << std::endl;
      }
    }

  private:
    HANDLE m_hMutex;
  };

}

#endif //_MutexLock_H_


