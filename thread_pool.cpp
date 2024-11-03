#include "thread_pool.h"

void ThreadPool::SpawnDetachedThread_Atomic()
{
    for (int i = m_NumThreads; i > 0; --i)
    {
        std::thread(&ThreadPool::ThreadStart_Atomic, this, 20 * i).detach();
    }
}

void ThreadPool::ThreadStart_Atomic(int workTime)
{
    this_thread::sleep_for(chrono::milliseconds(workTime));

    // This thread is done, so subtract 1
    int oldVal = m_Pool.fetch_sub(1);

    char buf[100];
    snprintf(buf, sizeof(buf), "ThreadID: %x worked %d ms, OldVal %d\n",
            this_thread::get_id(), workTime, oldVal);
    cout << buf;
}

void ThreadPool::SpawnDetachedThread_Atomic_CV()
{
    for (int i = m_NumThreads; i > 0; --i)
    {
        std::thread(&ThreadPool::ThreadStart_Atomic_CV, this, 20 * i).detach();
    }
}

void ThreadPool::ThreadStart_Atomic_CV(int workTime)
{
    this_thread::sleep_for(chrono::milliseconds(workTime));

    // This thread is done, so subtract 1
    int oldVal = m_Pool.fetch_sub(1);

    char buf[100];
    snprintf(buf, sizeof(buf), "ThreadID: %x worked %d ms, OldVal %d\n",
            this_thread::get_id(), workTime, oldVal);
    cout << buf;

    if (GetRunningThreadNum() == 0)
    {
        m_CV.notify_one();
        cout<<"All threads are done, NOTIFIED by thread: "<<this_thread::get_id()<<endl;
    }
}

void ThreadPool::Wait()
{
    std::unique_lock<std::mutex> ulk(m_Mutex);
    std::thread::id id = this_thread::get_id();
    cout<<"Wait-ing: thread: "<<id<<endl;;
    m_CV.wait(ulk);
    cout<<"Done with waiting: thread: "<<id<<endl;
}
