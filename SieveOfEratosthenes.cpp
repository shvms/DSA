#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

void generateSieve(long long);

int main() {
    long long limit = 2*100000000;
    
    auto t1 = chrono::high_resolution_clock::now();
    generateSieve(limit);
    auto t2 = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    cout << duration << " ms" << endl;

    return 0;
}

void generateSieve(long long limit) {
    vector<bool> isPrime(limit, true);

    for(long long i=2;i*i<=limit;i++) {
        if (isPrime[i]) {
            for(long long j=i*i;j<=limit;j+=i) {
                isPrime[j] = false;
            }
        }
    }
    // for(long long i=2;i<=limit;i++) {
    //     if (isPrime[i])
    //         cout << i << " ";
    // }
    // cout << endl;
}