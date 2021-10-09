#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

void worker(int n);
void setTimeout(int ms);

mutex my_res;

int main()
{
    int workers = 4;

    thread tid[workers];
    for (int i = 0; i < workers; i++)
    {
        tid[i] = thread(worker, i);
    }

    for (int i = 0; i < workers; ++i)
    {
        tid[i].join();
    }
    return 0;
}

void worker(int n)
{
    int non_blocking_time = n%2==0 ? 700-(n*150) : 400;
    int blocking_time = 1000;

    setTimeout(non_blocking_time);
    my_res.lock();
    setTimeout(blocking_time);
    cout << "This thread (" << n << ") is waiting " << (float)blocking_time/1000 << "s" << endl;
    my_res.unlock();
}

void setTimeout(int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}