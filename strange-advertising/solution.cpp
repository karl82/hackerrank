#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n;
    cin >> n;
    
    auto liked_sum = 0;
    auto seen = 5;
    for (auto i = 1; i <= n; ++i) {
        auto liked = floor(seen/2);
        seen = liked * 3;
        liked_sum += liked;
    }
    
    cout << liked_sum;
    
    return 0;
}

