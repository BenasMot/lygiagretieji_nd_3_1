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
    // Let them all "work" for a bit
    setTimeout(1000);

    // If 0th, endless loop
    bool myBool = true;
    while(n == 0) {
        myBool = !myBool;
    }

    // If not 1st, keep on "working"
    if(n != 1) {
        setTimeout(5000);
    }

    my_res.lock();
    cout << "Thread " << n << " is no longer working " << endl;
    my_res.unlock();
}

void setTimeout(int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}