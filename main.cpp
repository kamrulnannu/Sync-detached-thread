#include "thread_pool.h"

void Driver_Atomic()
{
    ThreadPool & tp = ThreadPool::Instance(6);

    tp.SpawnDetachedThread_Atomic();

    int nt;
    do
    {
        nt = tp.GetRunningThreadNum();
    } while(nt != 0);

    // All threads terminates
}

void Driver_Atomic_And_CV()
{
    ThreadPool & tp = ThreadPool::Instance(6);

    tp.SpawnDetachedThread_Atomic_CV();

    tp.Wait();
}

int main()
{
    //Driver_Atomic();

    Driver_Atomic_And_CV();
}

