#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <memory>
#include <mutex>

using namespace std;

const int MaxCount = 500000;
const int ThreadCount = 4;

bool IsPrime(int n) {
    if(n == 1) return false;
    if(n == 2 || n == 3) return true;
    for(int i = 2; i < n - 1; i++)
        if(n % i == 0) return false;
    return true;
}

void PrintNums(const vector<int> &primes) {
    for(int v : primes)
        cout << v << endl;
}

int main() {
    int num = 1;
    recursive_mutex num_mutex;

    vector<int> primes;
    recursive_mutex primes_mutex;

    auto t0 = chrono::system_clock::now();

    vector<shared_ptr<thread>> threads;

    for(int i = 0; i < ThreadCount; i++) {
        shared_ptr<thread> thread(new class thread([&]() {
            while(true) {
                int n;
                {
                    lock_guard<recursive_mutex> num_lock(num_mutex);
                    n = num;
                    num++;
                }

                if(n >= MaxCount) break;

                if(IsPrime(n)) {
                    lock_guard<recursive_mutex> primes_lock(primes_mutex);
                    primes.push_back(n);
                }
            }
        }));

        threads.push_back(thread);
    }

    for(auto thread : threads)
        thread->join();

    auto t1 = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();

    cout << "Took " << duration << " milliseconds" << endl;
}