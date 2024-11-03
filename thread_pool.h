#include <bits/stdc++.h>

using namespace std;

class ThreadPool
{
    private:
        int m_NumThreads;
        atomic<int> m_Pool;
        std::mutex m_Mutex;
        std::condition_variable m_CV;

        void ThreadStart_Atomic(int workTime);

        void ThreadStart_Atomic_CV(int workTime);

        ThreadPool(int num = 5) :
            m_NumThreads(num)
        {
            // Set value atomically
            m_Pool.store(num, std::memory_order_relaxed);
        }

    public:
        static ThreadPool & Instance(int num = 5)
        {
            static ThreadPool pool(num);

            return pool;
        }

        void SpawnDetachedThread_Atomic();

        void SpawnDetachedThread_Atomic_CV();

        int GetRunningThreadNum() const
        {
            return m_Pool.load();
        }

        /*
         * This call will return when all threads in pool are done with
         * processing.
         */
        void Wait();
};
